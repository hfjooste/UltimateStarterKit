// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Weapons/WeaponItem.h"
#include "WeaponItemAssetFactory.generated.h"

/**
 * @brief Factory class used to create a weapon items
 */
UCLASS()
class USKEDITOR_API UWeaponItemAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UWeaponItemAssetFactory() { SupportedClass = AWeaponItem::StaticClass(); }
};
