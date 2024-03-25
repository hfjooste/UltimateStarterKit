// Created by Henry Jooste

#include "EdNodeDialogueEntry.h"

#include "DialoguePin.h"
#include "EditorStyleSet.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "SCommentBubble.h"
#include "SlateOptMacros.h"
#include "SGraphPin.h"
#include "GraphEditorSettings.h"
#include "EdGraphNodeDialogueEntry.h"

/**
 * @brief Constructs the SEdNodeDialogueEntry widget.
 * @param InArgs The Slate arguments for the widget.
 * @param InNode The UEdGraphNodeDialogueEntry instance that this widget represents.
 */
void SEdNodeDialogueEntry::Construct(const FArguments& InArgs, UEdGraphNodeDialogueEntry* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
	InNode->SEdNode = this;
}

/**
 * @brief Gets the maximum width at which text should wrap.
 * @return The maximum width at which text should wrap.
 */
float SEdNodeDialogueEntry::GetWrapTextAt() const
{
	return 350;
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

/**
 * @brief Updates the appearance of the node based on its current state.
 */
void SEdNodeDialogueEntry::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();
	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	const FSlateBrush *NodeTypeIcon = GetNameIcon();
	constexpr FLinearColor TitleShadowColor(0.6f, 0.6f, 0.6f);
	TSharedPtr<SErrorText> ErrorText;
	TSharedPtr<SVerticalBox> NodeBody;
	const TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);
	this->GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(SBorder)
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 1
			.BorderImage(FAppStyle::GetBrush("Graph.StateNode.Body"))
#else
			.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
#endif
			.Padding(0.0f)
			.BorderBackgroundColor(this, &SEdNodeDialogueEntry::GetBorderBackgroundColor)
			[
				SNew(SOverlay)

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SVerticalBox)

					+ SVerticalBox::Slot()
					.FillHeight(1)
					[
						SAssignNew(LeftNodeBox, SVerticalBox)
					]

					+ SVerticalBox::Slot()
					.FillHeight(1)
					[
						SAssignNew(RightNodeBox, SVerticalBox)
					]
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.Padding(8.0f)
				[
					SNew(SBorder)
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 1
					.BorderImage(FAppStyle::GetBrush("Graph.StateNode.ColorSpill"))
#else
					.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.ColorSpill"))
#endif
					.BorderBackgroundColor(TitleShadowColor)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.Visibility(EVisibility::SelfHitTestInvisible)
					.Padding(6.0f)
					[
						SAssignNew(NodeBody, SVerticalBox)

						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SHorizontalBox)

							+ SHorizontalBox::Slot()
							.AutoWidth()
							[
								SAssignNew(ErrorText, SErrorText)
								.BackgroundColor(this, &SEdNodeDialogueEntry::GetErrorColor)
								.ToolTipText(this, &SEdNodeDialogueEntry::GetErrorMsgToolTip)
							]

							+SHorizontalBox::Slot()
							.AutoWidth()
							.VAlign(VAlign_Center)
							[
								SNew(SImage)
								.Image(NodeTypeIcon)
							]

							+ SHorizontalBox::Slot()
							.Padding(FMargin(4.0f, 0.0f, 4.0f, 0.0f))
							[
								SNew(SVerticalBox)
								+ SVerticalBox::Slot()
								.AutoHeight()
								[
									SAssignNew(InlineEditableText, SInlineEditableTextBlock)
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 1
									.Style(FAppStyle::Get(), "Graph.StateNode.NodeTitleInlineEditableText")
#else
									.Style(FEditorStyle::Get(), "Graph.StateNode.NodeTitleInlineEditableText")
#endif
									.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
									.WrapTextAt(this, &SEdNodeDialogueEntry::GetWrapTextAt)
									.OnVerifyTextChanged(this, &SEdNodeDialogueEntry::OnVerifyNameTextChanged)
									.OnTextCommitted(this, &SEdNodeDialogueEntry::OnNameTextCommited)
									.IsReadOnly(this, &SEdNodeDialogueEntry::IsNameReadOnly)
									.IsSelected(this, &SEdNodeDialogueEntry::IsSelectedExclusively)
								]
								+ SVerticalBox::Slot()
								.AutoHeight()
								[
									NodeTitle.ToSharedRef()
								]
							]
						]					
					]
				]
			]
		];

	TSharedPtr<SCommentBubble> CommentBubble;
	const FSlateColor CommentColor = GetDefault<UGraphEditorSettings>()->DefaultCommentNodeTitleColor;

	SAssignNew(CommentBubble, SCommentBubble)
		.GraphNode(GraphNode)
		.Text(this, &SGraphNode::GetNodeComment)
		.OnTextCommitted(this, &SGraphNode::OnCommentTextCommitted)
		.ColorAndOpacity(CommentColor)
		.AllowPinning(true)
		.EnableTitleBarBubble(true)
		.EnableBubbleCtrls(true)
		.GraphLOD(this, &SGraphNode::GetCurrentLOD)
		.IsGraphNodeHovered(this, &SGraphNode::IsHovered);

	GetOrAddSlot(ENodeZone::TopCenter)
		.SlotOffset(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetOffset))
		.SlotSize(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetSize))
		.AllowScaling(TAttribute<bool>(CommentBubble.Get(), &SCommentBubble::IsScalingAllowed))
		.VAlign(VAlign_Top)
		[
			CommentBubble.ToSharedRef()
		];

	ErrorReporting = ErrorText;
	ErrorReporting->SetError(ErrorMsg);
	CreatePinWidgets();
}

