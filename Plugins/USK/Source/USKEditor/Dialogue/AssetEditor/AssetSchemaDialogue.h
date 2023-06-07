// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "AssetSchemaDialogue.generated.h"

/**
 * @brief Pprovides additional functionality for the schema of the dialogue asset editor.
 */
UCLASS(MinimalAPI)
class UAssetSchemaDialogue : public UEdGraphSchema
{
	GENERATED_BODY()

public:
	/**
	 * @brief Adds the actions to break a link to a submenu
	 * @param Menu The menu to add the actions to
	 * @param InGraphPin The pin to break the link to
	 */
	void GetBreakLinkToSubMenuActions(UToolMenu* Menu, UEdGraphPin* InGraphPin);

	/**
	 * @brief Gets the type of graph
	 * @param TestEdGraph A reference to the test graph
	 * @return The type of graph
	 */
	virtual EGraphType GetGraphType(const UEdGraph* TestEdGraph) const override;

	/**
	 * @brief Gets the context menu actions for the graph
	 * @param ContextMenuBuilder The builder used to build the context menu
	 */
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;

	/**
	 * @brief Gets the context menu actions for the graph node
	 * @param Menu The menu to add the actions to
	 * @param Context The builder used to build the context menu
	 */
	virtual void GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;

	/**
	 * @brief Determines if a connection can be created between two pins
	 * @param A The first pin
	 * @param B The second pin
	 * @return The response to the connection creation
	 */
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;

	/**
	 * @brief Attempts to create a connection between two pins
	 * @param A The first pin
	 * @param B The second pin
	 * @return True if the connection was created, false otherwise
	 */
	virtual bool TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const override;

	/**
	 * @brief Creates an automatic conversion node and connections between two pins
	 * @param A The first pin
	 * @param B The second pin
	 * @return True if the conversion node and connections were created, false otherwise
	 */
	virtual bool CreateAutomaticConversionNodeAndConnections(UEdGraphPin* A, UEdGraphPin* B) const override;

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
	virtual FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) const override;

	/**
	 * @brief Gets the color of a pin type
	 * @param PinType The pin type
	 * @return The color of the pin type
	 */
	virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;

	/**
	 * @brief Breaks all links to a node
	 * @param TargetNode The node to break links to
	 */
	virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;

	/**
	 * @brief Breaks all links to a pin
	 * @param TargetPin The pin to break links to
	 * @param bSendsNodeNotification Whether or not to send a node notification
	 */
	virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotification) const override;

	/**
	 * @brief Breaks a single link between two pins
	 * @param SourcePin The source pin
	 * @param TargetPin The target pin
	 */
	virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;

	/**
	 * @brief Drops a pin on a node
	 * @param InTargetNode The target node
	 * @param InSourcePinName The name of the source pin
	 * @param InSourcePinType The type of the source pin
	 * @param InSourcePinDirection The direction of the source pin
	 * @return The pin that was dropped on the node
	 */
	virtual UEdGraphPin* DropPinOnNode(UEdGraphNode* InTargetNode, const FName& InSourcePinName, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection) const override;

	/**
	 * @brief Determines if a pin can be dropped on a node
	 * @param InTargetNode The target node
	 * @param InSourcePinType The type of the source pin
	 * @param InSourcePinDirection The direction of the source pin
	 * @param OutErrorMessage The error message to display if the pin cannot be dropped
	 * @return True if the pin can be dropped, false otherwise
	 */
	virtual bool SupportsDropPinOnNode(UEdGraphNode* InTargetNode, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection, FText& OutErrorMessage) const override;

	/**
	 * @brief Determines if the visualization cache is out of date
	 * @param InVisualizationCacheID The ID of the visualization cache
	 * @return True if the cache is out of date, false otherwise
	 */
	virtual bool IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const override;

	/**
	 * @brief Gets the current visualization cache ID
	 * @return The current visualization cache ID
	 */
	virtual int32 GetCurrentVisualizationCacheID() const override;

	/**
	 * @brief Forces the visualization cache to clear
	 */
	virtual void ForceVisualizationCacheClear() const override;

private:
	/**
	 * @brief A static integer variable used to keep track of the current cache refresh ID
	 */
	static int32 CurrentCacheRefreshID;
};
