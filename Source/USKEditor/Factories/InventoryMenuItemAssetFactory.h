// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Inventory/InventoryMenuItem.h"
#include "InventoryMenuItemAssetFactory.generated.h"

/**
 * @brief Factory class used to create an inventory menu item
 */
UCLASS()
class USKEDITOR_API UInventoryMenuItemAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UInventoryMenuItemAssetFactory() { SupportedClass = UInventoryMenuItem::StaticClass(); }
};
