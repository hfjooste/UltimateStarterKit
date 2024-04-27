// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "DialogueTransitionType.h"
#include "DialogueParticipant.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "Styling/SlateColor.h"
#include "Templates/SubclassOf.h"
#include "Sound/SoundBase.h"
#include "DialogueEntry.generated.h"

class UDialogue;
class UDialogueTransition;

/**
 * @brief A single entry in a dialogue
 */
UCLASS(Blueprintable, DisplayName = "Dialogue Entry")
class USK_API UDialogueEntry : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * @brief The owner participant of the dialogue entry
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Entry")
	UDialogueParticipant* Owner;

	/**
	 * @brief The type of transition for this dialogue entry
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Entry")
	EDialogueTransitionType Transition;

	/**
	 * @brief The ID of the dialogue entry
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Entry")
	FName Id = FName(FGuid::NewGuid().ToString());

	/**
	 * @brief The text to display
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Entry")
	FText Text;

	/**
	 * @brief The speed of the dialogue
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Entry")
	float Speed = 12.5f;

	/**
	 * @brief The audio to play with this dialogue entry
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Entry")
	USoundBase* Audio;

	/**
	 * @brief Should the rich text style be overridden?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Entry")
	bool bOverrideRichTextStyle;

	/**
	 * @brief The rich text style applied to the widget
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Entry",
		meta=(EditCondition="bOverrideRichTextStyle", EditConditionHides))
	UDataTable* RichTextStyle;

	/**
	 * @brief Should the participant portrait image be overridden?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Entry")
	bool bOverridePortraitImage;

	/**
	 * @brief The custom portrait image for this dialogue entry
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Entry",
		meta=(EditCondition="bOverridePortraitImage", EditConditionHides))
	UTexture2D* CustomPortraitImage;

	/**
	 * @brief The custom portrait border color for this dialogue entry
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dialogue|Entry",
		meta=(EditCondition="bOverridePortraitImage", EditConditionHides))
	FSlateColor CustomPortraitBorderColor = FSlateColor(FLinearColor::Black);

	/**
	 * @brief A reference to the dialogue containing this entry
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ultimate Starter Kit|Dialogue|Entry")
	UDialogue* Dialogue;

	/**
	 * @brief An array of all the parent entries for this dialogue entry
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ultimate Starter Kit|Dialogue|Entry")
	TArray<UDialogueEntry*> ParentNodes;

	/**
	 * @brief An array of all the child entries for this dialogue entry
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ultimate Starter Kit|Dialogue|Entry")
	TArray<UDialogueEntry*> ChildrenNodes;

	/**
	 * @brief A map of all the possible edges for this dialogue entry
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ultimate Starter Kit|Dialogue|Entry")
	TMap<UDialogueEntry*, UDialogueTransition*> Edges;

	/**
	 * @brief Check if this entry is a leaf node
	 * @return A boolean value indicating if this entry is a leaf node
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Dialogue|Entry")
	bool IsLeafNode() const;

	/**
	 * @brief Get the title displayed for this dialogue entry
	 * @return The title displayed for this dialogue entry
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Dialogue|Entry")
	FText GetTitle();

	/**
	 * @brief Get the text displayed for this dialogue entry
	 * @return The text displayed for this dialogue entry
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Dialogue|Entry")
	FText GetText();

#if WITH_EDITOR
	/**
	 * @brief This is called when a property is about to be modified externally
	 * @param PropertyAboutToChange The property that is about to be modified
	 */
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;

	/**
	 * @brief Called when a property on this object has been modified externally
	 * @param PropertyChangedEvent The event containing information about the property that was changed
	 */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	/**
	 * @brief Should the update to the transition property be blocked?
	 */
	bool BlockTransitionUpdate;

	/**
	 * @brief The value of the transition property before it was changed
	 */
	EDialogueTransitionType PreviousTransition;
};
