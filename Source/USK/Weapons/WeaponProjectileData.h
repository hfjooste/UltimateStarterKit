// Created by Henry Jooste

#pragma once

#include "WeaponProjectile.h"
#include "WeaponProjectileData.generated.h"

/**
 * @brief Structure describing a projectile spawned by a weapon
 */
USTRUCT(BlueprintType)
struct USK_API FWeaponProjectileData
{
	GENERATED_USTRUCT_BODY()

	/**
	 * @brief The class of the projectile to spawn
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon Projectile")
	TSubclassOf<AWeaponProjectile> ProjectileClass;

	/**
	 * @brief The relative transform of the projectile
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon Projectile")
	FTransform SpawnTransform;
};