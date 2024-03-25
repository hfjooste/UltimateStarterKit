// Created by Henry Jooste

#include "DialogueNodeFactory.h"
#include <EdGraph/EdGraphNode.h>
#include "AssetEditor/EdNodeDialogueTransition.h"
#include "AssetEditor/EdGraphNodeDialogueEntry.h"
#include "AssetEditor/EdNodeDialogueEntry.h"
#include "AssetEditor/EdGraphNodeDialogueTransition.h"

/**
 * @brief Create a new dialogue node 
 * @param Node A reference to the editor node
 * @return The newly created node
 */
TSharedPtr<SGraphNode> FDialogueEntryFactory::CreateNode(UEdGraphNode* Node) const
{
	UEdGraphNodeDialogueEntry* DialogueEntry = dynamic_cast<UEdGraphNodeDialogueEntry*>(Node);
	if (IsValid(DialogueEntry))
	{
		return SNew(SEdNodeDialogueEntry, DialogueEntry);
	}

	UEdGraphNodeDialogueTransition* DialogueTransition = dynamic_cast<UEdGraphNodeDialogueTransition*>(Node);
	if (IsValid(DialogueTransition))
	{
		return SNew(SEdNodeDialogueTransition, DialogueTransition);
	}

	return nullptr;
}