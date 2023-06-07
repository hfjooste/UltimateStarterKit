// Created by Henry Jooste

#include "DialogueDragConnection.h"

#include "EdGraphNodeDialogueEntry.h"
#include "EditorStyleSet.h"
#include "Widgets/SBoxPanel.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/Images/SImage.h"
#include "EdGraph/EdGraph.h"
#include "SGraphPanel.h"
#include "ScopedTransaction.h"

/**
 * @brief Constructor for creating a new instance of FDialogueDragConnection.
 * @param InGraphPanel The graph panel where the drag and drop action is taking place.
 * @param InStartingPins The pins that are being dragged and dropped.
 * @return A shared reference to the new instance of FDialogueDragConnection.
 */
TSharedRef<FDialogueDragConnection> FDialogueDragConnection::New(const TSharedRef<SGraphPanel>& InGraphPanel,
	const FDraggedPinTable& InStartingPins)
{
	TSharedRef<FDialogueDragConnection> Operation = MakeShareable(new FDialogueDragConnection(InGraphPanel, InStartingPins));
	Operation->Construct();
	return Operation;
}

/**
 * @brief Called when the pins are dropped onto the graph.
 * @param bDropWasHandled Whether the drop was handled or not.
 * @param MouseEvent The mouse event that triggered the drop.
 */
void FDialogueDragConnection::OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent)
{
	GraphPanel->OnStopMakingConnection();
	Super::OnDrop(bDropWasHandled, MouseEvent);
}

/**
 * @brief Called when the pins are being dragged.
 * @param DragDropEvent The drag and drop event.
 */
void FDialogueDragConnection::OnDragged(const class FDragDropEvent& DragDropEvent)
{
	const FVector2D TargetPosition = DragDropEvent.GetScreenSpacePosition();
	CursorDecoratorWindow->MoveWindowTo(DragDropEvent.GetScreenSpacePosition() + DecoratorAdjust);
	GraphPanel->RequestDeferredPan(TargetPosition);
}

/**
 * @brief Called when the hover target changes.
 */
