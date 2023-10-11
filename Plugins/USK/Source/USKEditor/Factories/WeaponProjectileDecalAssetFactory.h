// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Weapons/WeaponProjectileDecal.h"
#include "WeaponProjectileDecalAssetFactory.generated.h"

/**
 * @brief Factory class used to create a weapon projectile decals
 */
UCLASS()
class USKEDITOR_API UWeaponProjectileDecalAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UWeaponProjectileDecalAssetFactory() { SupportedClass = AWeaponProjectileDecal::StaticClass(); }
};
