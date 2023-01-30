// Created by Henry Jooste

#pragma once

#include "GameFramework/SaveGame.h"
#include "USKSaveGame.generated.h"

/**
 * @brief Base class for all data saved using the game instance
 */
UCLASS()
class USK_API UUSKSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief A map of all the currencies that are currently saved
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit")
	TMap<FName, int> Currency;

	/**
	 * @brief A map of all the stats that are currently saved
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit")
	TMap<FName, float> Stats;
};
