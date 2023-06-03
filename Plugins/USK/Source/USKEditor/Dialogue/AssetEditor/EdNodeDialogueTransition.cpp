// Created by Henry Jooste

#include "EdNodeDialogueTransition.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "Widgets/SToolTip.h"
#include "SGraphPanel.h"
#include "EdGraphSchema_K2.h"
#include "EditorStyleSet.h"
#include "USK/Dialogue/DialogueTransition.h"
#include "EdGraphNodeDialogueEntry.h"
#include "EdGraphNodeDialogueTransition.h"
#include "ConnectionDrawingPolicyDialogue.h"

/**
 * @brief Constructs the widget.
 * @param InArgs The slate arguments.
 * @param InNode The dialogue transition node to display and edit.
 */
void SEdNodeDialogueTransition::Construct(const FArguments& InArgs, UEdGraphNodeDialogueTransition* InNode)
{
	this->GraphNode = InNode;
	this->UpdateGraphNode();
}

/**
 * @brief Determines if a second pass of layout is required.
 * @return True if a second pass of layout is required, false otherwise.
 */
bool SEdNodeDialogueTransition::RequiresSecondPassLayout() const
{
	return true;
}

/**
 * @brief Performs a second pass of layout.
 * @param NodeToWidgetLookup A map of nodes to their corresponding widgets.
 */
void SEdNodeDialogueTransition::PerformSecondPassLayout(const TMap< UObject*, TSharedRef<SNode> >& NodeToWidgetLookup) const
{
	UEdGraphNodeDialogueTransition* EdgeNode = CastChecked<UEdGraphNodeDialogueTransition>(GraphNode);

	FGeometry StartGeom;
	FGeometry EndGeom;
	const UEdGraphNodeDialogueEntry* Start = EdgeNode->GetStartNode();
	const UEdGraphNodeDialogueEntry* End = EdgeNode->GetEndNode();
	
	if (Start != nullptr && End != nullptr)
	{
		const TSharedRef<SNode>* PFromWidget = NodeToWidgetLookup.Find(Start);
		const TSharedRef<SNode>* PToWidget = NodeToWidgetLookup.Find(End);
		if (PFromWidget != nullptr && PToWidget != nullptr)
		{
			const TSharedRef<SNode>& FromWidget = *PFromWidget;
			const TSharedRef<SNode>& ToWidget = *PToWidget;

			StartGeom = FGeometry(FVector2D(Start->NodePosX, Start->NodePosY),
				FVector2D::ZeroVector, FromWidget->GetDesiredSize(), 1.0f);
			EndGeom = FGeometry(FVector2D(End->NodePosX, End->NodePosY),
				FVector2D::ZeroVector, ToWidget->GetDesiredSize(), 1.0f);
		}
	}

	PositionBetweenTwoNodesWithOffset(StartGeom, EndGeom, 0, 1);
}

/**
 * @brief Updates the graph node.
 */
void SEdNodeDialogueTransition::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();
	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	const TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	this->ContentScale.Bind( this, &SGraphNode::GetContentScale );
	this->GetOrAddSlot( ENodeZone::Center )
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				SNew(SImage)
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 1
				.Image(FAppStyle::GetBrush("Graph.TransitionNode.ColorSpill"))
#else
				.Image(FEditorStyle::GetBrush("Graph.TransitionNode.ColorSpill"))
#endif
				.ColorAndOpacity(this, &SEdNodeDialogueTransition::GetEdgeColor)
			]
			+ SOverlay::Slot()
			[
				SNew(SImage)
				.Image(this, &SEdNodeDialogueTransition::GetEdgeImage)
				.Visibility(this, &SEdNodeDialogueTransition::GetEdgeImageVisibility)
			]

			+ SOverlay::Slot()
			.Padding(FMargin(4.0f, 4.0f, 4.0f, 4.0f))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					SAssignNew(InlineEditableText, SInlineEditableTextBlock)
					.ColorAndOpacity(FLinearColor::Black)
					.Visibility(this, &SEdNodeDialogueTransition::GetEdgeTitleVisibility)
					.Font(FCoreStyle::GetDefaultFontStyle("Regular", 12))
					.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
					.OnTextCommitted(this, &SEdNodeDialogueTransition::OnNameTextCommited)
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					NodeTitle.ToSharedRef()
				]
			]
		];
}

/**
 * @brief Calculates the position for multiple nodes to be placed between a start and end point.
 * @param StartGeom The geometry of the start node.
 * @param EndGeom The geometry of the end node.
 * @param NodeIndex The index of this node.
 * @param MaxNodes The maximum number of nodes to position.
 */
