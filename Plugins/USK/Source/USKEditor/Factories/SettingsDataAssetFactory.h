// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Settings/SettingsData.h"
#include "SettingsDataAssetFactory.generated.h"

/**
 * @brief Factory class used to create a settings data
 */
UCLASS()
class USKEDITOR_API USettingsDataAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	USettingsDataAssetFactory() { SupportedClass = USettingsData::StaticClass(); }
};
