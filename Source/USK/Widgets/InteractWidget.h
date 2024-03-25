// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractWidget.generated.h"

/**
 * @brief The widget displayed when the player can interact with an object
 */
UCLASS()
class USK_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * @brief The text block used to display the text before the input indicator
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UTextBlock* BeforeTextBlock;

	/**
	 * @brief The text block used to display the text after the input indicator
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UTextBlock* AfterTextBlock;
	
	/**
	 * @brief The animation played when the widget is shown
	 */
	UPROPERTY(meta = (BindWidgetAnimOptional), Transient, EditAnywhere, BlueprintReadWrite,
			Category = "Ultimate Starter Kit|UI")
	class UWidgetAnimation* ShowAnimation;

	/**
	 * @brief Show the interact widget
	 * @param BeforeText The text displayed before the input indicator
	 * @param AfterText The text displayed after the input indicator
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void Show(FText BeforeText, FText AfterText);

	/**
	 * @brief Hide the interact widget
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void Hide();
};
