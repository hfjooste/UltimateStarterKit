// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraphNodeDialogueTransition.generated.h"

class UDialogueEntry;
class UDialogueTransition;
class UEdGraphNodeDialogueEntry;

/**
 * @brief Represents a node in the dialogue graph that represents a transition between two dialogue entries
 */
UCLASS(MinimalAPI)
class UEdGraphNodeDialogueTransition : public UEdGraphNode
{
	GENERATED_BODY()

public:
	/**
	 * @brief Pointer to the graph that owns this node.
	 */
	UPROPERTY()
	UEdGraph* Graph;

	/**
	 * @brief The dialogue transition asset that this node represents.
	 */
	UPROPERTY(VisibleAnywhere, Instanced, Category = "Dialogue")
	UDialogueTransition* DialogueEdge;
	
	/**
	 * @brief Constructor for UEdGraphNodeDialogueTransition class.
	 */
	UEdGraphNodeDialogueTransition();

	/**
	 * @brief Sets the dialogue transition asset that this node represents.
	 * @param Edge The dialogue transition asset.
	 */
	void SetEdge(UDialogueTransition* Edge);

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
	 * @brief Called when the connection list of a pin is changed.
	 * @param Pin The pin whose connection list was changed.
	 */
	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;

	/**
	 * @brief Prepares this node for copying.
	 */
	virtual void PrepareForCopying() override;

	/**
	 * @brief Gets the input pin of this node.
	 * @return The input pin of this node.
	 */
	virtual UEdGraphPin* GetInputPin() const { return Pins[0]; }

	/**
	 * @brief Gets the output pin of this node.
	 * @return The output pin of this node.
	 */
	virtual UEdGraphPin* GetOutputPin() const { return Pins[1]; }

	/**
	 * @brief Creates connections between the start and end nodes.
	 * @param Start The start node.
	 * @param End The end node.
	 */
	void CreateConnections(UEdGraphNodeDialogueEntry* Start, UEdGraphNodeDialogueEntry* End);

	/**
	 * @brief Gets the start node of this transition.
	 * @return The start node of this transition.
	 */
	UEdGraphNodeDialogueEntry* GetStartNode();

	/**
	 * @brief Gets the end node of this transition.
	 * @return The end node of this transition.
	 */
	UEdGraphNodeDialogueEntry* GetEndNode();

	/**
	 * @brief Destroys this node.
	 */
	UFUNCTION()
	void Destroy();
};