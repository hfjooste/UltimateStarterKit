// Created by Henry Jooste

#include "AssetSchemaDialogue.h"

#include "AssetSchemaDialogueEntry.h"
#include "AssetSchemaDialogueTransition.h"
#include "ToolMenus.h"
#include "EdGraphNodeDialogueEntry.h"
#include "EdGraphNodeDialogueTransition.h"
#include "ConnectionDrawingPolicyDialogue.h"
#include "GraphEditorActions.h"
#include "NodeVisitorCycleChecker.h"
#include "Framework/Commands/GenericCommands.h"
#include "USK/Dialogue/Dialogue.h"
#include "USK/Dialogue/DialogueTransition.h"

int32 UAssetSchemaDialogue::CurrentCacheRefreshID = 0;

/**
 * @brief Adds the actions to break a link to a submenu
 * @param Menu The menu to add the actions to
 * @param InGraphPin The pin to break the link to
 */
void UAssetSchemaDialogue::GetBreakLinkToSubMenuActions(UToolMenu* Menu, UEdGraphPin* InGraphPin)
{
	TMap< FString, uint32 > LinkTitleCount;
	FToolMenuSection& Section = Menu->FindOrAddSection("DialogueAssetGraphSchemaPinActions");
	
	for (TArray<UEdGraphPin*>::TConstIterator Links(InGraphPin->LinkedTo); Links; ++Links)
	{
		const UEdGraphPin* Pin = *Links;
		FString TitleString = Pin->GetOwningNode()->GetNodeTitle(ENodeTitleType::ListView).ToString();
		FText Title = FText::FromString(TitleString);
		if (Pin->PinName != TEXT(""))
		{
			TitleString = FString::Printf(TEXT("%s (%s)"), *TitleString, *Pin->PinName.ToString());
			FFormatNamedArguments Args;
			Args.Add(TEXT("NodeTitle"), Title);
			Args.Add(TEXT("PinName"), Pin->GetDisplayName());
			Title = FText::Format(FText::FromString("{NodeTitle} ({PinName})"), Args);
		}

		uint32& Count = LinkTitleCount.FindOrAdd(TitleString);

		FText Description;
		FFormatNamedArguments Args;
		Args.Add(TEXT("NodeTitle"), Title);
		Args.Add(TEXT("NumberOfNodes"), Count);
		Description = Count == 0
			? FText::Format(FText::FromString("Break link to {NodeTitle}"), Args)
			: FText::Format(FText::FromString("Break link to {NodeTitle} ({NumberOfNodes})"), Args);
		++Count;

		Section.AddMenuEntry(NAME_None, Description, Description, FSlateIcon(), FUIAction(
			FExecuteAction::CreateUObject(this, &UAssetSchemaDialogue::BreakSinglePinLink, InGraphPin, *Links)));
	}
}

/**
 * @brief Gets the type of graph
 * @param TestEdGraph A reference to the test graph
 * @return The type of graph
 */
EGraphType UAssetSchemaDialogue::GetGraphType(const UEdGraph* TestEdGraph) const
{
	return GT_StateMachine;
}

/**
 * @brief Gets the context menu actions for the graph
 * @param ContextMenuBuilder The builder used to build the context menu
 */
