// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "EdGraphDialogue.generated.h"

class UDialogue;
class UDialogueEntry;
class UDialogueTransition;
class UEdGraphNodeDialogueEntry;
class UEdGraphNodeDialogueTransition;

/**
 * @brief Used to represent a dialogue graph in the editor
 */
UCLASS()
class USKEDITOR_API UEdGraphDialogue : public UEdGraph
{
	GENERATED_BODY()

public:
	/**
	 * @brief Rebuilds the dialogue graph.
	 */
	virtual void RebuildDialogue();

	/**
	 * @brief Returns the dialogue associated with this graph.
	 * @return The dialogue associated with this graph.
	 */
	UDialogue* GetDialogue() const;

	/**
	 * @brief Overrides the Modify function of the parent class to mark the graph as dirty.
	 * @param bAlwaysMarkDirty Whether to always mark the graph as dirty.
	 * @return Whether the graph was modified.
	 */
	virtual bool Modify(bool bAlwaysMarkDirty = true) override;

	/**
	 * @brief Overrides the PostEditUndo function of the parent class to update the graph after an undo operation.
	 */
	virtual void PostEditUndo() override;

	/**
	 * @brief Map of dialogue entries to their corresponding graph nodes.
	 */
	UPROPERTY(Transient)
	TMap<UDialogueEntry*, UEdGraphNodeDialogueEntry*> NodeMap;

	/**
	 * @brief Map of dialogue transitions to their corresponding graph edges.
	 */
	UPROPERTY(Transient)
	TMap<UDialogueTransition*, UEdGraphNodeDialogueTransition*> EdgeMap;

protected:
	/**
	 * @brief Clears the dialogue graph.
	 */
	void ClearDialogue();

	/**
	 * @brief Sorts the dialogue graph starting from the root node.
	 * @param RootNode The root node of the dialogue graph.
	 */
	void SortDialogue(UDialogueEntry* RootNode);
};
