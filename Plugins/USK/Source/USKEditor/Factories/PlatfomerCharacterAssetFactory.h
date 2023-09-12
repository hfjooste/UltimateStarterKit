// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Character/PlatformerCharacter.h"
#include "PlatfomerCharacterAssetFactory.generated.h"

/**
 * @brief Factory class used to create a platformer character
 */
UCLASS()
class USKEDITOR_API UPlatfomerCharacterAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UPlatfomerCharacterAssetFactory() { SupportedClass = APlatformerCharacter::StaticClass(); }
};
