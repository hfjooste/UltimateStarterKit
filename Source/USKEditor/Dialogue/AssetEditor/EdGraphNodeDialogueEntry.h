// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "USK/Dialogue/DialogueEntry.h"
#include "EdGraphNodeDialogueEntry.generated.h"

class SEdNodeDialogueEntry;
class UEdGraphNodeDialogueTransition;
class UEdGraphDialogue;

/**
 * @brief Represents a node in the Dialogue editor graph
 */
UCLASS(MinimalAPI)
class UEdGraphNodeDialogueEntry : public UEdGraphNode
{
	GENERATED_BODY()

public:
	/**
	 * @brief The DialogueNode instance associated with this node.
	 */
	UPROPERTY(VisibleAnywhere, Instanced, Category = "Dialogue")
	UDialogueEntry* DialogueNode;
	
	/**
	 * @brief Constructor for UEdGraphNodeDialogueEntry.
	 */
	UEdGraphNodeDialogueEntry();

	/**
	 * @brief Sets the DialogueNode instance associated with this node.
	 * @param InNode The DialogueNode instance to set.
	 */
	void SetDialogueNode(UDialogueEntry* InNode);

	/**
	 * @brief Gets the UEdGraphDialogue instance associated with this node.
	 * @return The UEdGraphDialogue instance associated with this node.
	 */
	UEdGraphDialogue* GetDialogueEdGraph() const;

	/**
	 * @brief The SEdNodeDialogueEntry instance associated with this node.
	 */
	SEdNodeDialogueEntry* SEdNode;

	/**
	 * @brief Allocates default input/output pins for this node.
	 */
	virtual void AllocateDefaultPins() override;

	/**
	 * @brief Gets the title of this node.
	 * @param TitleType The type of title to get.
	 * @return The title of this node.
	 */
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	/**
	 * @brief Prepares this node for copying.
	 */
	virtual void PrepareForCopying() override;

	/**
	 * @brief Auto-wires a new node to this node.
	 * @param FromPin The pin to auto-wire from.
	 */
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;

	/**
	 * @brief Gets the background color of this node.
	 * @return The background color of this node.
	 */
	virtual FLinearColor GetBackgroundColor() const;

	/**
	 * @brief Gets the input pin of this node.
	 * @return The input pin of this node.
	 */
	virtual UEdGraphPin* GetInputPin() const;

	/**
	 * @brief Gets the output pin of this node.
	 * @return The output pin of this node.
	 */
	virtual UEdGraphPin* GetOutputPin() const;

#if WITH_EDITOR
	/**
	 * @brief Overrides the PostEditUndo function to handle undo/redo operations.
	 */
	virtual void PostEditUndo() override;
#endif
};
