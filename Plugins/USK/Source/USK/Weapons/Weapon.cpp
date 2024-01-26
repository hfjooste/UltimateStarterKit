// Created by Henry Jooste

#include "Weapon.h"

#include "NiagaraFunctionLibrary.h"
#include "WeaponProjectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "USK/Audio/AudioUtils.h"
#include "USK/Character/USKCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Create a new instance of the AWeapon actor
 */
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Weapon Root");
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon Mesh");
	WeaponMesh->SetupAttachment(RootComponent);
	MuzzleFlash = CreateDefaultSubobject<USceneComponent>("Muzzle Flash");
	MuzzleFlash->SetupAttachment(WeaponMesh);
}

/**
 * @brief Overridable native event for when play begins for this actor
 */
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	AmmoRemaining = bRequireReloading ? AmmoPerClip : Ammo;
	ReloadAmmoRemaining = Ammo - AmmoPerClip;
	OnWeaponAmmoUpdated.Broadcast(this, AmmoRemaining, ReloadAmmoRemaining);
}

/**
 * @brief Event called every frame, if ticking is enabled
 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
 */
void AWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bRecoil)
	{
		ApplyRecoil(DeltaSeconds);
	}

	if (bRecoilRecovery)
	{
		ApplyRecoilRecovery(DeltaSeconds);
	}
}

/**
 * @brief Equip the weapon
 * @param TargetCharacter The character that will use the weapon
 * @param IsNewWeapon Is this a new weapon?
 */
void AWeapon::Equip(AUSKCharacter* TargetCharacter, const bool IsNewWeapon)
{
	Character = TargetCharacter;
	if (!IsValid(Character))
	{
		return;
	}

	if (IsNewWeapon)
	{
		PlayerController = dynamic_cast<APlayerController*>(Character->GetController());
		const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPoint);
		Character->SetWeapon(this);	
	}
	
	SetActorRelativeTransform(WeaponTransform);
	SetActorHiddenInGame(false);
	PlayAnimation(EquipAnimation);
	TargetCharacter->OnWeaponUpdated();
	
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
		Character->GetWeapon()->SetActorHiddenInGame(true);
	}

	OnWeaponUnequipped.Broadcast();
	USK_LOG_INFO("Weapon unequipped");
}

/**
 * @brief Start firing the weapon
 */
