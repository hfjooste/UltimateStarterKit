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

	/**
	 * @brief Limit only the rows of the inventory and allow the columns to increase
	 */
	FixedRows,

	/**
	 * @brief Limit only the columns of the inventory and allow the rows to increase
	 */
	FixedColumns
};