void UAssetSchemaDialogue::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	UDialogue* Dialogue = CastChecked<UDialogue>(ContextMenuBuilder.CurrentGraph->GetOuter());
	const FText AddToolTip = FText::FromString("Add node here");
	TSet<TSubclassOf<UDialogueEntry> > Visited;

	FString Title = UDialogueEntry::StaticClass()->GetName();
	Title.RemoveFromEnd("_C");
	FText Desc = FText::FromString(Title);

	if (!UDialogueEntry::StaticClass()->HasAnyClassFlags(CLASS_Abstract))
	{
		const TSharedPtr<FAssetSchemaDialogueEntry> NewNodeAction(new FAssetSchemaDialogueEntry(
			FText::FromString("Dialogue Node"), Desc, AddToolTip, 0));
		NewNodeAction->Template = NewObject<UEdGraphNodeDialogueEntry>(ContextMenuBuilder.OwnerOfTemporaries);
		NewNodeAction->Template->DialogueNode = NewObject<UDialogueEntry>(
			NewNodeAction->Template, UDialogueEntry::StaticClass());
		NewNodeAction->Template->DialogueNode->Dialogue = Dialogue;
		ContextMenuBuilder.AddAction(NewNodeAction);
		Visited.Add(UDialogueEntry::StaticClass());
	}

	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (It->IsChildOf(UDialogueEntry::StaticClass()) &&
			!It->HasAnyClassFlags(CLASS_Abstract) && !Visited.Contains(*It))
		{
			TSubclassOf<UDialogueEntry> NodeType = *It;
			if (It->GetName().StartsWith("REINST") || It->GetName().StartsWith("SKEL"))
			{
				continue;
			}

			Title = NodeType->GetName();
			Title.RemoveFromEnd("_C");
			Desc = FText::FromString(Title);

			TSharedPtr<FAssetSchemaDialogueEntry> Action(new FAssetSchemaDialogueEntry(FText::FromString("Dialogue Entry"), Desc, AddToolTip, 0));
			Action->Template = NewObject<UEdGraphNodeDialogueEntry>(ContextMenuBuilder.OwnerOfTemporaries);
			Action->Template->DialogueNode = NewObject<UDialogueEntry>(Action->Template, NodeType);
			Action->Template->DialogueNode->Dialogue = Dialogue;
			ContextMenuBuilder.AddAction(Action);

			Visited.Add(NodeType);
		}
	}
}

/**
 * @brief Gets the context menu actions for the graph node
 * @param Menu The menu to add the actions to
 * @param Context The builder used to build the context menu
 */
void UAssetSchemaDialogue::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	if (Context->Pin)
	{
		FToolMenuSection& Section = Menu->AddSection("DialogueAssetGraphSchemaNodeActions",
			FText::FromString("Pin Actions"));
		if (Context->Pin->LinkedTo.Num() > 0)
		{
			Section.AddMenuEntry(FGraphEditorCommands::Get().BreakPinLinks);
			if (Context->Pin->LinkedTo.Num() > 1)
			{
				Section.AddSubMenu(
					"BreakLinkTo",
					FText::FromString("Break Link To..."),
					FText::FromString("Break a specific link..."),
					FNewToolMenuDelegate::CreateUObject(const_cast<UAssetSchemaDialogue* const>(this),
						&UAssetSchemaDialogue::GetBreakLinkToSubMenuActions, const_cast<UEdGraphPin*>(Context->Pin)));
			}
			else
			{
				const_cast<UAssetSchemaDialogue* const>(this)->GetBreakLinkToSubMenuActions(
					Menu, const_cast<UEdGraphPin*>(Context->Pin));
			}
		}
	}
	else if (Context->Node)
	{
		FToolMenuSection& Section = Menu->AddSection("DialogueAssetGraphSchemaNodeActions",
			FText::FromString("Node Actions"));
		Section.AddMenuEntry(FGenericCommands::Get().Delete);
		Section.AddMenuEntry(FGenericCommands::Get().Cut);
		Section.AddMenuEntry(FGenericCommands::Get().Copy);
		Section.AddMenuEntry(FGenericCommands::Get().Duplicate);

		Section.AddMenuEntry(FGraphEditorCommands::Get().BreakNodeLinks);
	}

	Super::GetContextMenuActions(Menu, Context);
}

/**
 * @brief Determines if a connection can be created between two pins
 * @param A The first pin
 * @param B The second pin
 * @return The response to the connection creation
 */
