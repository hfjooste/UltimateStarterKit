// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Input/DragAndDrop.h"
#include "Input/Reply.h"
#include "Widgets/SWidget.h"
#include "GraphEditorDragDropAction.h"
#include "SGraphPin.h"

class SGraphPanel;
class UEdGraph;

/**
 * @brief Represents a drag and drop action for connecting pins in a graph editor
 */
class FDialogueDragConnection : public FGraphEditorDragDropAction
{
public:
	DRAG_DROP_OPERATOR_TYPE(FDragConnection, FGraphEditorDragDropAction)

	/**
	 * @brief A typedef for an array of FGraphPinHandle, representing a table of pins that are being dragged.
	 */
	typedef TArray<FGraphPinHandle> FDraggedPinTable;
	
	/**
	 * @brief Constructor for creating a new instance of FDialogueDragConnection.
	 * @param InGraphPanel The graph panel where the drag and drop action is taking place.
	 * @param InStartingPins The pins that are being dragged and dropped.
	 * @return A shared reference to the new instance of FDialogueDragConnection.
	 */
	static TSharedRef<FDialogueDragConnection> New(const TSharedRef<SGraphPanel>& InGraphPanel,
		const FDraggedPinTable& InStartingPins);

	/**
	 * @brief Called when the pins are dropped onto the graph.
	 * @param bDropWasHandled Whether the drop was handled or not.
	 * @param MouseEvent The mouse event that triggered the drop.
	 */
	virtual void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent) override;

	/**
	 * @brief Called when the hover target changes.
	 */
	virtual void HoverTargetChanged() override;

	/**
	 * @brief Called when the pins are dropped onto a pin.
	 * @param ScreenPosition The position of the mouse on the screen.
	 * @param GraphPosition The position of the mouse on the graph.
	 * @return The reply to the drop action.
	 */
	virtual FReply DroppedOnPin(FVector2D ScreenPosition, FVector2D GraphPosition) override;

	/**
	 * @brief Called when the pins are dropped onto a node.
	 * @param ScreenPosition The position of the mouse on the screen.
	 * @param GraphPosition The position of the mouse on the graph.
	 * @return The reply to the drop action.
	 */
	virtual FReply DroppedOnNode(FVector2D ScreenPosition, FVector2D GraphPosition) override;

	/**
	 * @brief Called when the pins are dropped onto the graph panel.
	 * @param Panel The panel where the pins are dropped.
	 * @param ScreenPosition The position of the mouse on the screen.
	 * @param GraphPosition The position of the mouse on the graph.
	 * @param Graph The graph where the pins are dropped.
	 * @return The reply to the drop action.
	 */
	virtual FReply DroppedOnPanel(const TSharedRef< SWidget >& Panel, FVector2D ScreenPosition,
		FVector2D GraphPosition, UEdGraph& Graph) override;

	/**
	 * @brief Called when the pins are being dragged.
	 * @param DragDropEvent The drag and drop event.
	 */
	virtual void OnDragged(const FDragDropEvent& DragDropEvent) override;

	/**
	 * @brief Validates the list of pins that are being dragged.
	 * @param OutValidPins The list of valid pins.
	 */
	virtual void ValidateGraphPinList(TArray<UEdGraphPin*>& OutValidPins);

protected:
	/**
	 * @brief A typedef for FGraphEditorDragDropAction, which is the parent class of FDialogueDragConnection.
	 */
	typedef FGraphEditorDragDropAction Super;
	
	/**
	 * @brief A shared pointer to the graph panel where the drag and drop action is taking place.
	 */
	TSharedPtr<SGraphPanel> GraphPanel;

	/**
	 * @brief A table of pins that are being dragged.
	 */
	FDraggedPinTable DraggingPins;

	/**
	 * A vector that represents the adjustment of the decorator.
	 */
	FVector2D DecoratorAdjust;

	/**
	 * @brief Constructor for creating a new instance of FDialogueDragConnection.
	 * @param GraphPanel The graph panel where the drag and drop action is taking place.
	 * @param DraggedPins The pins that are being dragged and dropped.
	 */
	FDialogueDragConnection(const TSharedRef<SGraphPanel>& GraphPanel, const FDraggedPinTable& DraggedPins);
};