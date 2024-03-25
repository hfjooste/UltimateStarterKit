// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Weapons/WeaponAmmoItem.h"
#include "WeaponAmmoItemAssetFactory.generated.h"

/**
 * @brief Factory class used to create a weapon ammo items
 */
UCLASS()
class USKEDITOR_API UWeaponAmmoItemAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UWeaponAmmoItemAssetFactory() { SupportedClass = AWeaponAmmoItem::StaticClass(); }
};
