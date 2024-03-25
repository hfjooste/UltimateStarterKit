// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputIndicatorIcon.h"
#include "Blueprint/UserWidget.h"
#include "USK/Core/USKGameInstance.h"
#include "InputIndicator.generated.h"

/**
 * @brief A widget used to display input indicators based on the current input device and input action
 */
UCLASS()
class USK_API UInputIndicator : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The container used to display multiple images
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UHorizontalBox* Container;

	/**
	 * @brief The input indicator icon class
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|UI")
	TSubclassOf<UInputIndicatorIcon> InputIndicatorIconClass;

	/**
	 * @brief The input action displayed by widget
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|UI")
	UInputAction* Action;

	/**
	 * @brief The size of the image
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|UI")
	float Size = 50.0f;

	/**
	 * @brief The amount of images to display for the input action
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|UI")
	int Amount = 1;

	/**
	 * @brief Update the input action displayed by the widget
	 * @param NewAction The new action
	 * @param NewAmount The new amount of images to display
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void UpdateAction(UInputAction* NewAction, int NewAmount);

protected:
	/**
	 * @brief Overridable native event for when the widget has been constructed
	 */
	virtual void NativeConstruct() override;

private:
	/**
	 * @brief A reference to the game instance
	 */
	UPROPERTY()
	UUSKGameInstance* GameInstance;

	/**
	 * @brief Update the icon displayed in the widget
	 */
	UFUNCTION()
	void UpdateIcon();

	/**
	 * @brief Add a new icon to the container
	 * @param Icon The icon to add
	 */
	void AddIconImage(UTexture2D* Icon);
};
