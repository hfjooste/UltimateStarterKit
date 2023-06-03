// Created by Henry Jooste

#include "AssetSchemaDialogueTransition.h"

#include "EdGraphNodeDialogueTransition.h"
#include "ScopedTransaction.h"
#include "EdGraph/EdGraph.h"
#include "USK/Dialogue/DialogueTransition.h"

/**
 * @brief Default constructor
 */
FAssetSchemaDialogueTransition::FAssetSchemaDialogueTransition() : Template(nullptr){ }

/**
 * @brief Constructor that initializes the node category, menu description, tooltip, and grouping.
 * @param InNodeCategory The category of the node.
 * @param InMenuDesc The description of the node in the menu.
 * @param InToolTip The tooltip for the node.
 * @param InGrouping The grouping of the node.
 */
FAssetSchemaDialogueTransition::FAssetSchemaDialogueTransition(const FText& InNodeCategory, const FText& InMenuDesc,
	const FText& InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping), Template(nullptr) { }

/**
 * @brief Creates a new dialogue transition node and adds it to the graph.
 * @param ParentGraph The graph to add the node to.
 * @param FromPin The pin that the node is connected from.
 * @param Location The location to place the node.
 * @param bSelectNewNode Whether or not to select the new node.
 * @return The new dialogue transition node.
 */
UEdGraphNode* FAssetSchemaDialogueTransition::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin,
	const FVector2D Location, bool bSelectNewNode)
{
	if (!IsValid(Template))
	{
		return nullptr;
	}

	const FScopedTransaction Transaction(FText::FromString("Dialogue Editor: New Edge"));
	ParentGraph->Modify();
	if (FromPin != nullptr)
	{
		FromPin->Modify();
	}

	Template->Rename(nullptr, ParentGraph);
	ParentGraph->AddNode(Template, true, bSelectNewNode);

	Template->CreateNewGuid();
	Template->PostPlacedNewNode();
	Template->AllocateDefaultPins();
	Template->AutowireNewNode(FromPin);

	Template->NodePosX = Location.X;
	Template->NodePosY = Location.Y;

	Template->DialogueEdge->SetFlags(RF_Transactional);
	Template->SetFlags(RF_Transactional);
	return Template;
}

/**
 * @brief Adds any referenced objects to the reference collector.
 * @param Collector The reference collector to add objects to.
 */
void FAssetSchemaDialogueTransition::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);
	Collector.AddReferencedObject(Template);
}