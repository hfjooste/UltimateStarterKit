// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "PatrolType.generated.h"

/**
 * @brief The type of patrol an enemy character can perform
 */
UENUM(BlueprintType)
enum class EPatrolType : uint8
{
	/**
	 * @brief Reverse the patrol points after reaching the end
	 */
	ReverseDirection,

	/**
	 * @brief Restart the patrol path after reaching the end
	 */
	RestartPath,

	/**
	 * @brief Move to a random location each time a patrol point is reached
	 */
	RandomLocation,
};