const FPinConnectionResponse UAssetSchemaDialogue::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	if (A->GetOwningNode() == B->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW,
			FText::FromString("Can't connect node to itself"));
	}

	const UEdGraphPin *Out = A;
	const UEdGraphPin *In = B;
	const UEdGraphNodeDialogueEntry* EdNode_Out = Cast<UEdGraphNodeDialogueEntry>(Out->GetOwningNode());
	const UEdGraphNodeDialogueEntry* EdNode_In = Cast<UEdGraphNodeDialogueEntry>(In->GetOwningNode());

	if (EdNode_Out == nullptr || EdNode_In == nullptr)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW,
			FText::FromString("Not a valid UDialogueEdNode"));
	}

	FNodeVisitorCycleChecker CycleChecker;
	if (!CycleChecker.CheckForLoop(Out->GetOwningNode(), In->GetOwningNode()))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW,
			FText::FromString("Can't create a graph cycle"));
	}	

	if (EdNode_Out->DialogueNode->Transition == EDialogueTransitionType::Auto &&
		EdNode_Out->GetOutputPin()->LinkedTo.Num() > 0)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW,
			FText::FromString("Auto dialogue advancement only supports a single child node"));
	}

	if (EdNode_Out->DialogueNode->Transition == EDialogueTransitionType::Auto &&
		EdNode_In->GetInputPin()->LinkedTo.Num() > 0)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW,
			FText::FromString("Auto dialogue advancement only supports a single child node"));
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE,
		FText::FromString("Connect nodes with edge"));
}

/**
 * @brief Attempts to create a connection between two pins
 * @param A The first pin
 * @param B The second pin
 * @return True if the connection was created, false otherwise
 */
bool UAssetSchemaDialogue::TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const
{
	const UEdGraphNodeDialogueEntry* NodeA = Cast<UEdGraphNodeDialogueEntry>(A->GetOwningNode());
	const UEdGraphNodeDialogueEntry* NodeB = Cast<UEdGraphNodeDialogueEntry>(B->GetOwningNode());
	for (const UEdGraphPin *TestPin : NodeA->GetOutputPin()->LinkedTo)
	{
		UEdGraphNode* ChildNode = TestPin->GetOwningNode();
		if (UEdGraphNodeDialogueTransition* EdNode_Edge = Cast<UEdGraphNodeDialogueTransition>(ChildNode))
		{
			ChildNode = EdNode_Edge->GetEndNode();
		}

		if (ChildNode == NodeB)
		{
			return false;
		}
	}

	if (NodeA && NodeB)
	{
		Super::TryCreateConnection(NodeA->GetOutputPin(), NodeB->GetInputPin());
		return true;
	}

	return false;
}

/**
 * @brief Creates an automatic conversion node and connections between two pins
 * @param A The first pin
 * @param B The second pin
 * @return True if the conversion node and connections were created, false otherwise
 */
bool UAssetSchemaDialogue::CreateAutomaticConversionNodeAndConnections(UEdGraphPin* A, UEdGraphPin* B) const
{
	UEdGraphNodeDialogueEntry* NodeA = Cast<UEdGraphNodeDialogueEntry>(A->GetOwningNode());
	UEdGraphNodeDialogueEntry* NodeB = Cast<UEdGraphNodeDialogueEntry>(B->GetOwningNode());
	if (!NodeA || !NodeA->GetOutputPin() || !NodeB || !NodeB->GetInputPin())
	{
		return false;
	}

	const FVector2D InitPos((NodeA->NodePosX + NodeB->NodePosX) / 2, (NodeA->NodePosY + NodeB->NodePosY) / 2);
	FAssetSchemaDialogueTransition Action;
	Action.Template = NewObject<UEdGraphNodeDialogueTransition>(NodeA->GetGraph());
	Action.Template->SetEdge(NewObject<UDialogueTransition>(Action.Template,
		UDialogueTransition::StaticClass()));
	UEdGraphNodeDialogueTransition* EdgeNode = Cast<UEdGraphNodeDialogueTransition>(
		Action.PerformAction(NodeA->GetGraph(), nullptr, InitPos, false));

	EdgeNode->CreateConnections(NodeA, NodeB);
	NodeA->DialogueNode->Edges.Add(NodeB->DialogueNode, EdgeNode->DialogueEdge);
	return true;
}

