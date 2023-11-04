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
	 * @brief The animation played when the widget is shown
	 */
	UPROPERTY(meta = (BindWidgetAnimOptional), Transient, EditAnywhere, BlueprintReadWrite,
			Category = "Ultimate Starter Kit|UI")
	class UWidgetAnimation* ShowAnimation;

	/**
	 * @brief Show the interact widget
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void Show();

	/**
	 * @brief Hide the interact widget
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void Hide();
};
