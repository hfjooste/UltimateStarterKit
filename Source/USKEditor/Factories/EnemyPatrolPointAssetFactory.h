// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/AI/EnemyPatrolPoint.h"
#include "EnemyPatrolPointAssetFactory.generated.h"

/**
 * @brief Factory class used to create an enemy patrol point
 */
UCLASS()
class USKEDITOR_API UEnemyPatrolPointAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UEnemyPatrolPointAssetFactory() { SupportedClass = AEnemyPatrolPoint::StaticClass(); }
};
