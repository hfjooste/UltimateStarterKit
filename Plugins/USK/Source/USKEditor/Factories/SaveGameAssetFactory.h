// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Core/USKSaveGame.h"
#include "SaveGameAssetFactory.generated.h"

/**
 * @brief Factory class used to create a save game
 */
UCLASS()
class USKEDITOR_API USaveGameAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	USaveGameAssetFactory() { SupportedClass = UUSKSaveGame::StaticClass(); }
};
