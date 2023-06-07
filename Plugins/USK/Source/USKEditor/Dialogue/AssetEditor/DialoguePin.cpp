// Created by Henry Jooste

#include "DialoguePin.h"

#include "DialogueDragConnection.h"
#include "EditorStyleSet.h"

/**
 * @brief Constructs the SDialoguePin widget.
 * @param InArgs The arguments used to construct the widget.
 * @param InPin The graph pin associated with the widget.
 */
void SDialoguePin::Construct(const FArguments& InArgs, UEdGraphPin* InPin)
{
	this->SetCursor(EMouseCursor::Default);
	bShowLabel = true;

	GraphPinObj = InPin;
	check(GraphPinObj != nullptr);

	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	check(Schema);

	SBorder::Construct(SBorder::FArguments()
		.BorderImage(this, &SDialoguePin::GetPinBorder)
		.BorderBackgroundColor(this, &SDialoguePin::GetPinColor)
		.OnMouseButtonDown(this, &SDialoguePin::OnPinMouseDown)
		.Cursor(this, &SDialoguePin::GetPinCursor)
		.Padding(FMargin(5.0f))
	);
}

/**
 * @brief Returns the color of the pin based on its direction and connection status.
 * @return The color of the pin.
 */
FSlateColor SDialoguePin::GetPinColor() const
{
	return FLinearColor(0.02f, 0.02f, 0.02f);
}

/**
 * @brief Returns the widget used to display the default value of the pin.
 * @return The widget used to display the default value of the pin.
 */
TSharedRef<SWidget> SDialoguePin::GetDefaultValueWidget()
{
	return SNew(STextBlock);
}

/**
 * @brief Returns the border brush for the pin based on its direction and connection status.
 * @return The border brush of the pin.
 */
const FSlateBrush* SDialoguePin::GetPinBorder() const
{
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 1
	return FAppStyle::GetBrush(TEXT("Graph.StateNode.Body"));
#else
	return FEditorStyle::GetBrush(TEXT("Graph.StateNode.Body"));
#endif
}

/**
 * @brief Spawns a drag and drop operation for the pin.
 * @param InGraphPanel The graph panel that the drag and drop operation is being performed on.
 * @param InStartingPins The starting pins for the drag and drop operation.
 * @return The drag and drop operation.
 */
TSharedRef<FDragDropOperation> SDialoguePin::SpawnPinDragEvent(const TSharedRef<SGraphPanel>& InGraphPanel,
	const TArray<TSharedRef<SGraphPin>>& InStartingPins)
{
	FDialogueDragConnection::FDraggedPinTable PinHandles;
	PinHandles.Reserve(InStartingPins.Num());
	for (const TSharedRef<SGraphPin>& PinWidget : InStartingPins)
	{
		PinHandles.Add(PinWidget->GetPinObj());
	}

	return FDialogueDragConnection::New(InGraphPanel, PinHandles);
}