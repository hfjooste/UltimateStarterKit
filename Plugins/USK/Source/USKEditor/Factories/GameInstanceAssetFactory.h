// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Core/USKGameInstance.h"
#include "GameInstanceAssetFactory.generated.h"

/**
 * @brief Factory class used to create a game instance
 */
UCLASS()
class USKEDITOR_API UGameInstanceAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UGameInstanceAssetFactory() { SupportedClass = UUSKGameInstance::StaticClass(); }
};
