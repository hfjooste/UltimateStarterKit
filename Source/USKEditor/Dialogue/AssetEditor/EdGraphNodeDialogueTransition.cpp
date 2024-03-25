// Created by Henry Jooste

#include "EdGraphNodeDialogueTransition.h"
#include "USK/Dialogue/DialogueTransition.h"
#include "EdGraphNodeDialogueEntry.h"

/**
 * @brief Constructor for UEdGraphNodeDialogueTransition class.
 */
UEdGraphNodeDialogueTransition::UEdGraphNodeDialogueTransition()
{
	bCanRenameNode = true;
}

/**
 * @brief Sets the dialogue transition asset that this node represents.
 * @param Edge The dialogue transition asset.
 */
void UEdGraphNodeDialogueTransition::SetEdge(UDialogueTransition* Edge)
{
	DialogueEdge = Edge;
	if (IsValid(DialogueEdge))
	{
		DialogueEdge->OnMarkedForDeletion.AddDynamic(this, &UEdGraphNodeDialogueTransition::Destroy);	
	}
}

/**
 * @brief Allocates default input/output pins for this node.
 */
void UEdGraphNodeDialogueTransition::AllocateDefaultPins()
{
	UEdGraphPin* Inputs = CreatePin(EGPD_Input, TEXT("Edge"), FName(), TEXT("In"));
	Inputs->bHidden = true;
	
	UEdGraphPin* Outputs = CreatePin(EGPD_Output, TEXT("Edge"), FName(), TEXT("Out"));
	Outputs->bHidden = true;
}

/**
 * @brief Gets the title of this node.
 * @param TitleType The type of title to get.
 * @return The title of this node.
 */
FText UEdGraphNodeDialogueTransition::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (!IsValid(DialogueEdge) || !IsValid(DialogueEdge->StartEntry) ||
		DialogueEdge->StartEntry->Transition != EDialogueTransitionType::Choice) 
	{
		return FText();
	}
	
	return DialogueEdge->Text.IsEmpty() ? FText::FromString("WARNING: Empty Choice") : DialogueEdge->Text;
}

/**
 * @brief Called when the connection list of a pin is changed.
 * @param Pin The pin whose connection list was changed.
 */
void UEdGraphNodeDialogueTransition::PinConnectionListChanged(UEdGraphPin* Pin)
{
	if (Pin->LinkedTo.Num() == 0)
	{
		Modify();
		
		if (UEdGraph* ParentGraph = GetGraph())
		{
			ParentGraph->Modify();
		}

		DestroyNode();
	}
}

/**
 * @brief Prepares this node for copying.
 */
void UEdGraphNodeDialogueTransition::PrepareForCopying()
{
	DialogueEdge->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);
}

/**
 * @brief Creates connections between the start and end nodes.
 * @param Start The start node.
 * @param End The end node.
 */
void UEdGraphNodeDialogueTransition::CreateConnections(UEdGraphNodeDialogueEntry* Start, UEdGraphNodeDialogueEntry* End)
{
	Pins[0]->Modify();
	Pins[0]->LinkedTo.Empty();

	Start->GetOutputPin()->Modify();
	Pins[0]->MakeLinkTo(Start->GetOutputPin());

	Pins[1]->Modify();
	Pins[1]->LinkedTo.Empty();

	End->GetInputPin()->Modify();
	Pins[1]->MakeLinkTo(End->GetInputPin());
}

/**
 * @brief Gets the start node of this transition.
 * @return The start node of this transition.
 */
UEdGraphNodeDialogueEntry* UEdGraphNodeDialogueTransition::GetStartNode()
{
	if (Pins[0]->LinkedTo.Num() > 0)
	{
		return Cast<UEdGraphNodeDialogueEntry>(Pins[0]->LinkedTo[0]->GetOwningNode());
	}

	return nullptr;
}

/**
 * @brief Gets the end node of this transition.
 * @return The end node of this transition.
 */
UEdGraphNodeDialogueEntry* UEdGraphNodeDialogueTransition::GetEndNode()
{
	if (Pins[1]->LinkedTo.Num() > 0)
	{
		return Cast<UEdGraphNodeDialogueEntry>(Pins[1]->LinkedTo[0]->GetOwningNode());
	}

	return nullptr;
}

/**
 * @brief Destroys this node.
 */
void UEdGraphNodeDialogueTransition::Destroy()
{
	Modify();

	if (UEdGraph* ParentGraph = GetGraph())
	{
		ParentGraph->Modify();
	}

	DestroyNode();
}