// Created by Henry Jooste

#include "EdGraphNodeDialogueEntry.h"
#include "EdGraphDialogue.h"
#include "Kismet2/Kismet2NameValidators.h"
#include "USK/Dialogue/DialogueTransition.h"

/**
 * @brief Constructor for UEdGraphNodeDialogueEntry.
 */
UEdGraphNodeDialogueEntry::UEdGraphNodeDialogueEntry()
{
	bCanRenameNode = true;
}

/**
 * @brief Allocates default input/output pins for this node.
 */
void UEdGraphNodeDialogueEntry::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, "MultipleNodes", FName(), TEXT("In"));
	CreatePin(EGPD_Output, "MultipleNodes", FName(), TEXT("Out"));
}

/**
 * @brief Gets the UEdGraphDialogue instance associated with this node.
 * @return The UEdGraphDialogue instance associated with this node.
 */
UEdGraphDialogue* UEdGraphNodeDialogueEntry::GetDialogueEdGraph() const
{
	return Cast<UEdGraphDialogue>(GetGraph());
}

/**
 * @brief Gets the title of this node.
 * @param TitleType The type of title to get.
 * @return The title of this node.
 */
FText UEdGraphNodeDialogueEntry::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (!IsValid(DialogueNode))
	{
		return Super::GetNodeTitle(TitleType);
	}

	return DialogueNode->Text.IsEmpty()
		? FText::FromString("WARNING: Empty Dialogue Entry")
		: DialogueNode->Text;
}

/**
 * @brief Prepares this node for copying.
 */
void UEdGraphNodeDialogueEntry::PrepareForCopying()
{
	DialogueNode->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);
}

/**
 * @brief Auto-wires a new node to this node.
 * @param FromPin The pin to auto-wire from.
 */
void UEdGraphNodeDialogueEntry::AutowireNewNode(UEdGraphPin* FromPin)
{
	Super::AutowireNewNode(FromPin);

	if (FromPin != nullptr)
	{
		if (GetSchema()->TryCreateConnection(FromPin, GetInputPin()))
		{
			FromPin->GetOwningNode()->NodeConnectionListChanged();
		}
	}
}

/**
 * @brief Sets the DialogueNode instance associated with this node.
 * @param InNode The DialogueNode instance to set.
 */
void UEdGraphNodeDialogueEntry::SetDialogueNode(UDialogueEntry* InNode)
{
	DialogueNode = InNode;
}

/**
 * @brief Gets the background color of this node.
 * @return The background color of this node.
 */
FLinearColor UEdGraphNodeDialogueEntry::GetBackgroundColor() const
{
	return !IsValid(DialogueNode) || !IsValid(DialogueNode->Owner)
		? FLinearColor::Black
		: DialogueNode->Owner->Color;
}

/**
 * @brief Gets the input pin of this node.
 * @return The input pin of this node.
 */
UEdGraphPin* UEdGraphNodeDialogueEntry::GetInputPin() const
{
	return Pins[0];
}

/**
 * @brief Gets the output pin of this node.
 * @return The output pin of this node.
 */
UEdGraphPin* UEdGraphNodeDialogueEntry::GetOutputPin() const
{
	return Pins[1];
}

#if WITH_EDITOR
/**
 * @brief Overrides the PostEditUndo function to handle undo/redo operations.
 */
void UEdGraphNodeDialogueEntry::PostEditUndo()
{
	UEdGraphNode::PostEditUndo();
}
#endif