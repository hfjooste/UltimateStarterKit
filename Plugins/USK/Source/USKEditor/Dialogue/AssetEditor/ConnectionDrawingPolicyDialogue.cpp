// Created by Henry Jooste

#include "ConnectionDrawingPolicyDialogue.h"
#include "EdGraphNodeDialogueEntry.h"
#include "EdGraphNodeDialogueTransition.h"

/**
 * @brief Constructor for the FConnectionDrawingPolicyDialogue class.
 * @param InBackLayerID The ID of the back layer for drawing connections.
 * @param InFrontLayerID The ID of the front layer for drawing connections.
 * @param ZoomFactor The current zoom factor of the graph editor.
 * @param InClippingRect The clipping rectangle for the graph editor.
 * @param InDrawElements The list of draw elements for the graph editor.
 * @param InGraphObj Pointer to the graph object being edited.
 */
FConnectionDrawingPolicyDialogue::FConnectionDrawingPolicyDialogue(int32 InBackLayerID, int32 InFrontLayerID,
	float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj)
		: FConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, ZoomFactor, InClippingRect, InDrawElements), GraphObj(InGraphObj) { }

/**
 * @brief Determines the wiring style for a connection between two pins.
 * @param OutputPin The pin that the connection is coming from.
 * @param InputPin The pin that the connection is going to.
 * @param Params The connection parameters to be determined.
 */
void FConnectionDrawingPolicyDialogue::DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params)
{
	Params.AssociatedPin1 = OutputPin;
	Params.AssociatedPin2 = InputPin;
	Params.WireThickness = 1.5f;

	const bool bDeemphasizeUnhoveredPins = HoveredPins.Num() > 0;
	if (bDeemphasizeUnhoveredPins)
	{
		ApplyHoverDeemphasis(OutputPin, InputPin, Params.WireThickness, Params.WireColor);
	}
}

/**
 * @brief Draws the connections between nodes in the graph editor.
 * @param InPinGeometries The geometries of the pins being connected.
 * @param ArrangedNodes The arranged nodes in the graph editor.
 */
void FConnectionDrawingPolicyDialogue::Draw(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries, FArrangedChildren& ArrangedNodes)
{
	NodeWidgetMap.Empty();
	for (int32 NodeIndex = 0; NodeIndex < ArrangedNodes.Num(); ++NodeIndex)
	{
		FArrangedWidget& CurWidget = ArrangedNodes[NodeIndex];
		const TSharedRef<SGraphNode> ChildNode = StaticCastSharedRef<SGraphNode>(CurWidget.Widget);
		NodeWidgetMap.Add(ChildNode->GetNodeObj(), NodeIndex);
	}

	FConnectionDrawingPolicy::Draw(InPinGeometries, ArrangedNodes);
}

/**
 * @brief Draws a preview connector between a pin and a mouse cursor.
 * @param PinGeometry The geometry of the pin being connected.
 * @param StartPoint The starting point of the preview connector.
 * @param EndPoint The ending point of the preview connector.
 * @param Pin The pin being connected.
 */
void FConnectionDrawingPolicyDialogue::DrawPreviewConnector(const FGeometry& PinGeometry, const FVector2D& StartPoint,
	const FVector2D& EndPoint, UEdGraphPin* Pin)
{
	FConnectionParams Params;
	DetermineWiringStyle(Pin, nullptr, /*inout*/ Params);

	if (Pin->Direction == EGPD_Output)
	{
		DrawSplineWithArrow(FGeometryHelper::FindClosestPointOnGeom(PinGeometry, EndPoint), EndPoint, Params);
		return;
	}

	DrawSplineWithArrow(FGeometryHelper::FindClosestPointOnGeom(PinGeometry, StartPoint), StartPoint, Params);
}

/**
 * @brief Draws a connection spline with an arrowhead at the end.
 * @param StartPoint The starting point of the connection spline.
 * @param EndPoint The ending point of the connection spline.
 * @param Params The connection parameters to be used.
 */
void FConnectionDrawingPolicyDialogue::DrawSplineWithArrow(const FVector2D& StartPoint, const FVector2D& EndPoint, const FConnectionParams& Params)
{
	const FVector2D& P0 = Params.bUserFlag1 ? EndPoint : StartPoint;
	const FVector2D& P1 = Params.bUserFlag1 ? StartPoint : EndPoint;
	Internal_DrawLineWithArrow(P0, P1, Params);
}

/**
 * @brief Draws a line with an arrowhead at the end.
 * @param StartAnchorPoint The starting point of the line.
 * @param EndAnchorPoint The ending point of the line.
 * @param Params The connection parameters to be used.
 */
