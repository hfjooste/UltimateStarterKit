// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FpsCounter.generated.h"

/**
 * @brief A widget used to display the current framerate
 */
UCLASS()
class USK_API UFpsCounter : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * @brief The text block used to display the framerate
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UTextBlock* FramerateText;

	/**
	 * @brief The delay in seconds between each update
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|UI")
	float UpdateDelay = 0.125f;

	/**
	 * @brief A framerate that is considered high and will use the high color
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|UI")
	int HighFramerate = 60;

	/**
	 * @brief A framerate that is considered medium and will use the medium color
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|UI")
	int MediumFramerate = 30;

	/**
	 * @brief The color used to display high framerates
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	FLinearColor HighColor = FLinearColor::Green;

	/**
	 * @brief The color used to display medium framerates
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	FLinearColor MediumColor = FLinearColor::Yellow;

	/**
	 * @brief The color used to display low framerates
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	FLinearColor LowColor = FLinearColor::Red;

	/**
	 * @brief Update the visibility of the widget
	 * @param IsVisible Is the widget visible?
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void UpdateVisibility(bool IsVisible);

protected:
	/**
	 * @brief Overridable native event for when the widget has been constructed
	 */
	virtual void NativeConstruct() override;

private:
	/**
	 * @brief Initialize the visibility of the widget by checking the settings
	 */
	void InitializeVisibility();
	/**
	 * @brief Update the framerate after a delay
	 */
	void UpdateFramerateAfterDelay();

	/**
	 * @brief Update the framerate
	 */
	UFUNCTION()
	void UpdateFramerate();
};
