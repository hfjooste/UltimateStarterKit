// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "WeaponFireMode.h"
#include "GameFramework/Actor.h"
#include "Animation/AnimMontage.h"
#include "WeaponProjectileData.h"
#include "WeaponType.h"
#include "Curves/CurveVector.h"
#include "Weapon.generated.h"

class AUSKCharacter;

/**
 * @brief The weapon attached to characters
 */
UCLASS()
class USK_API AWeapon : public AActor
{
	GENERATED_BODY()

	/**
	 * @brief Event used to notify other classes when the weapon is equipped
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponEquipped);

	/**
	 * @brief Event used to notify other classes when the weapon is unequipped
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponUnequipped);

	/**
	 * @brief Event used to notify other classes when the weapon is fired
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFired);

	/**
	 * @brief Event used to notify other classes when the weapon is fired with an empty clip
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFiredEmptyClip);

	/**
	 * @brief Event used to notify other classes when the ammo is updated
	 * @param RemainingAmmo The amount of ammo remaining
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponAmmoUpdated, int, RemainingAmmo);

	/**
	 * @brief Event used to notify other classes when the ammo is empty
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponAmmoEmpty);

	/**
	 * @brief The muzzle flash of the weapon
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Weapon",
		meta=(AllowPrivateAccess = "true"))
	class USceneComponent* MuzzleFlash;
	
public:
	/**
	 * @brief The type of weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon|Information")
	EWeaponType WeaponType;

	/**
	 * @brief The fire mode of weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon|Information")
	EWeaponFireMode WeaponFireMode;

	/**
	 * @brief The fire rate of the weapon (amount of seconds between each shot)
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon|Firing",
		meta=(EditCondition = "WeaponFireMode == EWeaponFireMode::SemiAuto || WeaponFireMode == EWeaponFireMode::FullAuto",
			EditConditionHides))
	float FireRate = 0.2f;

	/**
	 * @brief The amount of shots fired per fire event
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon|Firing",
		meta=(EditCondition = "WeaponFireMode == EWeaponFireMode::SemiAuto", EditConditionHides))
	int MaxShotsPerFireEvent = 3;

	/**
	 * @brief The projectiles spawned by the weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon|Firing")
	TArray<FWeaponProjectileData> Projectiles;

	/**
	 * @brief Does the weapon have an infinite amount of ammo?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon|Ammo")
	bool bInfiniteAmmo;

	/**
	 * @brief The amount of ammo for the weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon|Ammo",
		meta=(EditCondition = "!bInfiniteAmmo", EditConditionHides))
	int Ammo = 50;

	/**
	 * @brief The attach point used by all weapons
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon|Attachment")
	FName WeaponAttachPoint;

	/**
	 * @brief The relative transform of the weapon after it is attached to a character
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon|Attachment")
	FTransform WeaponTransform;

	/**
	 * @brief The curve used to add recoil to the weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon|Recoil")
	UCurveVector* RecoilCurve;

	/**
	 * @brief The recovery time after recoil was applied
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon|Recoil",
		meta=(EditCondition = "RecoilCurve != nullptr", EditConditionHides))
	float RecoveryTime = 1.0f;

	/**
	 * @brief The delay before we start recovering from recoil
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon|Recoil",
		meta=(EditCondition = "RecoilCurve != nullptr && WeaponFireMode == EWeaponFireMode::SingleSHot",
			EditConditionHides))
	float RecoilRecoveryDelay = 0.15f;

	/**
	 * @brief The muzzle flash particle effects
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon|Effects")
	UNiagaraSystem* MuzzleFlashParticleFx;

	/**
	 * @brief The sound played each time the weapon is fired
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon|Effects")
	USoundBase* FireSound;

	/**
	 * @brief The sound played each time the weapon is fired with an empty clip
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon|Effects")
	USoundBase* EmptyClipFireSound;

	/**
	 * @brief The animation played when the weapon is fired
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon|Animations")
	UAnimMontage* FireAnimation;

	/**
	 * @brief The animation played when the weapon is fired with an empty clip
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon|Animations")
	UAnimMontage* EmptyClipFireAnimation;

	/**
	 * @brief Event used to notify other classes when the weapon is equipped
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Weapon|Events")
	FWeaponEquipped OnWeaponEquipped;

	/**
	 * @brief Event used to notify other classes when the weapon is unequipped
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Weapon|Events")
	FWeaponUnequipped OnWeaponUnequipped;

	/**
	 * @brief Event used to notify other classes when the weapon is fired
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Weapon|Events")
	FWeaponFired OnWeaponFired;

	/**
	 * @brief Event used to notify other classes when the weapon is fired with an empty clip
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Weapon|Events")
	FWeaponFiredEmptyClip OnWeaponFiredEmptyClip;

	/**
	 * @brief Event used to notify other classes when the ammo is updated
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Weapon|Events")
	FWeaponAmmoUpdated OnWeaponAmmoUpdated;

	/**
	 * @brief Event used to notify other classes when the ammo is empty
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Weapon|Events")
	FWeaponAmmoEmpty OnWeaponAmmoEmpty;

	/**
	 * @brief Create a new instance of the AWeapon actor
	 */
	AWeapon();

