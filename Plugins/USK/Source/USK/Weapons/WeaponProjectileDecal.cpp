// Created by Henry Jooste

#include "WeaponProjectileDecal.h"

#include "Kismet/KismetSystemLibrary.h"
#include "USK/Logger/Log.h"

/**
 * @brief Create a new instance of the AWeaponProjectile actor
 */
AWeaponProjectileDecal::AWeaponProjectileDecal()
{
	PrimaryActorTick.bCanEverTick = true;
}

/**
 * @brief Overridable native event for when play begins for this actor
 */
void AWeaponProjectileDecal::BeginPlay()
{
	Super::BeginPlay();
	if (bAutomaticallyDestroy && Lifetime > 0.0f)
	{
		USK_LOG_TRACE("Starting projectile decal destruction timer");
		UKismetSystemLibrary::K2_SetTimer(this, "DestroyDecal", Lifetime, false);
	}
}

/**
 * @brief Destroy the decal actor
 */
void AWeaponProjectileDecal::DestroyDecal_Implementation()
{
	USK_LOG_INFO("Destroying projectile decal");
	Destroy();
}