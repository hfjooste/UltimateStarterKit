// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "CameraPerspective.generated.h"

/**
 * @brief The different camera perspectives that can be used by a character
 */
UENUM(BlueprintType)
enum class ECameraPerspective : uint8
{
	/**
	 * @brief First person camera perspective
	 */
	FirstPerson,

	/**
	 * @brief Third person camera perspective
	 */
	ThirdPerson,
};	