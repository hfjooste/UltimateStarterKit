// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "WeaponFireMode.generated.h"

/**
 * @brief The types of weapon fire modes
 */
UENUM(BlueprintType)
enum class EWeaponFireMode : uint8
{
	/**
	 * @brief Fires a single shot each time the trigger is pulled
	 */
	SingleShot,

	/**
	 * @brief Fires multiple projectiles each time the trigger is pulled
	 */
	SemiAuto,

	/**
	 * @brief Continuously fires projectiles while the trigger is held
	 */
	FullAuto,
};	
