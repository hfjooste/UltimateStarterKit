// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/AI/EnemyWanderArea.h"
#include "EnemyWanderAreaAssetFactory.generated.h"

/**
 * @brief Factory class used to create an enemy wander area
 */
UCLASS()
class USKEDITOR_API UEnemyWanderAreaAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UEnemyWanderAreaAssetFactory() { SupportedClass = AEnemyWanderArea::StaticClass(); }
};
