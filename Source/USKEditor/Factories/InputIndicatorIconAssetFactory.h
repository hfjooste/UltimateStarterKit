// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Widgets/InputIndicatorIcon.h"
#include "InputIndicatorIconAssetFactory.generated.h"

/**
 * @brief Factory class used to create an input indicator icon
 */
UCLASS()
class USKEDITOR_API UInputIndicatorIconAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UInputIndicatorIconAssetFactory() { SupportedClass = UInputIndicatorIcon::StaticClass(); }
};
