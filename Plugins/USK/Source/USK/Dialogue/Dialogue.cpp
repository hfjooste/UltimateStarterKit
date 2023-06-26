// Created by Henry Jooste

#include "Dialogue.h"
#include "Engine/Engine.h"

/**
 * @brief Clear all the entries in the dialogue
 */
void UDialogue::ClearDialogue()
{
	for (int Index = 0; Index < AllEntries.Num(); ++Index)
	{
		UDialogueEntry* Entry = AllEntries[Index];
		if (IsValid(Entry))
		{
			Entry->ParentNodes.Empty();
			Entry->ChildrenNodes.Empty();
			Entry->Edges.Empty();
		}
	}

	AllEntries.Empty();
	RootEntries.Empty();
}