// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "DialogueEntry.h"
#include "Dialogue.generated.h"

UCLASS(Blueprintable)
class USK_API UDialogue : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * @brief An array of all the root entries contained by this dialogue
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ultimate Starter Kit|Dialogue")
	TArray<UDialogueEntry*> RootEntries;

	/**
	 * @brief An array of all the entries contained by this dialogue
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ultimate Starter Kit|Dialogue")
	TArray<UDialogueEntry*> AllEntries;

	/**
	 * @brief Clear all the entries in the dialogue
	 */
	void ClearDialogue();

#if WITH_EDITORONLY_DATA
	/**
	 * @brief A reference to the editor graph used by this dialogue
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ultimate Starter Kit|Dialogue")
	class UEdGraph* EditorGraph;
#endif
};
