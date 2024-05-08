// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "USK/Settings/SettingsFpsCounterType.h"
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
	 * @brief Container for the simple view
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	UCanvasPanel* SimpleViewContainer;

	/**
	 * @brief Container for the detailed view
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	UCanvasPanel* DetailedViewContainer;
	
	/**
	 * @brief The text block used to display the framerate in the simple view
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	UTextBlock* FramerateSimpleText;
	
	/**
	 * @brief The text block used to display the framerate
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	UTextBlock* FramerateText;

	/**
	 * @brief The text block used to display the min framerate
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	UTextBlock* MinText;

	/**
	 * @brief The text block used to display the max framerate
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	UTextBlock* MaxText;

	/**
	 * @brief The text block used to display the average framerate
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	UTextBlock* AverageText;

	/**
	 * @brief The delay in seconds between each update
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	float UpdateDelay = 0.125f;

	/**
	 * @brief The amount of seconds to measure the FPS before removing old measurements
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	int MeasureTime = 120;

	/**
	 * @brief A framerate that is considered high and will use the high color
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	int HighFramerate = 60;

	/**
	 * @brief A framerate that is considered medium and will use the medium color
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
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

	/**
	 * @brief Load and apply the FPS counter settings
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void LoadSettings();

protected:
	/**
	 * @brief Overridable native event for when the widget has been constructed
	 */
	virtual void NativeConstruct() override;

private:
	/**
	 * @brief The FPS values measured
	 */
	TArray<int> FpsValues;

	/**
	 * @brief The minimum FPS that was measured
	 */
	int MinFps = INT_MAX;

	/**
	 * @brief The maximum FPS that was measured
	 */
	int MaxFps = INT_MIN;

	/**
	 * @brief Update the framerate after a delay
	 */
	void UpdateFramerateAfterDelay();

	/**
	 * @brief Update the framerate
	 */
	UFUNCTION()
	void UpdateFramerate();

	/**
	 * @brief Update the framerate text
	 * @param TextBlock The text block to update
	 * @param Value The framerate value to display
	 */
	void UpdateFramerateText(UTextBlock* TextBlock, int Value) const;

	/**
	 * @brief Update the framerate widget type
	 * @param Type The type of framerate widget to display
	 */
	void UpdateWidgetType(ESettingsFpsCounterType Type);
};
