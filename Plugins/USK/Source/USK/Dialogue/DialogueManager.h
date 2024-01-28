// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
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
class USK_API ADialogueManager : public APawn
{
	GENERATED_BODY()

	/**
	 * @brief Event used to notify other classes when the dialogue has ended
	 * @param LastEntryId The ID of the last entry in the dialogue
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogueEnded, FName, LastEntryId);

	/**
	 * @brief Event used to notify other classes when a dialogue entry has started
	 * @param LastEntryId The ID of the dialogue entry
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogueEntryStarted, FName, EntryId);

	/**
	 * @brief Event used to notify other classes when a dialogue entry has ended
	 * @param LastEntryId The ID of the dialogue entry
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogueEntryEnded, FName, EntryId);

	/**
	 * @brief The audio component responsible for playing the audio files of the dialogue entries
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Dialogue",
		meta=(AllowPrivateAccess = "true"))
	class UAudioComponent* AudioComponent;
	
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
	 * @brief A boolean value indicating if the dialogue should automatically be destroyed when completed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue")
	bool DestroyOnComplete = true;

	/**
	 * @brief A boolean value indicating if the dialogue should automatically be stopped when completed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue",
		meta=(EditCondition = "!DestroyOnComplete", EditConditionHides))
	bool StopOnComplete = true;

	/**
	 * @brief The sound effect to play when an entry is skipped
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Audio")
	USoundBase* SkipSFX;

	/**
	 * @brief The sound effect to play when advancing to the next entry
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Audio")
	USoundBase* AdvanceSFX;

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
	 * @brief Event used to notify other classes when a dialogue entry has started
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Dialogue|Events")
	FDialogueEntryStarted OnDialogueEntryStarted;

	/**
	 * @brief Event used to notify other classes when a dialogue entry has ended
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Dialogue|Events")
	FDialogueEntryEnded OnDialogueEntryEnded;

	/**
	 * @brief Create a new instance of the DialogueManager class 
	 */
	ADialogueManager();

	/**
	 * @brief Play the dialogue
	 */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Ultimate Starter Kit|Dialogue")
	virtual void PlayDialogue();

	/**
	 * @brief Stop playing the dialogue
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Dialogue")
	virtual void StopDialogue();

	/**
	 * @brief Stop playing the dialogue and destroy the dialogue manager
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Dialogue")
	virtual void DestroyDialogue();

	/**
	 * @brief Skip the current entry in the dialogue
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Dialogue")
	virtual void SkipEntry();

	/**
	 * @brief Get the dialogue widget
	 * @return A reference to the dialogue widget
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Dialogue")
	UDialogueWidget* GetDialogueWidget() const;

protected:
	/**
	 * @brief Overridable native event for when play begins for this actor
	 */
	virtual void BeginPlay() override;

private:
	/**
	 * @brief A reference to the pawn that was possessed before the dialogue started
	 */
	UPROPERTY()
	APawn* PossessedPawn;
	
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
