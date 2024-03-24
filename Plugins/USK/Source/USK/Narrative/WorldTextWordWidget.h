// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "WorldTextWordWidget.generated.h"

class UWorldTextWidget;

/**
 * @brief The widget used to display a word in the world
 */
UCLASS()
class USK_API UWorldTextWordWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The container for all the letters
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Narrative")
	UHorizontalBox* Container;

	/**
	 * @brief Initialize the word
	 * @param Text The parent world text widget
	 * @param Word The word to display
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Narrative")
	void InitializeWord(UWorldTextWidget* Text, FString Word);

	/**
	 * @brief Update the reference to the next word in the text
	 * @param Word The next word in the text
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Narrative")
	void UpdateNextWord(UWorldTextWordWidget* Word);

	/**
	 * @brief Show the word
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Narrative")
	void Show();

	/**
	 * @brief Show the next word
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Narrative")
	void ShowNextWord();

	/**
	 * @brief Destroy the word widget
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Narrative")
	void Destroy() const;

private:
	/**
	 * @brief A reference to the parent world text widget
	 */
	UPROPERTY()
	UWorldTextWidget* ParentText;

	/**
	 * @brief A reference to the next world word widget
	 */
	UPROPERTY()
	UWorldTextWordWidget* NextWord;
};
