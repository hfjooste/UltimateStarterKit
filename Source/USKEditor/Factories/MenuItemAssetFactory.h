// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Widgets/MenuItem.h"
#include "MenuItemAssetFactory.generated.h"

/**
 * @brief Factory class used to create a menu item
 */
UCLASS()
class USKEDITOR_API UMenuItemAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UMenuItemAssetFactory() { SupportedClass = UMenuItem::StaticClass(); }
};
