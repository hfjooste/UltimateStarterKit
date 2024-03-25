// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USKDataAssetFactory.h"
#include "Factories/Factory.h"
#include "USK/Settings/SettingsConfig.h"
#include "SettingsConfigAssetFactory.generated.h"

/**
 * @brief Factory class used to create a settings config
 */
UCLASS()
class USKEDITOR_API USettingsConfigAssetFactory : public UUSKDataAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	USettingsConfigAssetFactory()
	{
		DataAssetClass = USettingsConfig::StaticClass();
		SupportedClass = USettingsConfig::StaticClass();
	}
};
