// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Widgets/FpsCounter.h"
#include "FramerateCounterAssetFactory.generated.h"

/**
 * @brief Factory class used to create a framerate counter
 */
UCLASS()
class USKEDITOR_API UFramerateCounterAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UFramerateCounterAssetFactory() { SupportedClass = UFpsCounter::StaticClass(); }
};
