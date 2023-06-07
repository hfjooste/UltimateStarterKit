// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateColor.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"
#include "SNodePanel.h"
#include "SGraphNode.h"

class SToolTip;
class UEdGraphNodeDialogueTransition;

/**
 * @brief Widget for displaying and editing a dialogue transition node in the graph editor.
 */
class USKEDITOR_API SEdNodeDialogueTransition : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SEdNodeDialogueTransition){}
	SLATE_END_ARGS()

	/**
	 * @brief Constructs the widget.
	 * @param InArgs The slate arguments.
	 * @param InNode The dialogue transition node to display and edit.
	 */
	void Construct(const FArguments& InArgs, UEdGraphNodeDialogueTransition* InNode);

	/**
	 * @brief Determines if a second pass of layout is required.
	 * @return True if a second pass of layout is required, false otherwise.
	 */
	virtual bool RequiresSecondPassLayout() const override;

	/**
	 * @brief Performs a second pass of layout.
	 * @param NodeToWidgetLookup A map of nodes to their corresponding widgets.
	 */
	virtual void PerformSecondPassLayout(const TMap< UObject*, TSharedRef<SNode> >& NodeToWidgetLookup) const override;

	/**
	 * @brief Updates the graph node.
	 */
	virtual void UpdateGraphNode() override;

	/**
	 * @brief Calculates the position for multiple nodes to be placed between a start and end point.
	 * @param StartGeom The geometry of the start node.
	 * @param EndGeom The geometry of the end node.
	 * @param NodeIndex The index of this node.
	 * @param MaxNodes The maximum number of nodes to position.
	 */
	void PositionBetweenTwoNodesWithOffset(const FGeometry& StartGeom, const FGeometry& EndGeom, int32 NodeIndex, int32 MaxNodes) const;

protected:
	/**
	 * @brief Gets the color of the edge.
	 * @return The color of the edge.
	 */
	FSlateColor GetEdgeColor() const;

	/**
	 * @brief Gets the image of the edge.
	 * @return The image of the edge.
	 */
	const FSlateBrush* GetEdgeImage() const;

	/**
	 * @brief Gets the visibility of the edge image.
	 * @return The visibility of the edge image.
	 */
	EVisibility GetEdgeImageVisibility() const;

	/**
	 * @brief Gets the visibility of the edge title.
	 * @return The visibility of the edge title.
	 */
	EVisibility GetEdgeTitleVisibility() const;

private:
	/**
	 * @brief Widget for editing the transition text.
	 */
	TSharedPtr<STextEntryPopup> TextEntryWidget;
};
