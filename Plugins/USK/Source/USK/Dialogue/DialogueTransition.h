// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "DialogueEntry.h"
#include "DialogueTransition.generated.h"

class UDialogue;

/**
 * @brief A transition from one dialogue entry to the next
 */
UCLASS(Blueprintable)
class USK_API UDialogueTransition : public UObject
{
	GENERATED_BODY()

	/**
	 * @brief Event used to notify other classes that the transition is marked for deletion
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMarkedForDeletion);

public:
	/**
	 * @brief Event used to notify other classes that the transition is marked for deletion
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Dialogue|Transition")
	FMarkedForDeletion OnMarkedForDeletion;

	/**
	 * @brief The text displayed for this transition (choice)
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Transition")
	FText Text;

	/**
	 * @brief The dialogue entry where the transition starts
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ultimate Starter Kit|Dialogue|Transition")
	UDialogueEntry* StartEntry;

	/**
	 * @brief The dialogue entry where the transition ends
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ultimate Starter Kit|Dialogue|Transition")
	UDialogueEntry* EndEntry;
};
