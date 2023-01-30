// Created by Henry Jooste

#pragma once

#include "Currency.generated.h"

/**
 * @brief A type of currency to track
 */
USTRUCT(BlueprintType)
struct USK_API FCurrency
{
	GENERATED_USTRUCT_BODY()

	/**
	 * @brief The initial amount for the currency
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Currency")
	int InitialAmount;

	/**
	 * @brief Should all value updates automatically be saved using the game instance?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Currency",
		DisplayName = "Automatically save/load the value")
	bool AutoSave;

	/**
	 * @brief The current amount of the currency
	 */
	int Amount;
};