void FConnectionDrawingPolicyDialogue::Internal_DrawLineWithArrow(const FVector2D& StartAnchorPoint, const FVector2D& EndAnchorPoint, const FConnectionParams& Params)
{
	constexpr float LineSeparationAmount = 4.5f;
	const FVector2D DeltaPos = EndAnchorPoint - StartAnchorPoint;
	const FVector2D UnitDelta = DeltaPos.GetSafeNormal();
	const FVector2D Normal = FVector2D(DeltaPos.Y, -DeltaPos.X).GetSafeNormal();

	const FVector2D DirectionBias = Normal * LineSeparationAmount;
	const FVector2D LengthBias = ArrowRadius.X * UnitDelta;
	const FVector2D StartPoint = StartAnchorPoint + DirectionBias + LengthBias;
	const FVector2D EndPoint = EndAnchorPoint + DirectionBias - LengthBias;

	DrawConnection(WireLayerID, StartPoint, EndPoint, Params);
	const FVector2D ArrowDrawPos = EndPoint - ArrowRadius;
	const float AngleInRadians = FMath::Atan2(DeltaPos.Y, DeltaPos.X);

	FSlateDrawElement::MakeRotatedBox(DrawElementsList, ArrowLayerID,
		FPaintGeometry(ArrowDrawPos, ArrowImage->ImageSize * ZoomFactor, ZoomFactor),
		ArrowImage, ESlateDrawEffect::None, AngleInRadians, TOptional<FVector2D>(),
FSlateDrawElement::RelativeToElement, Params.WireColor
	);
}

/**
 * @brief Draws a connection spline with an arrowhead at the end.
 * @param StartGeom The geometry of the pin that the connection is coming from.
 * @param EndGeom The geometry of the pin that the connection is going to.
 * @param Params The connection parameters to be used.
 */
void FConnectionDrawingPolicyDialogue::DrawSplineWithArrow(const FGeometry& StartGeom, const FGeometry& EndGeom, const FConnectionParams& Params)
{
	const FVector2D StartCenter = FGeometryHelper::CenterOf(StartGeom);
	const FVector2D EndCenter = FGeometryHelper::CenterOf(EndGeom);
	const FVector2D SeedPoint = (StartCenter + EndCenter) * 0.5f;

	const FVector2D StartAnchorPoint = FGeometryHelper::FindClosestPointOnGeom(StartGeom, SeedPoint);
	const FVector2D EndAnchorPoint = FGeometryHelper::FindClosestPointOnGeom(EndGeom, SeedPoint);
	DrawSplineWithArrow(StartAnchorPoint, EndAnchorPoint, Params);
}

/**
 * @brief Computes the tangent for a connection spline between two points.
 * @param Start The starting point of the connection spline.
 * @param End The ending point of the connection spline.
 * @return The computed tangent vector.
 */
FVector2D FConnectionDrawingPolicyDialogue::ComputeSplineTangent(const FVector2D& Start, const FVector2D& End) const
{
	return (End - Start).GetSafeNormal();
}

/**
 * @brief Determines the geometry of a connection link between two pins.
 * @param ArrangedNodes The arranged nodes in the graph editor.
 * @param OutputPinWidget The widget of the pin that the connection is coming from.
 * @param OutputPin The pin that the connection is coming from.
 * @param InputPin The pin that the connection is going to.
 * @param StartWidgetGeometry The geometry of the pin that the connection is coming from.
 * @param EndWidgetGeometry The geometry of the pin that the connection is going to.
 */
void FConnectionDrawingPolicyDialogue::DetermineLinkGeometry(FArrangedChildren& ArrangedNodes, TSharedRef<SWidget>& OutputPinWidget,
	UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FArrangedWidget*& StartWidgetGeometry, FArrangedWidget*& EndWidgetGeometry)
{
	if (UEdGraphNodeDialogueTransition* EdgeNode = Cast<UEdGraphNodeDialogueTransition>(InputPin->GetOwningNode()))
	{
		const UEdGraphNodeDialogueEntry* Start = EdgeNode->GetStartNode();
		const UEdGraphNodeDialogueEntry* End = EdgeNode->GetEndNode();
		if (Start != nullptr && End != nullptr)
		{
			const int32* StartNodeIndex = NodeWidgetMap.Find(Start);
			const int32* EndNodeIndex = NodeWidgetMap.Find(End);
			if (StartNodeIndex != nullptr && EndNodeIndex != nullptr)
			{
				StartWidgetGeometry = &(ArrangedNodes[*StartNodeIndex]);
				EndWidgetGeometry = &(ArrangedNodes[*EndNodeIndex]);
			}
		}
	}
	else
	{
		StartWidgetGeometry = PinGeometries->Find(OutputPinWidget);
		if (const TSharedPtr<SGraphPin>* pTargetWidget = PinToPinWidgetMap.Find(InputPin))
		{
			const TSharedRef<SGraphPin> InputWidget = (*pTargetWidget).ToSharedRef();
			EndWidgetGeometry = PinGeometries->Find(InputWidget);
		}
	}
}

