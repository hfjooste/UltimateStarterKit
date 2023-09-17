// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Character/FpsCharacter.h"
#include "FpsCharacterAssetFactory.generated.h"

/**
 * @brief Factory class used to create a FPS character
 */
UCLASS()
class USKEDITOR_API UFpsCharacterAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UFpsCharacterAssetFactory() { SupportedClass = AFpsCharacter::StaticClass(); }
};
