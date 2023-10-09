// Created by Henry Jooste

#pragma once

#include "NiagaraSystem.h"
#include "WeaponProjectileHitData.generated.h"

/**
 * @brief Structure describing the hit data of a projectile
 */
USTRUCT(BlueprintType)
struct USK_API FWeaponProjectileHitData
{
	GENERATED_USTRUCT_BODY()

	/**
	 * @brief The particle FX to spawn when the projectile hits the actor
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon Projectile Hit")
	UNiagaraSystem* HitParticleFx;

	/**
	 * @brief The transform of the particle FX
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon Projectile Hit")
	FTransform HitParticleFxTransform;

	/**
	 * @brief The sound effect to play when the projectile hits the actor
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon Projectile Hit")
	TArray<USoundBase*> HitSfx;
};