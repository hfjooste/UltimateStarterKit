// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "InventorySize.generated.h"

/**
 * @brief The size restrictions of the inventory
 */
UENUM(BlueprintType)
enum class EInventorySize : uint8
{
	/**
	 * @brief Limit both the width and height of the inventory
	 */
	FixedSize,
};