/**
 * @brief Creates a connection drawing policy for the graph
 * @param InBackLayerID The ID of the back layer
 * @param InFrontLayerID The ID of the front layer
 * @param InZoomFactor The zoom factor
 * @param InClippingRect The clipping rectangle
 * @param InDrawElements The list of draw elements
 * @param InGraphObj The graph object
 * @return The connection drawing policy
 */
FConnectionDrawingPolicy* UAssetSchemaDialogue::CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID,
	float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) const
{
	return new FConnectionDrawingPolicyDialogue(InBackLayerID, InFrontLayerID, InZoomFactor,
		InClippingRect, InDrawElements, InGraphObj);
}

/**
 * @brief Gets the color of a pin type
 * @param PinType The pin type
 * @return The color of the pin type
 */
FLinearColor UAssetSchemaDialogue::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return FColor::White;
}

/**
 * @brief Breaks all links to a node
 * @param TargetNode The node to break links to
 */
void UAssetSchemaDialogue::BreakNodeLinks(UEdGraphNode& TargetNode) const
{
	const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd",
		"GraphEd_BreakNodeLinks", "Break Node Links"));
	Super::BreakNodeLinks(TargetNode);
}

/**
 * @brief Breaks all links to a pin
 * @param TargetPin The pin to break links to
 * @param bSendsNodeNotification Whether or not to send a node notification
 */
void UAssetSchemaDialogue::BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotification) const
{
	const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd",
		"GraphEd_BreakPinLinks", "Break Pin Links"));
	Super::BreakPinLinks(TargetPin, bSendsNodeNotification);
}

/**
 * @brief Breaks a single link between two pins
 * @param SourcePin The source pin
 * @param TargetPin The target pin
 */
void UAssetSchemaDialogue::BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const
{
	const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd",
		"GraphEd_BreakSinglePinLink", "Break Pin Link"));
	Super::BreakSinglePinLink(SourcePin, TargetPin);
}

/**
 * @brief Drops a pin on a node
 * @param InTargetNode The target node
 * @param InSourcePinName The name of the source pin
 * @param InSourcePinType The type of the source pin
 * @param InSourcePinDirection The direction of the source pin
 * @return The pin that was dropped on the node
 */
UEdGraphPin* UAssetSchemaDialogue::DropPinOnNode(UEdGraphNode* InTargetNode, const FName& InSourcePinName,
	const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection) const
{
	const UEdGraphNodeDialogueEntry* EdNode = Cast<UEdGraphNodeDialogueEntry>(InTargetNode);
	switch (InSourcePinDirection)
	{
	case EGPD_Input:
		return EdNode->GetOutputPin();
	case EGPD_Output:
		return EdNode->GetInputPin();
	default:
		return nullptr;
	}
}

/**
 * @brief Determines if a pin can be dropped on a node
 * @param InTargetNode The target node
 * @param InSourcePinType The type of the source pin
 * @param InSourcePinDirection The direction of the source pin
 * @param OutErrorMessage The error message to display if the pin cannot be dropped
 * @return True if the pin can be dropped, false otherwise
 */
bool UAssetSchemaDialogue::SupportsDropPinOnNode(UEdGraphNode* InTargetNode, const FEdGraphPinType& InSourcePinType,
	EEdGraphPinDirection InSourcePinDirection, FText& OutErrorMessage) const
{
	return Cast<UEdGraphNodeDialogueEntry>(InTargetNode) != nullptr;
}

/**
 * @brief Determines if the visualization cache is out of date
 * @param InVisualizationCacheID The ID of the visualization cache
 * @return True if the cache is out of date, false otherwise
 */
bool UAssetSchemaDialogue::IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const
{
	return CurrentCacheRefreshID != InVisualizationCacheID;
}

/**
 * @brief Gets the current visualization cache ID
 * @return The current visualization cache ID
 */
int32 UAssetSchemaDialogue::GetCurrentVisualizationCacheID() const
{
	return CurrentCacheRefreshID;
}

/**
 * @brief Forces the visualization cache to clear
 */
void UAssetSchemaDialogue::ForceVisualizationCacheClear() const
{
	++CurrentCacheRefreshID;
}
