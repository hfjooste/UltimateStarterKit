// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "WeaponFireMode.h"
#include "GameFramework/Actor.h"
#include "Animation/AnimMontage.h"
#include "WeaponProjectile.h"
#include "WeaponProjectileData.h"
#include "WeaponType.h"
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
	 * @brief The muzzle flash of the weapon
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Weapon",
		meta=(AllowPrivateAccess = "true"))
	class USceneComponent* MuzzleFlash;
	
public:
	/**
	 * @brief The type of weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon")
	EWeaponType WeaponType;

	/**
	 * @brief The fire mode of weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon")
	EWeaponFireMode WeaponFireMode;

	/**
	 * @brief The fire rate of the weapon (amount of seconds between each shot)
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon",
		meta=(EditCondition = "WeaponFireMode == EWeaponFireMode::SemiAuto || WeaponFireMode == EWeaponFireMode::FullAuto",
			EditConditionHides))
	float FireRate = 0.2f;

	/**
	 * @brief The amount of shots fired per fire event
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon",
		meta=(EditCondition = "WeaponFireMode == EWeaponFireMode::SemiAuto", EditConditionHides))
	int MaxShotsPerFireEvent = 3;

	/**
	 * @brief The attach point used by all weapons
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Weapon")
	FName WeaponAttachPoint;

	/**
	 * @brief The relative transform of the weapon after it is attached to a character
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Weapon")
	FTransform WeaponTransform;

	/**
	 * @brief The projectiles spawned by the weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon")
	TArray<FWeaponProjectileData> Projectiles;

	/**
	 * @brief The muzzle flash particle effects
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Weapon")
	UNiagaraSystem* MuzzleFlashParticleFx;

	/**
	 * @brief The sound played each time the weapon is fired
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon")
	USoundBase* FireSound;

	/**
	 * @brief The animation played when the weapon is fired
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon")
	UAnimMontage* FireAnimation;

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

private:
	/**
	 * @brief A reference to the owner character
	 */
	UPROPERTY()
	AUSKCharacter* Character;

	/**
	 * @brief Is the weapon currently being fired?
	 */
	bool bIsFiring;

	/**
	 * @brief The amount of shots remaining before the weapon stops firing
	 */
	int ShotsRemaining;

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
};