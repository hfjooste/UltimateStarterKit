// Created by Henry Jooste

#include "Weapon.h"

#include "NiagaraFunctionLibrary.h"
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
 * @brief Fire the weapon
 */
void AWeapon::Fire()
{
	if (!IsValid(Character) || !IsValid(Character->GetController()))
	{
		return;
	}

	SpawnProjectile();
	PlayFireAnimation();
	OnWeaponFired.Broadcast();
}

/**
 * @brief Spawn the projectile
 */
void AWeapon::SpawnProjectile() const
{
	if (!IsValid(ProjectileClass))
	{
		return;
	}

	const APlayerController* PlayerController = dynamic_cast<APlayerController*>(Character->GetController());
	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	const FVector SpawnLocation = MuzzleFlash->GetComponentLocation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AWeaponProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	UAudioUtils::PlaySound(Character, FireSound);

	if (IsValid(MuzzleFlashParticleFx))
    {
    	UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFlashParticleFx, MuzzleFlash, NAME_None,
    		FVector::ZeroVector, FRotator::ZeroRotator,
    		EAttachLocation::SnapToTarget, true);
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
