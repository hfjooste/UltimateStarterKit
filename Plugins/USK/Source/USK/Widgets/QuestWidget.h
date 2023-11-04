// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestWidget.generated.h"

class UQuest;
/**
 * @brief The widget displayed for the current quest point
 */
UCLASS()
class USK_API UQuestWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * @brief The text block used to quest title
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UTextBlock* QuestTitleText;

	/**
	 * @brief The text block used to quest details
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UTextBlock* QuestDetailsText;
	
	/**
	 * @brief The animation played when the widget is shown
	 */
	UPROPERTY(meta = (BindWidgetAnimOptional), Transient, EditAnywhere, BlueprintReadWrite,
			Category = "Ultimate Starter Kit|UI")
	class UWidgetAnimation* ShowAnimation;

	/**
	 * @brief Show the quest widget
	 * @param Quest The current quest
	 * @param Point The current quest point
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void Show(UQuest* Quest, int Point);

	/**
	 * @brief Hide the quest widget
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void Hide();
};