/**
 * @brief Creates the pin widgets for this node.
 */
void SEdNodeDialogueEntry::CreatePinWidgets()
{
	UEdGraphNodeDialogueEntry* StateNode = CastChecked<UEdGraphNodeDialogueEntry>(GraphNode);
	for (int32 PinIdx = 0; PinIdx < StateNode->Pins.Num(); PinIdx++)
	{
		UEdGraphPin* MyPin = StateNode->Pins[PinIdx];
		if (!MyPin->bHidden)
		{
			TSharedPtr<SGraphPin> NewPin = SNew(SDialoguePin, MyPin);
			AddPin(NewPin.ToSharedRef());
		}
	}
}

/**
 * @brief Adds a pin widget to this node.
 * @param PinToAdd The pin widget to add.
 */
void SEdNodeDialogueEntry::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	PinToAdd->SetOwner(SharedThis(this));

	const UEdGraphPin* PinObj = PinToAdd->GetPinObj();
	const bool bAdvancedParameter = PinObj && PinObj->bAdvancedView;
	if (bAdvancedParameter)
	{
		PinToAdd->SetVisibility( TAttribute<EVisibility>(PinToAdd, &SGraphPin::IsPinVisibleAsAdvanced) );
	}

	TSharedPtr<SVerticalBox> PinBox;
	if (PinToAdd->GetDirection() == EGPD_Input)
	{
		PinBox = LeftNodeBox;
		InputPins.Add(PinToAdd);
	}
	else
	{
		PinBox = RightNodeBox;
		OutputPins.Add(PinToAdd);
	}

	if (PinBox)
	{
		PinBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.FillHeight(1.0f)
			[
				PinToAdd
			];
	}
}

/**
 * @brief Determines whether the node name is read-only.
 * @return True if the node name is read-only, false otherwise.
 */
bool SEdNodeDialogueEntry::IsNameReadOnly() const
{
	return true;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

/**
 * @brief Called when the node name text has been committed.
 * @param InText The new text for the node name.
 * @param CommitInfo The type of text commit that occurred.
 */
void SEdNodeDialogueEntry::OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo)
{
	SGraphNode::OnNameTextCommited(InText, CommitInfo);
	UEdGraphNodeDialogueEntry* MyNode = CastChecked<UEdGraphNodeDialogueEntry>(GraphNode);

	if (MyNode != nullptr && MyNode->DialogueNode != nullptr)
	{
		const FScopedTransaction Transaction(FText::FromString("Dialogue Editor: Rename Node"));
		MyNode->Modify();
		MyNode->DialogueNode->Modify();
		UpdateGraphNode();
	}
}

/**
 * @brief Gets the background color of the node's border.
 * @return The background color of the node's border.
 */
FSlateColor SEdNodeDialogueEntry::GetBorderBackgroundColor() const
{
	const UEdGraphNodeDialogueEntry* MyNode = CastChecked<UEdGraphNodeDialogueEntry>(GraphNode);
	return MyNode ? MyNode->GetBackgroundColor() : FLinearColor(0.0f, 0.22f, 0.4f);
}

/**
 * @brief Gets the background color of the node.
 * @return The background color of the node.
 */
FSlateColor SEdNodeDialogueEntry::GetBackgroundColor() const
{
	return FLinearColor(0.1f, 0.1f, 0.1f);
}

/**
 * @brief Gets the visibility of the drag over marker.
 * @return The visibility of the drag over marker.
 */
EVisibility SEdNodeDialogueEntry::GetDragOverMarkerVisibility() const
{
	return EVisibility::Visible;
}

/**
 * @brief Gets the icon to display next to the node name.
 * @return The icon to display next to the node name.
 */
const FSlateBrush* SEdNodeDialogueEntry::GetNameIcon() const
{
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 1
	return FAppStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Icon"));
#else
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Icon"));
#endif
}