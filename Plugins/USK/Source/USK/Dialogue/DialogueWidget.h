// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

enum class EDialogueTransitionType : uint8;

class UMenuItem;
class UDialogueEntry;

/**
 * @brief Widget used to display a dialogue
 */
UCLASS()
class USK_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

	/**
	 * @brief Event used to notify other classes when a choice is selected
	 * @param Index The index of the choice that was selected
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChoiceSelected, int, Index);

public:
	/**
	 * @brief The text block used to display the dialogue title
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UTextBlock* DialogueTitle;

	/**
	 * @brief The text block used to display the dialogue text
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UTextBlock* DialogueText;

	/**
	 * @brief The menu used to display the dialogue choices
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UMenu* ChoiceMenu;

	/**
	 * @brief The image displayed when the dialogue entry is completed
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* SkipEntryImage;

	/**
	 * @brief The class for all choice menu items
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	TSubclassOf<UMenuItem> ChoiceMenuItemClass;

	/**
	 * @brief Event used to notify other classes when a choice is selected
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|UI|Events")
	FChoiceSelected OnChoiceSelected;

	/**
	 * @brief Update the current entry and refresh the UI
	 * @param Entry The new dialogue entry
	 */
	void UpdateEntry(const UDialogueEntry* Entry);

	/**
	 * @brief Skip the current entry
	 * @return A boolean value indicating if the entry was skipped
	 */
	bool SkipEntry();

protected:
	/**
	 * @brief Event called every frame, if ticking is enabled
	 * @param MyGeometry Represents the position, size, and absolute position of a widget
	 * @param InDeltaTime Game time elapsed during last frame modified by the time dilation 
	 */
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	/**
	 * @brief An array of all the choice menu items
	 */
	TArray<UMenuItem*> ChoiceMenuItems;

	/**
	 * @brief The index of the text in the current dialogue entry
	 */
	float TextIndex;

	/**
	 * @brief The text of the current dialogue entry
	 */
	FText CurrentText;

	/**
	 * @brief The speed used to update the index and text
	 */
	float UpdateSpeed;

	/**
	 * @brief The transition type of the current dialogue entry
	 */
	EDialogueTransitionType CurrentTransitionType;

	/**
	 * @brief Initialize the choice menu items for the dialogue entry
	 * @param Entry The dialogue entry containing the choice data
	 */
	void InitializeMenuItems(const UDialogueEntry* Entry);

	/**
	 * @brief Notify other classes that a choice was selected
	 * @param Index The index of the choice that was selected
	 */
	UFUNCTION()
	void NotifyChoiceSelected(int Index);

	/**
	 * @brief Update the visibility of the transition widget
	 * @param NewVisibility The new visibility of the widget
	 */
	void UpdateTransitionIndicatorVisibility(ESlateVisibility NewVisibility);
};
