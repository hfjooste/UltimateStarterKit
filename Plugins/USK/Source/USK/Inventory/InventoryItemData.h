// Created by Henry Jooste

#pragma once

#include "Engine/DataTable.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	/**
	 * @brief The description of the inventory item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	/**
	 * @brief The image displayed in the inventory
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* InventoryImage;

	/**
	 * @brief The preview image displayed when the item is highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* PreviewImage;
};
