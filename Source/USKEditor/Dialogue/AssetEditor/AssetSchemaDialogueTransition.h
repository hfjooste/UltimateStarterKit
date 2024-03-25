// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "AssetSchemaDialogueTransition.generated.h"

class UEdGraphNodeDialogueTransition;

/**
 * @brief Struct representing a custom schema action for a dialogue transition node in the asset editor
 */
USTRUCT()
struct USKEDITOR_API FAssetSchemaDialogueTransition : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

	/**
	 * @brief The template node for this schema action
	 */
	UPROPERTY()
	UEdGraphNodeDialogueTransition* Template;

	/**
	 * @brief Default constructor
	 */
	FAssetSchemaDialogueTransition();

	/**
	 * @brief Constructor that initializes the node category, menu description, tooltip, and grouping.
	 * @param InNodeCategory The category of the node.
	 * @param InMenuDesc The description of the node in the menu.
	 * @param InToolTip The tooltip for the node.
	 * @param InGrouping The grouping of the node.
	 */
	FAssetSchemaDialogueTransition(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping);

	/**
	 * @brief Creates a new dialogue transition node and adds it to the graph.
	 * @param ParentGraph The graph to add the node to.
	 * @param FromPin The pin that the node is connected from.
	 * @param Location The location to place the node.
	 * @param bSelectNewNode Whether or not to select the new node.
	 * @return The new dialogue transition node.
	 */
	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	
	/**
	 * @brief Adds any referenced objects to the reference collector.
	 * @param Collector The reference collector to add objects to.
	 */
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
};

