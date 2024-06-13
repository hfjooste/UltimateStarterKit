// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "EnemyAttackType.generated.h"

/**
 * @brief The type of attack performed by an enemy character
 */
UENUM(BlueprintType)
enum class EEnemyAttackType : uint8
{
	/**
	 * @brief A melee attack
	 */
	Melee,

	/**
	 * @brief A ranged attack
	 */
	Ranged,

	/**
	 * @brief Move to a random location each time a patrol point is reached
	 */
	RandomLocation,
};
