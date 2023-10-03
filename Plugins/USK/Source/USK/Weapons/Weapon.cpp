// Created by Henry Jooste

#include "Weapon.h"

#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "USK/Audio/AudioUtils.h"
#include "USK/Character/USKCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Create a new instance of the AWeapon actor
 */
AWeapon::AWeapon()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("Weapon Root");
	MuzzleFlash = CreateDefaultSubobject<USceneComponent>("Muzzle Flash");
	MuzzleFlash->SetupAttachment(RootComponent);
}

/**
 * @brief Equip the weapon
 * @param TargetCharacter The character that will use the weapon
 */
void AWeapon::Equip(AUSKCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	if (!IsValid(Character))
	{
		return;
	}

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPoint);
	Character->SetWeapon(this);
	SetActorRelativeTransform(WeaponTransform);
	OnWeaponEquipped.Broadcast();
	USK_LOG_INFO("Weapon equipped");
}

/**
 * @brief Unequip the weapon
 */
void AWeapon::Unequip()
{
	if (IsValid(Character) && Character->GetWeapon() == this)
	{
		Character->SetWeapon(nullptr);
	}

	OnWeaponUnequipped.Broadcast();
	USK_LOG_INFO("Weapon unequipped");
	Destroy();
}

/**
 * @brief Start firing the weapon
 */
void AWeapon::StartFiring()
{
	bIsFiring = true;
	ShotsRemaining = MaxShotsPerFireEvent;
	
	switch (WeaponFireMode)
	{
	case EWeaponFireMode::SingleShot:
		StartFiringSingleShot();
		break;
	case EWeaponFireMode::SemiAuto:
		StartFiringSemiAuto();
		break;
	case EWeaponFireMode::FullAuto:
		StartFiringFullAuto();
		break;
	default:
		USK_LOG_ERROR("Invalid weapon fire mode");
		break;
	}
}

/**
 * @brief Stop firing the weapon
 */
void AWeapon::StopFiring()
{
	bIsFiring = false;
}

/**
 * @brief Fire a single shot weapon
 */
void AWeapon::StartFiringSingleShot()
{
	if (!bIsFiring || !IsValid(Character) || !IsValid(Character->GetController()))
	{
		return;
	}

	UAudioUtils::PlaySound(Character, FireSound);
	for (FWeaponProjectileData Projectile : Projectiles)
	{
		SpawnProjectile(Projectile);
	}

	if (IsValid(MuzzleFlashParticleFx))
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFlashParticleFx, MuzzleFlash, NAME_None,
			FVector::ZeroVector, FRotator::ZeroRotator,
			EAttachLocation::SnapToTarget, true);
	}
	
	PlayFireAnimation();
	OnWeaponFired.Broadcast();
}

/**
 * @brief Fire a semi-auto weapon
 */
void AWeapon::StartFiringSemiAuto()
{
	if (!bIsFiring)
	{
		return;
	}

	ShotsRemaining--;
	if (ShotsRemaining < 0)
	{
		return;
	}
	
	StartFiringSingleShot();
	UKismetSystemLibrary::K2_SetTimer(this, "StartFiringSemiAuto", FireRate, false);
}

/**
 * @brief Fire a full auto weapon
 */
void AWeapon::StartFiringFullAuto()
{
	if (!bIsFiring)
	{
		return;
	}
	
	StartFiringSingleShot();
	UKismetSystemLibrary::K2_SetTimer(this, "StartFiringFullAuto", FireRate, false);
}

/**
 * @brief Spawn the projectile
 * @param Projectile The projectile to spawn
 */
void AWeapon::SpawnProjectile(const FWeaponProjectileData& Projectile) const
{
	if (!IsValid(Projectile.ProjectileClass))
	{
		return;
	}

	const APlayerController* PlayerController = dynamic_cast<APlayerController*>(Character->GetController());
	const FRotator SpawnRotation = UKismetMathLibrary::ComposeRotators(
		PlayerController->PlayerCameraManager->GetCameraRotation(), Projectile.SpawnTransform.Rotator());
	const FVector SpawnLocation = MuzzleFlash->GetComponentLocation() + Projectile.SpawnTransform.GetLocation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AWeaponProjectile* WeaponProjectile = GetWorld()->SpawnActor<AWeaponProjectile>(Projectile.ProjectileClass,
		SpawnLocation, SpawnRotation, SpawnParams);
	
	if (IsValid(WeaponProjectile))
	{
		WeaponProjectile->SetActorScale3D(Projectile.SpawnTransform.GetScale3D());
	}
}

/**
 * @brief Play the fire animation
 */
void AWeapon::PlayFireAnimation() const
{
	if (!IsValid(FireAnimation))
	{
		return;
	}

	Character->PlayAnimMontage(FireAnimation, 1.0f);
}
