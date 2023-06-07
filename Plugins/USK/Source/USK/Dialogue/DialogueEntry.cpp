// Created by Henry Jooste

#include "DialogueEntry.h"
#include "DialogueTransition.h"
#include "Misc/MessageDialog.h"

/**
 * @brief Check if this entry is a leaf node
 * @return A boolean value indicating if this entry is a leaf node
 */
bool UDialogueEntry::IsLeafNode() const
{
	return ChildrenNodes.Num() == 0;
}

/**
 * @brief Get the title displayed for this dialogue entry
 * @return The title displayed for this dialogue entry
 */
FText UDialogueEntry::GetTitle()
{
	return IsValid(Owner) ? Owner->Name : FText::GetEmpty();
}

/**
 * @brief Get the text displayed for this dialogue entry
 * @return The text displayed for this dialogue entry
 */
FText UDialogueEntry::GetText()
{
	return Text;
}

#if WITH_EDITOR

/**
 * @brief This is called when a property is about to be modified externally
 * @param PropertyAboutToChange The property that is about to be modified
 */
void UDialogueEntry::PreEditChange(FProperty* PropertyAboutToChange)
{
	Super::PreEditChange(PropertyAboutToChange);
	if (PropertyAboutToChange->GetFName() != GET_MEMBER_NAME_CHECKED(UDialogueEntry, Transition) ||
		Edges.Num() == 0)
	{
		return;
	}

	const FString Message = "Are you sure you want to update the transition type? "
					"This will break all connections from the current node";
	if (FMessageDialog::Open(EAppMsgType::YesNo, FText::FromString(Message)) != EAppReturnType::Yes)
	{
		BlockTransitionUpdate = true;
		PreviousTransition = Transition;
	}	
}

/**
 * @brief Called when a property on this object has been modified externally
 * @param PropertyChangedEvent The event containing information about the property that was changed
 */
void UDialogueEntry::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.Property->GetFName() != GET_MEMBER_NAME_CHECKED(UDialogueEntry, Transition) ||
		Edges.Num() == 0)
	{
		return;
	}

	if (!BlockTransitionUpdate)
	{
		TArray<UDialogueTransition*> Transitions;
		Edges.GenerateValueArray(Transitions);
		for (int Index = 0; Index < Transitions.Num(); Index++)
		{
			if (IsValid(Transitions[Index]))
			{
				Transitions[Index]->OnMarkedForDeletion.Broadcast();
			}
		}

		Edges.Empty();
		ChildrenNodes.Empty();
		return;
	}

	BlockTransitionUpdate = false;
	Transition = PreviousTransition;
}

#endif