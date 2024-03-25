// Created by Henry Jooste

#pragma once

#include "InventoryItem.h"
#include "InventoryData.generated.h"

/**
 * @brief The inventory data for a single inventory
 */
USTRUCT(BlueprintType)
struct USK_API FInventoryData
{
	GENERATED_USTRUCT_BODY()

	/**
	 * @brief The array of items in the inventory
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Inventory")
	TArray<FInventoryItem> Items;
};
