﻿// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "DialogueManager.generated.h"

class UInputAction;
class UInputMappingContext;
class UDialogueEntry;
class UDialogueWidget;
class UDialogue;

/**
 * @brief The pawn responsible for managing the dialogue
 */
UCLASS()
class ADialogueManager : public APawn
{
	GENERATED_BODY()

	/**
	 * @brief Event used to notify other classes when the dialogue has ended
	 * @param LastEntryId The ID of the last entry in the dialogue
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogueEnded, FName, LastEntryId);
	
public:
	/**
	 * @brief The dialogue that should be played by the dialogue manager
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue")
	UDialogue* Dialogue;

	/**
	 * @brief The class of the widget used to display the dialogue
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue")
	TSubclassOf<UDialogueWidget> DialogueWidgetClass;

	/**
	 * @brief A boolean value indicating if the dialogue should automatically play when the level is started
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue")
	bool PlayOnStart = true;

	/**
	 * @brief The input mapping context used to interact with the dialogue
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Input")
	UInputMappingContext* InputMappingContext;

	/**
	 * @brief The input action used to skip the current dialogue entry
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Input")
	UInputAction* SkipAction;

	/**
	 * @brief Event used to notify other classes when the dialogue has ended
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Dialogue|Events")
	FDialogueEnded OnDialogueEnded;

	/**
	 * @brief Play the dialogue
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Dialogue")
	void PlayDialogue();

	/**
	 * @brief Skip the current entry in the dialogue
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Dialogue")
	void SkipEntry();

protected:
	/**
	 * @brief Overridable native event for when play begins for this actor
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Tell client that the Pawn is begin restarted
	 */
	virtual void PawnClientRestart() override;

	/**
	 * @brief Allows a Pawn to set up custom input bindings
	 * @param PlayerInputComponent The component that enables an Actor to bind various forms of input events
	 */
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	/**
	 * @brief A reference to the dialogue widget
	 */
	UPROPERTY()
	UDialogueWidget* DialogueWidget;

	/**
	 * @brief A reference to the current entry in the dialogue
	 */
	UPROPERTY()
	UDialogueEntry* CurrentEntry;

	/**
	 * @brief Update the current dialogue entry
	 * @param NewEntry The new dialogue entry
	 */
	void UpdateCurrentEntry(UDialogueEntry* NewEntry);

	/**
	 * @brief Update the dialogue after a choice has been selected
	 * @param Index The index of the choice that was selected
	 */
	UFUNCTION()
	void OnChoiceSelected(int Index);
};
