// Created by Henry Jooste

#pragma once

#include "ConnectionDrawingPolicy.h"

/**
 * @brief responsible for drawing connections between nodes in the graph editor
 */
class FConnectionDrawingPolicyDialogue : public FConnectionDrawingPolicy
{
public:
	/**
	 * @brief Constructor for the FConnectionDrawingPolicyDialogue class.
	 * @param InBackLayerID The ID of the back layer for drawing connections.
	 * @param InFrontLayerID The ID of the front layer for drawing connections.
	 * @param ZoomFactor The current zoom factor of the graph editor.
	 * @param InClippingRect The clipping rectangle for the graph editor.
	 * @param InDrawElements The list of draw elements for the graph editor.
	 * @param InGraphObj Pointer to the graph object being edited.
	 */
	FConnectionDrawingPolicyDialogue(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor,
		const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj);

	/**
	 * @brief Determines the wiring style for a connection between two pins.
	 * @param OutputPin The pin that the connection is coming from.
	 * @param InputPin The pin that the connection is going to.
	 * @param Params The connection parameters to be determined.
	 */
	virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;

	/**
	 * @brief Draws the connections between nodes in the graph editor.
	 * @param InPinGeometries The geometries of the pins being connected.
	 * @param ArrangedNodes The arranged nodes in the graph editor.
	 */
	virtual void Draw(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries,
		FArrangedChildren& ArrangedNodes) override;

	/**
	 * @brief Draws a connection spline with an arrowhead at the end.
	 * @param StartGeom The geometry of the pin that the connection is coming from.
	 * @param EndGeom The geometry of the pin that the connection is going to.
	 * @param Params The connection parameters to be used.
	 */
	virtual void DrawSplineWithArrow(const FGeometry& StartGeom, const FGeometry& EndGeom,
		const FConnectionParams& Params) override;

	/**
	 * @brief Draws a connection spline with an arrowhead at the end.
	 * @param StartPoint The starting point of the connection spline.
	 * @param EndPoint The ending point of the connection spline.
	 * @param Params The connection parameters to be used.
	 */
	virtual void DrawSplineWithArrow(const FVector2D& StartPoint, const FVector2D& EndPoint,
		const FConnectionParams& Params) override;

	/**
	 * @brief Draws a preview connector between a pin and a mouse cursor.
	 * @param PinGeometry The geometry of the pin being connected.
	 * @param StartPoint The starting point of the preview connector.
	 * @param EndPoint The ending point of the preview connector.
	 * @param Pin The pin being connected.
	 */
	virtual void DrawPreviewConnector(const FGeometry& PinGeometry, const FVector2D& StartPoint,
		const FVector2D& EndPoint, UEdGraphPin* Pin) override;

	/**
	 * @brief Computes the tangent for a connection spline between two points.
	 * @param Start The starting point of the connection spline.
	 * @param End The ending point of the connection spline.
	 * @return The computed tangent vector.
	 */
	virtual FVector2D ComputeSplineTangent(const FVector2D& Start, const FVector2D& End) const override;

	/**
	 * @brief Determines the geometry of a connection link between two pins.
	 * @param ArrangedNodes The arranged nodes in the graph editor.
	 * @param OutputPinWidget The widget of the pin that the connection is coming from.
	 * @param OutputPin The pin that the connection is coming from.
	 * @param InputPin The pin that the connection is going to.
	 * @param StartWidgetGeometry The geometry of the pin that the connection is coming from.
	 * @param EndWidgetGeometry The geometry of the pin that the connection is going to.
	 */
	virtual void DetermineLinkGeometry(FArrangedChildren& ArrangedNodes, TSharedRef<SWidget>& OutputPinWidget,
		UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FArrangedWidget*& StartWidgetGeometry, FArrangedWidget*& EndWidgetGeometry) override;

protected:
	/**
	 * @brief Pointer to the graph object being edited
	 */
	UEdGraph* GraphObj;

	/**
	 * @brief Map of nodes to their widget IDs
	 */
	TMap<UEdGraphNode*, int32> NodeWidgetMap;
	
	/**
	 * @brief Draws a line with an arrowhead at the end.
	 * @param StartAnchorPoint The starting point of the line.
	 * @param EndAnchorPoint The ending point of the line.
	 * @param Params The connection parameters to be used.
	 */
	void Internal_DrawLineWithArrow(const FVector2D& StartAnchorPoint, const FVector2D& EndAnchorPoint,
		const FConnectionParams& Params);
};
