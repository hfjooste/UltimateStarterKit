// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Widgets/InputIndicator.h"
#include "InputIndicatorAssetFactory.generated.h"

/**
 * @brief Factory class used to create an input indicator
 */
UCLASS()
class USKEDITOR_API UInputIndicatorAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UInputIndicatorAssetFactory() { SupportedClass = UInputIndicator::StaticClass(); }
};
