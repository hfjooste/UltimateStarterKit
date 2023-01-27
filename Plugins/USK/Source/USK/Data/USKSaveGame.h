// Created by Henry Jooste

#pragma once

#include "GameFramework/SaveGame.h"
#include "USKSaveGame.generated.h"

/**
 * @brief Base class for all data saved using the save manager
 */
UCLASS()
class USK_API UUSKSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief A map of all the currencies that is handled by the currency manager
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit")
	TMap<FString, int> Currency;
};
