// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Character/USKEnemyCharacter.h"
#include "USKEnemyCharacterAssetFactory.generated.h"

/**
 * @brief Factory class used to create an enemy character
 */
UCLASS()
class USKEDITOR_API UUSKEnemyCharacterAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UUSKEnemyCharacterAssetFactory() { SupportedClass = AUSKEnemyCharacter::StaticClass(); }
};
