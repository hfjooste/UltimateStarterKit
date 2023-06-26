// Created by Henry Jooste

#pragma once

#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "InventoryItemData.generated.h"

/**
 * @brief The data used to describe an inventory item
 */
USTRUCT(BlueprintType)
struct USK_API FInventoryItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/**
	 * @brief The name of the inventory item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Inventory|Item Data")
	FText Name;

	/**
	 * @brief The description of the inventory item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Inventory|Item Data")
	FText Description;

	/**
	 * @brief The image displayed in the inventory
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Inventory|Item Data")
	UTexture2D* InventoryImage;

	/**
	 * @brief The preview image displayed when the item is highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Inventory|Item Data")
	UTexture2D* PreviewImage;
};
