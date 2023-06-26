// Created by Henry Jooste

#pragma once

#include "InventoryItem.generated.h"

/**
 * @brief The information about a specific inventory item
 */
USTRUCT(BlueprintType)
struct USK_API FInventoryItem
{
	GENERATED_USTRUCT_BODY()

	/**
	 * @brief The ID of the inventory item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Inventory|Item")
	FName Id;

	/**
	 * @brief The amount of the inventory item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Inventory|Item")
	int Amount;
};
