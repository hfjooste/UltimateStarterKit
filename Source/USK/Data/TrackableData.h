// Created by Henry Jooste

#pragma once

#include "TrackableData.generated.h"

/**
 * @brief All trackable data use the FTrackableData struct to specify the default values and behaviours
 */
USTRUCT(BlueprintType)
struct USK_API FTrackableData
{
	GENERATED_USTRUCT_BODY()

	/**
	 * @brief The initial value of the data
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Trackable Data")
	float InitialValue;

	/**
	 * @brief Should we enforce a maximum value?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Trackable Data")
	bool EnforceMaxValue;

	/**
	 * @brief The maximum value of the data
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Trackable Data",
		meta = (EditCondition = "EnforceMaxValue"))
	float MaxValue = 100.0f;

	/**
	 * @brief Should all value updates automatically be saved using the game instance?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Trackable Data",
		DisplayName = "Automatically save/load the value")
	bool AutoSave;

	/**
	 * @brief Should we automatically generate value every second?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Trackable Data",
		DisplayName = "Automatically generate value")
	bool AutoGenerate;

	/**
	 * @brief The amount of value to generate every second
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Trackable Data",
		meta = (EditCondition = "AutoGenerate"))
	float GenerateAmount;

	/**
	 * @brief The delay before the value starts generating after losing value
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Trackable Data",
		meta = (EditCondition = "AutoGenerate"))
	float GenerateDelay;

	/**
	 * @brief The current delay before regenerating the value
	 */
	float CurrentGenerateDelay;

	/**
	 * @brief The current value of the data
	 */
	float CurrentValue;
};