void FDialogueDragConnection::HoverTargetChanged()
{
	TArray<FPinConnectionResponse> UniqueMessages;
	if (const UEdGraphPin* TargetPinObj = GetHoveredPin())
	{
		TArray<UEdGraphPin*> ValidSourcePins;
		ValidateGraphPinList(ValidSourcePins);

		for (const UEdGraphPin* StartingPinObj : ValidSourcePins)
		{
			const UEdGraph* GraphObj = StartingPinObj->GetOwningNode()->GetGraph();
			const FPinConnectionResponse Response = GraphObj->GetSchema()->CanCreateConnection(StartingPinObj, TargetPinObj);
			
			if (Response.Response == CONNECT_RESPONSE_DISALLOW)
			{
				TSharedPtr<SGraphNode> NodeWidget = TargetPinObj->GetOwningNode()->DEPRECATED_NodeWidget.Pin();
				if (NodeWidget.IsValid())
				{
					NodeWidget->NotifyDisallowedPinConnection(StartingPinObj, TargetPinObj);
				}
			}

			UniqueMessages.AddUnique(Response);
		}
	}
	else if (const UEdGraphNodeDialogueEntry* TargetNodeObj = Cast<UEdGraphNodeDialogueEntry>(GetHoveredNode()))
	{
		TArray<UEdGraphPin*> ValidSourcePins;
		ValidateGraphPinList(ValidSourcePins);
		
		for (const UEdGraphPin* StartingPinObj : ValidSourcePins)
		{
			FPinConnectionResponse Response;			
			FText ResponseText;
			const UEdGraphSchema *Schema = StartingPinObj->GetSchema();
			const UEdGraphPin *TargetPin = TargetNodeObj->GetInputPin();

			if (Schema && TargetPin)
			{
				Response = Schema->CanCreateConnection(StartingPinObj, TargetPin);
				if (Response.Response == CONNECT_RESPONSE_DISALLOW)
				{
					TSharedPtr<SGraphNode> NodeWidget = TargetPin->GetOwningNode()->DEPRECATED_NodeWidget.Pin();
					if (NodeWidget.IsValid())
					{
						NodeWidget->NotifyDisallowedPinConnection(StartingPinObj, TargetPinObj);
					}
				}
			}
			else
			{
				Response = FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, FText::FromString("Not a valid UDialogueEdNode"));
			}

			UniqueMessages.AddUnique(Response);
		}
	}
	else if (const UEdGraph* CurrentHoveredGraph = GetHoveredGraph())
	{
		TArray<UEdGraphPin*> ValidSourcePins;
		ValidateGraphPinList(ValidSourcePins);

		for (UEdGraphPin* StartingPinObj : ValidSourcePins)
		{
			FPinConnectionResponse Response = CurrentHoveredGraph->GetSchema()->CanCreateNewNodes(StartingPinObj);
			if (!Response.Message.IsEmpty())
			{
				UniqueMessages.AddUnique(Response);
			}
		}
	}

	if (UniqueMessages.Num() == 0)
	{
		SetSimpleFeedbackMessage(
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 1
			FAppStyle::GetBrush(TEXT("Graph.ConnectorFeedback.NewNode")),
#else
			FEditorStyle::GetBrush(TEXT("Graph.ConnectorFeedback.NewNode")),
#endif
			FLinearColor::White,
			NSLOCTEXT("GraphEditor.Feedback", "PlaceNewNode", "Place a new node."));
		return;
	}

	const TSharedRef<SVerticalBox> FeedbackBox = SNew(SVerticalBox);
    for (auto ResponseIt = UniqueMessages.CreateConstIterator(); ResponseIt; ++ResponseIt)
    {
    	const FSlateBrush* StatusSymbol = nullptr;
    	switch (ResponseIt->Response)
    	{
    	case CONNECT_RESPONSE_MAKE:
    	case CONNECT_RESPONSE_BREAK_OTHERS_A:
    	case CONNECT_RESPONSE_BREAK_OTHERS_B:
    	case CONNECT_RESPONSE_BREAK_OTHERS_AB:
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 1
    		StatusSymbol = FAppStyle::GetBrush(TEXT("Graph.ConnectorFeedback.OK"));
#else
    		StatusSymbol = FEditorStyle::GetBrush(TEXT("Graph.ConnectorFeedback.OK"));
#endif
    		break;

    	case CONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE:
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 1
    		StatusSymbol = FAppStyle::GetBrush(TEXT("Graph.ConnectorFeedback.ViaCast"));
#else
    		StatusSymbol = FEditorStyle::GetBrush(TEXT("Graph.ConnectorFeedback.ViaCast"));
#endif
    		break;

    	case CONNECT_RESPONSE_DISALLOW:
    	default:
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 1
    		StatusSymbol = FAppStyle::GetBrush(TEXT("Graph.ConnectorFeedback.Error"));
#else
    		StatusSymbol = FEditorStyle::GetBrush(TEXT("Graph.ConnectorFeedback.Error"));
#endif
    		break;
    	}

    	FeedbackBox->AddSlot()
    		.AutoHeight()
    		[
    			SNew(SHorizontalBox)
    			+ SHorizontalBox::Slot()
    			.AutoWidth()
    			.Padding(3.0f)
    			.VAlign(VAlign_Center)
    			[
    				SNew(SImage).Image(StatusSymbol)
    			]
		    + SHorizontalBox::Slot()
    			.AutoWidth()
    			.VAlign(VAlign_Center)
    			[
    				SNew(STextBlock).Text(ResponseIt->Message)
    			]
    		];
    }

    SetFeedbackMessage(FeedbackBox);
}

/**
 * @brief Constructor for creating a new instance of FDialogueDragConnection.
 * @param GraphPanel The graph panel where the drag and drop action is taking place.
 * @param DraggedPins The pins that are being dragged and dropped.
 */
FDialogueDragConnection::FDialogueDragConnection(const TSharedRef<SGraphPanel>& GraphPanel, const FDraggedPinTable& DraggedPins)
	: GraphPanel(GraphPanel) , DraggingPins(DraggedPins) , DecoratorAdjust(FSlateApplication::Get().GetCursorSize())
{
	if (DraggingPins.Num() > 0)
	{
		const UEdGraphPin* PinObj = FDraggedPinTable::TConstIterator(DraggedPins)->GetPinObj(*GraphPanel);
		if (PinObj && PinObj->Direction == EGPD_Input)
		{
			DecoratorAdjust *= FVector2D(-1.0f, 1.0f);
		}
	}

	for (const FGraphPinHandle& DraggedPin : DraggedPins)
	{
		GraphPanel->OnBeginMakingConnection(DraggedPin);
	}
}

/**
 * @brief Called when the pins are dropped onto a pin.
 * @param ScreenPosition The position of the mouse on the screen.
 * @param GraphPosition The position of the mouse on the graph.
 * @return The reply to the drop action.
 */
