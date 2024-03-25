// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Weapons/Weapon.h"
#include "WeaponAssetFactory.generated.h"

/**
 * @brief Factory class used to create a weapons
 */
UCLASS()
class USKEDITOR_API UWeaponAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UWeaponAssetFactory() { SupportedClass = AWeapon::StaticClass(); }
};
