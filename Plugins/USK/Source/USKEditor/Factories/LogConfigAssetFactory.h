// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USKDataAssetFactory.h"
#include "Factories/Factory.h"
#include "USK/Logger/LogConfig.h"
#include "LogConfigAssetFactory.generated.h"

/**
 * @brief Factory class used to create a log config
 */
UCLASS()
class USKEDITOR_API ULogConfigAssetFactory : public UUSKDataAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	ULogConfigAssetFactory()
	{
		DataAssetClass = ULogConfig::StaticClass();
		SupportedClass = ULogConfig::StaticClass();
	}
};
