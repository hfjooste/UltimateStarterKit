// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "WeaponType.generated.h"

/**
 * @brief The types of weapons
 */
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	/**
	 * @brief A one handed weapon
	 */
	WeaponOneHanded,

	/**
	 * @brief A two handed weapon
	 */
	WeaponTwoHanded,
};	
