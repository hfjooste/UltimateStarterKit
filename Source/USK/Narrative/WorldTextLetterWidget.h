// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "WorldTextLetterWidget.generated.h"

class UWorldTextWordWidget;

/**
 * @brief A letter displayed in the world text
 */
UCLASS()
class USK_API UWorldTextLetterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The animation played when showing the letter
	 */
	UPROPERTY(meta = (BindWidgetAnimOptional), Transient, EditAnywhere, BlueprintReadWrite,
		Category = "Ultimate Starter Kit|Narrative")
	UWidgetAnimation* ShowAnimation;

	/**
	 * @brief The animation played when destroying the letter
	 */
	UPROPERTY(meta = (BindWidgetAnimOptional), Transient, EditAnywhere, BlueprintReadWrite,
		Category = "Ultimate Starter Kit|Narrative")
	UWidgetAnimation* DestroyAnimation;

	/**
	 * @brief The text block used to display the letter
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Narrative")
	UTextBlock* TextBlock;

	/**
	 * @brief The time it takes to type the letter
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Narrative")
	float TypeDuration = 0.055f;

	/**
	 * @brief Initialize the letter
	 * @param Word The parent world text word widget
	 * @param Letter The letter to display
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Narrative")
	void InitializeLetter(UWorldTextWordWidget* Word, const FString& Letter);

	/**
	 * @brief Update the reference to the next letter in the word
	 * @param Letter The next letter in the word
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Narrative")
	void UpdateNextLetter(UWorldTextLetterWidget* Letter);

	/**
	 * @brief Show the letter
	 * @param Index The index of the letter in the word
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Narrative")
	void Show(int Index);

	/**
	 * @brief Destroy the letter
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Narrative")
	void Destroy();

private:
	/**
	 * @brief A reference to the parent world word widget
	 */
	UPROPERTY()
	UWorldTextWordWidget* ParentWord;

	/**
	 * @brief A reference to the next letter
	 */
	UPROPERTY()
	UWorldTextLetterWidget* NextLetter;
};