void AWeapon::StartFiring()
{
	bIsFiring = true;
	ShotsRemaining = MaxShotsPerFireEvent;

	StartRecoil();
	switch (WeaponFireMode)
	{
	case EWeaponFireMode::SingleShot:
		StartFiringSingleShot();
		UKismetSystemLibrary::K2_SetTimer(this, "StopRecoil", RecoilRecoveryDelay, false);
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
	StopRecoil();
}

/**
 * @brief Add more ammo to the weapon
 * @param Amount The amount of ammo to add
 */
void AWeapon::AddAmmo(const int Amount)
{
	USK_LOG_DEBUG("Adding ammo to the weapon");
	if (bRequireReloading)
	{
		ReloadAmmoRemaining = FMath::Min(ReloadAmmoRemaining + Amount, Ammo);
	}
	else
	{
		AmmoRemaining = FMath::Min(AmmoRemaining + Amount, Ammo);
	}
	
	OnWeaponAmmoUpdated.Broadcast(this, AmmoRemaining, ReloadAmmoRemaining);
}

/**
 * @brief Remove ammo from the weapon
 * @param Amount The amount of ammo to remove
 */
void AWeapon::RemoveAmmo(const int Amount)
{
	USK_LOG_DEBUG("Removing ammo from the weapon");
	AmmoRemaining = FMath::Max(AmmoRemaining - Amount, 0);
	OnWeaponAmmoUpdated.Broadcast(this, AmmoRemaining, ReloadAmmoRemaining);	
	
	if (AmmoRemaining <= 0)
	{
		OnWeaponAmmoEmpty.Broadcast();
	}
}

/**
 * @brief Get the amount of ammo remaining
 * @return The amount of ammo remaining
 */
int AWeapon::GetAmmoRemaining() const
{
	return AmmoRemaining;
}

/**
 * @brief Get the amount of ammo that can be used when reloading
 * @return The amount of ammo that can be used when reloading
 */
int AWeapon::GetReloadAmmoRemaining() const
{
	return bRequireReloading ? ReloadAmmoRemaining : AmmoRemaining;
}

/**
 * @brief Reload the weapon
 */
void AWeapon::Reload()
{
	if (bIsReloading || !bRequireReloading || ReloadAmmoRemaining <= 0 || AmmoRemaining >= AmmoPerClip)
	{
		return;
	}

	USK_LOG_INFO("Reloading weapon");
	bIsReloading = true;
	StopRecoil();
	
	UAudioUtils::PlayRandomSound(this, ReloadSound);
	PlayAnimation(IsValid(Character) && Character->IsAiming() ? ReloadAimAnimation : ReloadAnimation);
	UKismetSystemLibrary::K2_SetTimer(this, "StopReloading", ReloadDuration, false);
}

/**
 * @brief Start applying recoil to the weapon
 */
void AWeapon::StartRecoil()
{
	if (!IsValid(RecoilCurve))
	{
		return;
	}

	StopRecoilRecovery();
	PlayerDeltaRot = FRotator::ZeroRotator;
	RecoilDeltaRot = FRotator::ZeroRotator;
	RecoilStartRotation = UKismetMathLibrary::NormalizedDeltaRotator(
		PlayerController->GetControlRotation(), FRotator::ZeroRotator);
			
	bRecoil = true;
	bRecoilRecovery = false;
}

/**
 * @brief Stop applying recoil to the weapon
 */
void AWeapon::StopRecoil()
{
	if (!IsValid(RecoilCurve) || !bRecoil)
	{
		return;
	}
	
	bRecoil = false;
	StartRecoilRecovery();
}

/**
 * @brief Apply recoil to the weapon
 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
 */
void AWeapon::ApplyRecoil(const float DeltaSeconds)
{
	RecoilTime += DeltaSeconds;
	FRotator Recoil = FRotator::MakeFromEuler(RecoilCurve->GetVectorValue(RecoilTime));
	Recoil.Roll = 0;
	
	PlayerDeltaRot = PlayerController->GetControlRotation() - RecoilStartRotation - RecoilDeltaRot;
	PlayerController->SetControlRotation(RecoilStartRotation + PlayerDeltaRot + Recoil);
	RecoilDeltaRot = Recoil;
}

/**
 * @brief Start recovering from recoil
 */
void AWeapon::StartRecoilRecovery()
{
	bRecoilRecovery = true;
	RecoilRecoveryTimeRemaining = RecoveryTime;

	const float MaxAdjustment = FMath::Max3(RecoilDeltaRot.Pitch, RecoilDeltaRot.Roll, RecoilDeltaRot.Yaw);
	RecoilRecoverySpeed = MaxAdjustment / RecoveryTime;
}

/**
 * @brief Stop recovering from recoil
 */
void AWeapon::StopRecoilRecovery()
{
	bRecoilRecovery = false;
	RecoilTime = 0.0f;
	RecoilDeltaRot = FRotator::ZeroRotator;
	PlayerDeltaRot = FRotator::ZeroRotator;
}

/**
 * @brief Recover from recoil
 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
 */
void AWeapon::ApplyRecoilRecovery(const float DeltaSeconds)
{
	if (RecoilRecoveryTimeRemaining >= 0.0f)
	{
		const FRotator CurrentRotation = PlayerController->GetControlRotation();
		RecoilRecoveryTimeRemaining -= DeltaSeconds;
		PlayerController->SetControlRotation(UKismetMathLibrary::RInterpTo(PlayerController->GetControlRotation(),
			PlayerController->GetControlRotation() - RecoilDeltaRot, DeltaSeconds, RecoilRecoverySpeed));
		RecoilDeltaRot = RecoilDeltaRot + (PlayerController->GetControlRotation() - CurrentRotation);
		return;
	}

	StopRecoilRecovery();
}

/**
 * @brief Fire a single shot weapon
 */
void AWeapon::StartFiringSingleShot()
{
	if (!bIsFiring || bIsReloading || !IsValid(Character) || !IsValid(Character->GetController()))
	{
		return;
	}

	if (!bInfiniteAmmo && AmmoRemaining <= 0)
	{
		if (bRequireReloading && bAutoReloadWhenFiringWhileEmpty && ReloadAmmoRemaining > 0)
		{
			Reload();
			return;
		}

		StopRecoil();
		UAudioUtils::PlayRandomSound(this, EmptyClipFireSound);
		PlayAnimation(EmptyClipFireAnimation);
		OnWeaponFiredEmptyClip.Broadcast();
		return;
	}

	if (!bInfiniteAmmo)
	{
		RemoveAmmo(1);
	}
	
	UAudioUtils::PlayRandomSound(this, FireSound);
	for (FWeaponProjectileData Projectile : Projectiles)
	{
		SpawnProjectile(Projectile);
	}

	if (IsValid(FireCameraShake))
	{
		UGameplayStatics::PlayWorldCameraShake(GetWorld(), FireCameraShake,
			GetActorLocation(), 1000.0f, 2000.0f, 1.0f);
	}

	if (IsValid(MuzzleFlashParticleFx))
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFlashParticleFx, MuzzleFlash, NAME_None,
			MuzzleFlashParticleFxTransform.GetLocation(), MuzzleFlashParticleFxTransform.Rotator(),
			MuzzleFlashParticleFxTransform.GetScale3D(), EAttachLocation::SnapToTarget, true,
			ENCPoolMethod::None);
	}
	
	PlayAnimation(FireAnimation);
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
		StopRecoil();
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
 * @brief Stop reloading and add ammo to the weapon
 */
void AWeapon::StopReloading()
{
	USK_LOG_INFO("Adding ammo to weapon after reloading");
	const int AmmoNeeded = FMath::Min(AmmoPerClip - AmmoRemaining, ReloadAmmoRemaining);
    ReloadAmmoRemaining = FMath::Max(ReloadAmmoRemaining - AmmoNeeded, 0);
    AmmoRemaining += AmmoNeeded;

	bIsReloading = false;
	OnWeaponAmmoUpdated.Broadcast(this, AmmoRemaining, ReloadAmmoRemaining);

	if (bIsFiring)
	{
		StartRecoil();
	}
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
 * @brief Play an animation montage
 * @param AnimMontage The animation montage to play
 */
void AWeapon::PlayAnimation(UAnimMontage* AnimMontage) const
{
	if (!IsValid(AnimMontage))
	{
		return;
	}

	Character->PlayAnimMontage(AnimMontage, 1.0f);
}