	/**
	 * @brief Equip the weapon
	 * @param TargetCharacter The character that will use the weapon
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Weapon")
	void Equip(AUSKCharacter* TargetCharacter);

	/**
	 * @brief Unequip the weapon
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Weapon")
	void Unequip();

	/**
	 * @brief Start firing the weapon
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Weapon")
	void StartFiring();

	/**
	 * @brief Stop firing the weapon
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Weapon")
	void StopFiring();

	/**
	 * @brief Add more ammo to the weapon
	 * @param Amount The amount of ammo to add
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Weapon")
	void AddAmmo(int Amount);

	/**
	 * @brief Remove ammo from the weapon
	 * @param Amount The amount of ammo to remove
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Weapon")
	void RemoveAmmo(int Amount);

	/**
	 * @brief Get the amount of ammo remaining
	 * @return The amount of ammo remaining
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Weapon")
	int GetAmmoRemaining() const;	

protected:
	/**
	 * @brief Overridable native event for when play begins for this actor
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Event called every frame, if ticking is enabled
	 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
	 */
	virtual void Tick(float DeltaSeconds) override;

	/**
	 * @brief Start applying recoil to the weapon
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Weapon")
	void StartRecoil();

	/**
	 * @brief Stop applying recoil to the weapon
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Weapon")
	void StopRecoil();

	/**
	 * @brief Apply recoil to the weapon
	 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Weapon")
	void ApplyRecoil(float DeltaSeconds);

	/**
	 * @brief Start recovering from recoil
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Weapon")
	void StartRecoilRecovery();

	/**
	 * @brief Stop recovering from recoil
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Weapon")
	void StopRecoilRecovery();

	/**
	 * @brief Recover from recoil
	 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Weapon")
	void ApplyRecoilRecovery(float DeltaSeconds);

private:
	/**
	 * @brief A reference to the owner character
	 */
	UPROPERTY()
	AUSKCharacter* Character;

	/**
	 * @brief A reference to the player controller
	 */
	UPROPERTY()
	APlayerController* PlayerController;

	/**
	 * @brief Is the weapon currently being fired?
	 */
	bool bIsFiring;

	/**
	 * @brief The amount of shots remaining before the weapon stops firing
	 */
	int ShotsRemaining;

	/**
	 * @brief The amount of ammo remaining
	 */
	int AmmoRemaining;

	/**
	 * @brief Are we currently applying recoil to the weapon?
	 */
	bool bRecoil;

	/**
	 * @brief Are we currently recovering from recoil?
	 */
	bool bRecoilRecovery;

	/**
	 * @brief The amount of time we have been applying recoil
	 */
	float RecoilTime;

	/**
	 * @brief The speed used to recover from recoil
	 */
	float RecoilRecoverySpeed;

	/**
	 * @brief The amount of time remaining to recover from recoil
	 */
	float RecoilRecoveryTimeRemaining;

	/**
	 * @brief The rotation before we start applying recoil
	 */
	FRotator RecoilStartRotation;

	/**
	 * @brief The rotation change that was applied because of recoil
	 */
	FRotator RecoilDeltaRot;

	/**
	 * @brief The rotation change due to player input
	 */
	FRotator PlayerDeltaRot;

	/**
	 * @brief Fire a single shot weapon
	 */
	UFUNCTION()
	void StartFiringSingleShot();

	/**
	 * @brief Fire a semi-auto weapon
	 */
	UFUNCTION()
	void StartFiringSemiAuto();

	/**
	 * @brief Fire a full auto weapon
	 */
	UFUNCTION()
	void StartFiringFullAuto();

	/**
	 * @brief Spawn the projectile
	 * @param Projectile The projectile to spawn
	 */
	void SpawnProjectile(const FWeaponProjectileData& Projectile) const;

	/**
	 * @brief Play the fire animation
	 */
	void PlayFireAnimation() const;

	/**
	 * @brief Play the empty clip fire animation
	 */
	void PlayEmptyClipFireAnimation() const;
};