void SEdNodeDialogueTransition::PositionBetweenTwoNodesWithOffset(const FGeometry& StartGeom, const FGeometry& EndGeom, int32 NodeIndex, int32 MaxNodes) const
{
	const FVector2D StartCenter = FGeometryHelper::CenterOf(StartGeom);
	const FVector2D EndCenter = FGeometryHelper::CenterOf(EndGeom);
	const FVector2D SeedPoint = (StartCenter + EndCenter) * 0.5f;
	const FVector2D StartAnchorPoint = FGeometryHelper::FindClosestPointOnGeom(StartGeom, SeedPoint);
	const FVector2D EndAnchorPoint = FGeometryHelper::FindClosestPointOnGeom(EndGeom, SeedPoint);
	
	const float Height = 30.0f;
	const FVector2D DesiredNodeSize = GetDesiredSize();
	FVector2D DeltaPos(EndAnchorPoint - StartAnchorPoint);

	if (DeltaPos.IsNearlyZero())
	{
		DeltaPos = FVector2D(10.0f, 0.0f);
	}

	const FVector2D Normal = FVector2D(DeltaPos.Y, -DeltaPos.X).GetSafeNormal();
	const FVector2D NewCenter = StartAnchorPoint + (0.5f * DeltaPos) + (Height * Normal);
	const FVector2D DeltaNormal = DeltaPos.GetSafeNormal();

	constexpr float MultiNodeSpace = 0.2f;
	constexpr float MultiNodeStep = (1.f + MultiNodeSpace);
	const float MultiNodeStart = -((MaxNodes - 1) * MultiNodeStep) / 2.f;
	const float MultiNodeOffset = MultiNodeStart + (NodeIndex * MultiNodeStep);
	const FVector2D NewCorner = NewCenter - (0.5f * DesiredNodeSize) +
		(DeltaNormal * MultiNodeOffset * DesiredNodeSize.Size());

	GraphNode->NodePosX = NewCorner.X;
	GraphNode->NodePosY = NewCorner.Y;
}

/**
 * @brief Gets the color of the edge.
 * @return The color of the edge.
 */
FSlateColor SEdNodeDialogueTransition::GetEdgeColor() const
{
	const UEdGraphNodeDialogueTransition* EdgeNode = CastChecked<UEdGraphNodeDialogueTransition>(GraphNode);
	if (!IsValid(EdgeNode) || !IsValid(EdgeNode->DialogueEdge) ||
		!IsValid(EdgeNode->DialogueEdge->StartEntry) || !IsValid(EdgeNode->DialogueEdge->EndEntry) ||
		!IsValid(EdgeNode->DialogueEdge->EndEntry->Owner) ||
		EdgeNode->DialogueEdge->StartEntry->Transition != EDialogueTransitionType::Choice)
	{
		return FLinearColor(0.9f, 0.9f, 0.9f, 1.0f);
	}

	return EdgeNode->DialogueEdge->EndEntry->Owner->Color;	
}

/**
 * @brief Gets the image of the edge.
 * @return The image of the edge.
 */
const FSlateBrush* SEdNodeDialogueTransition::GetEdgeImage() const
{
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 1
	return FAppStyle::GetBrush("Graph.TransitionNode.Icon");
#else
	return FEditorStyle::GetBrush("Graph.TransitionNode.Icon");
#endif
}

/**
 * @brief Gets the visibility of the edge image.
 * @return The visibility of the edge image.
 */
EVisibility SEdNodeDialogueTransition::GetEdgeImageVisibility() const
{
	return GetEdgeTitleVisibility() == EVisibility::Visible ? EVisibility::Collapsed : EVisibility::Visible;
}

/**
 * @brief Gets the visibility of the edge title.
 * @return The visibility of the edge title.
 */
EVisibility SEdNodeDialogueTransition::GetEdgeTitleVisibility() const
{
	const UEdGraphNodeDialogueTransition* EdgeNode = CastChecked<UEdGraphNodeDialogueTransition>(GraphNode);
	if (!IsValid(EdgeNode) || !IsValid(EdgeNode->DialogueEdge) ||
		!IsValid(EdgeNode->DialogueEdge->StartEntry) ||
		EdgeNode->DialogueEdge->StartEntry->Transition != EDialogueTransitionType::Choice)
	{
		return EVisibility::Collapsed;
	}

	return EVisibility::Visible;
}