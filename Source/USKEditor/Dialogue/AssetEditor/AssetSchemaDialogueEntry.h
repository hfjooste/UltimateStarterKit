// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "AssetSchemaDialogueEntry.generated.h"

class UEdGraphNodeDialogueEntry;

/**
 * @brief Action to add a node to the graph
 */
USTRUCT()

/**
 * @brief Struct representing an action to add a node to the graph
 */
struct USKEDITOR_API FAssetSchemaDialogueEntry : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

	/**
	 * @brief The template node for this action
	 */
	UPROPERTY()
	UEdGraphNodeDialogueEntry* Template;
	
	/**
	 * @brief Default constructor
	 */
	FAssetSchemaDialogueEntry();

	/**
	 * @brief Constructor with parameters
	 * @param InNodeCategory The category of the node
	 * @param InMenuDesc The description of the node in the menu
	 * @param InToolTip The tooltip of the node
	 * @param InGrouping The grouping of the node
	 */
	FAssetSchemaDialogueEntry(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping);

	/**
	 * @brief Performs the action of adding a node to the graph
	 * @param ParentGraph The graph to add the node to
	 * @param FromPin The pin to connect the node from
	 * @param Location The location to place the node
	 * @param bSelectNewNode Whether to select the new node after adding it
	 * @return The new node that was added to the graph
	 */
	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	
	/**
	 * @brief Adds any referenced objects to the reference collector
	 * @param Collector The reference collector to add the objects to
	 */
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
};

