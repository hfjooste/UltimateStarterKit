// Created by Henry Jooste

#pragma once

#include <EdGraphUtilities.h>
#include <EdGraph/EdGraphNode.h>

/**
 * @brief Factory class used to create new dialogue entries and transitions
 */
class USKEDITOR_API FDialogueEntryFactory : public FGraphPanelNodeFactory
{
	/**
	 * @brief Create a new dialogue node
	 * @param Node A reference to the editor node
	 * @return The newly created node
	 */
	virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* Node) const override;
};