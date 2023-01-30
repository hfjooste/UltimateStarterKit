// Created by Henry Jooste

#pragma once

#include "Stat.generated.h"

/**
 * @brief A type of stat to track
 */
USTRUCT(BlueprintType)
struct USK_API FStat
{
	GENERATED_USTRUCT_BODY()

	/**
	 * @brief The initial value for the stat
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Stats")
	float InitialValue;

	/**
	 * @brief The maximum value for the stat
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Stats")
	float MaxValue = 100.0f;

	/**
	 * @brief The amount of value to regenerate every second
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Stats")
	float RegenerateAmount;

	/**
	 * @brief The delay before the value starts regenerating
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Stats")
	float RegenerateDelay;

	/**
	 * @brief Should all value updates automatically be saved using the game instance?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Stats",
		DisplayName = "Automatically save/load the value")
	bool AutoSave;

	/**
	 * @brief The current amount of the stat
	 */
	float Value;

	/**
	 * @brief The current delay before regenerating the value
	 */
	float CurrentRegenerateDelay;
};
