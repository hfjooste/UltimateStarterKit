// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USKDataAssetFactory.h"
#include "Factories/Factory.h"
#include "USK/Weapons/CrosshairConfig.h"
#include "CrosshairConfigAssetFactory.generated.h"

/**
 * @brief Factory class used to create a crosshair config
 */
UCLASS()
class USKEDITOR_API UCrosshairConfigAssetFactory : public UUSKDataAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UCrosshairConfigAssetFactory()
	{
		DataAssetClass = UCrosshairConfig::StaticClass();
		SupportedClass = UCrosshairConfig::StaticClass();
	}
};
