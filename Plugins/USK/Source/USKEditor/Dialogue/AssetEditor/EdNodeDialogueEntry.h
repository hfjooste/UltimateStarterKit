// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"

class UEdGraphNodeDialogueEntry;

/**
 * @brief SEdNodeDialogueEntry is a Slate widget that represents a single node in the Dialogue Editor graph.
 */
class USKEDITOR_API SEdNodeDialogueEntry : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SEdNodeDialogueEntry) {}
	SLATE_END_ARGS()
	
	/**
	 * @brief Constructs the SEdNodeDialogueEntry widget.
	 * @param InArgs The Slate arguments for the widget.
	 * @param InNode The UEdGraphNodeDialogueEntry instance that this widget represents.
	 */
	void Construct(const FArguments& InArgs, UEdGraphNodeDialogueEntry* InNode);

	/**
	 * @brief Gets the maximum width at which text should wrap.
	 * @return The maximum width at which text should wrap.
	 */
	float GetWrapTextAt() const;

	/**
	 * @brief Updates the appearance of the node based on its current state.
	 */
	virtual void UpdateGraphNode() override;

	/**
	 * @brief Creates the pin widgets for this node.
	 */
	virtual void CreatePinWidgets() override;

	/**
	 * @brief Adds a pin widget to this node.
	 * @param PinToAdd The pin widget to add.
	 */
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;

	/**
	 * @brief Determines whether the node name is read-only.
	 * @return True if the node name is read-only, false otherwise.
	 */
	virtual bool IsNameReadOnly() const override;

	/**
	 * @brief Called when the node name text has been committed.
	 * @param InText The new text for the node name.
	 * @param CommitInfo The type of text commit that occurred.
	 */
	void OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo);

	/**
	 * @brief Gets the background color of the node's border.
	 * @return The background color of the node's border.
	 */
	virtual FSlateColor GetBorderBackgroundColor() const;

	/**
	 * @brief Gets the background color of the node.
	 * @return The background color of the node.
	 */
	virtual FSlateColor GetBackgroundColor() const;

	/**
	 * @brief Gets the visibility of the drag over marker.
	 * @return The visibility of the drag over marker.
	 */
	virtual EVisibility GetDragOverMarkerVisibility() const;

	/**
	 * @brief Gets the icon to display next to the node name.
	 * @return The icon to display next to the node name.
	 */
	virtual const FSlateBrush* GetNameIcon() const;
};