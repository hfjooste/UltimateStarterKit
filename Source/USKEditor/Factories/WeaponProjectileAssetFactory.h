// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Weapons/WeaponProjectile.h"
#include "WeaponProjectileAssetFactory.generated.h"

/**
 * @brief Factory class used to create a weapon projectiles
 */
UCLASS()
class USKEDITOR_API UWeaponProjectileAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UWeaponProjectileAssetFactory() { SupportedClass = AWeaponProjectile::StaticClass(); }
};
