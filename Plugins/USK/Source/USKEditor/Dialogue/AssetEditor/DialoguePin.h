// Created by Henry Jooste

#pragma once

#include "SGraphPin.h"

/**
 * @brief Represents a pin in the dialogue graph editor.
 */
class SDialoguePin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialoguePin) {}
	SLATE_END_ARGS()

	/**
	 * @brief Constructs the SDialoguePin widget.
	 * @param InArgs The arguments used to construct the widget.
	 * @param InPin The graph pin associated with the widget.
	 */
	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);

protected:
	/**
	 * @brief Returns the color of the pin based on its direction and connection status.
	 * @return The color of the pin.
	 */
	virtual FSlateColor GetPinColor() const override;

	/**
	 * @brief Returns the widget used to display the default value of the pin.
	 * @return The widget used to display the default value of the pin.
	 */
	virtual TSharedRef<SWidget> GetDefaultValueWidget() override;
	
	/**
	 * @brief Returns the border brush for the pin based on its direction and connection status.
	 * @return The border brush of the pin.
	 */
	const FSlateBrush* GetPinBorder() const;
	
	/**
	 * @brief Spawns a drag and drop operation for the pin.
	 * @param InGraphPanel The graph panel that the drag and drop operation is being performed on.
	 * @param InStartingPins The starting pins for the drag and drop operation.
	 * @return The drag and drop operation.
	 */
	virtual TSharedRef<FDragDropOperation> SpawnPinDragEvent(const TSharedRef<SGraphPanel>& InGraphPanel,
		const TArray<TSharedRef<SGraphPin>>& InStartingPins) override;
};