FReply FDialogueDragConnection::DroppedOnPin(FVector2D ScreenPosition, FVector2D GraphPosition)
{
	TArray<UEdGraphPin*> ValidSourcePins;
	ValidateGraphPinList(ValidSourcePins);

	const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd",
		"GraphEd_CreateConnection", "Create Pin Link"));

	UEdGraphPin* PinB = GetHoveredPin();
	bool bError = false;
	TSet<UEdGraphNode*> NodeList;

	for (UEdGraphPin* PinA : ValidSourcePins)
	{
		if (PinA != nullptr && PinB != nullptr)
		{
			const UEdGraph* MyGraphObj = PinA->GetOwningNode()->GetGraph();
			if (MyGraphObj->GetSchema()->TryCreateConnection(PinA, PinB))
			{
				if (!PinA->IsPendingKill())
				{
					NodeList.Add(PinA->GetOwningNode());
				}
				
				if (!PinB->IsPendingKill())
				{
					NodeList.Add(PinB->GetOwningNode());
				}
			}
		}
		else
		{
			bError = true;
		}
	}

	for (auto It = NodeList.CreateConstIterator(); It; ++It)
	{
		UEdGraphNode* Node = (*It);
		Node->NodeConnectionListChanged();
	}

	if (bError)
	{
		return FReply::Unhandled();
	}

	return FReply::Handled();
}

/**
 * @brief Called when the pins are dropped onto a node.
 * @param ScreenPosition The position of the mouse on the screen.
 * @param GraphPosition The position of the mouse on the graph.
 * @return The reply to the drop action.
 */
FReply FDialogueDragConnection::DroppedOnNode(FVector2D ScreenPosition, FVector2D GraphPosition)
{
	bool bHandledPinDropOnNode = false;
	UEdGraphNode* NodeOver = GetHoveredNode();

	if (NodeOver)
	{
		TArray<UEdGraphPin*> ValidSourcePins;
		ValidateGraphPinList(ValidSourcePins);

		if (ValidSourcePins.Num())
		{
			for (UEdGraphPin* SourcePin : ValidSourcePins)
			{
				FText ResponseText;
				if (SourcePin->GetOwningNode() != NodeOver && SourcePin->GetSchema()->SupportsDropPinOnNode(NodeOver,
						SourcePin->PinType, SourcePin->Direction, ResponseText))
				{
					bHandledPinDropOnNode = true;

					const FName PinName = SourcePin->PinFriendlyName.IsEmpty()
						? SourcePin->PinName
						: *SourcePin->PinFriendlyName.ToString();
					const FScopedTransaction Transaction(SourcePin->Direction == EGPD_Output
						? NSLOCTEXT("UnrealEd", "AddInParam", "Add In Parameter")
						: NSLOCTEXT("UnrealEd", "AddOutParam", "Add Out Parameter"));
					UEdGraphPin* EdGraphPin = NodeOver->GetSchema()->DropPinOnNode(GetHoveredNode(), PinName,
						SourcePin->PinType, SourcePin->Direction);

					if (SourcePin->GetOwningNodeUnchecked() && EdGraphPin)
					{
						SourcePin->Modify();
						EdGraphPin->Modify();
						SourcePin->GetSchema()->TryCreateConnection(SourcePin, EdGraphPin);
					}
				}

				if (!bHandledPinDropOnNode && !ResponseText.IsEmpty())
				{
					bHandledPinDropOnNode = true;
				}
			}
		}
	}
	
	return bHandledPinDropOnNode ? FReply::Handled() : FReply::Unhandled();
}

/**
 * @brief Called when the pins are dropped onto the graph panel.
 * @param Panel The panel where the pins are dropped.
 * @param ScreenPosition The position of the mouse on the screen.
 * @param GraphPosition The position of the mouse on the graph.
 * @param Graph The graph where the pins are dropped.
 * @return The reply to the drop action.
 */
FReply FDialogueDragConnection::DroppedOnPanel(const TSharedRef< SWidget >& Panel,
	FVector2D ScreenPosition, FVector2D GraphPosition, UEdGraph& Graph)
{
	TArray<UEdGraphPin*> PinObjects;
	ValidateGraphPinList(PinObjects);
	const TSharedPtr<SWidget> WidgetToFocus = GraphPanel->SummonContextMenu(ScreenPosition,
		GraphPosition, nullptr, nullptr, PinObjects);

	return WidgetToFocus.IsValid()
		? FReply::Handled().SetUserFocus(WidgetToFocus.ToSharedRef(), EFocusCause::SetDirectly)
		: FReply::Handled();
}

/**
 * @brief Validates the list of pins that are being dragged.
 * @param OutValidPins The list of valid pins.
 */
void FDialogueDragConnection::ValidateGraphPinList(TArray<UEdGraphPin*>& OutValidPins)
{
	OutValidPins.Empty(DraggingPins.Num());
	for (const FGraphPinHandle& PinHandle : DraggingPins)
	{
		if (UEdGraphPin* GraphPin = PinHandle.GetPinObj(*GraphPanel))
		{
			OutValidPins.Add(GraphPin);
		}
	}
}