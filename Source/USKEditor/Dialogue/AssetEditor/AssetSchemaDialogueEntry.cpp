// Created by Henry Jooste

#include "AssetSchemaDialogueEntry.h"

#include "EdGraphNodeDialogueEntry.h"
#include "ScopedTransaction.h"
#include "EdGraph/EdGraph.h"

/**
 * @brief Default constructor
 */
FAssetSchemaDialogueEntry::FAssetSchemaDialogueEntry() : Template(nullptr) { }

/**
 * @brief Constructor with parameters
 * @param InNodeCategory The category of the node
 * @param InMenuDesc The description of the node in the menu
 * @param InToolTip The tooltip of the node
 * @param InGrouping The grouping of the node
 */
FAssetSchemaDialogueEntry::FAssetSchemaDialogueEntry(const FText& InNodeCategory, const FText& InMenuDesc,
	const FText& InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping), Template(nullptr) {}

/**
 * @brief Performs the action of adding a node to the graph
 * @param ParentGraph The graph to add the node to
 * @param FromPin The pin to connect the node from
 * @param Location The location to place the node
 * @param bSelectNewNode Whether to select the new node after adding it
 * @return The new node that was added to the graph
 */
UEdGraphNode* FAssetSchemaDialogueEntry::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin,
	const FVector2D Location, bool bSelectNewNode)
{
	if (!IsValid(Template))
	{
		return nullptr;
	}

	const FScopedTransaction Transaction(FText::FromString("Dialogue Editor: New Node"));
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

	Template->DialogueNode->SetFlags(RF_Transactional);
	Template->SetFlags(RF_Transactional);
	return Template;
}

/**
 * @brief Adds any referenced objects to the reference collector
 * @param Collector The reference collector to add the objects to
 */
void FAssetSchemaDialogueEntry::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);
	Collector.AddReferencedObject(Template);
}