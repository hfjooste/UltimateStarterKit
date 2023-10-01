// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "Animation/AnimMontage.h"
#include "WeaponProjectile.h"
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
	 * @brief The projectile spawned by the weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon")
	TSubclassOf<AWeaponProjectile> ProjectileClass;

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
	 * @brief Create a new instance of the AWeapon actor
	 */
	AWeapon();

	/**
	 * @brief Attach the weapon to a character
	 * @param TargetCharacter The character that will use the weapon
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Weapon")
	void AttachWeapon(AUSKCharacter* TargetCharacter);

	/**
	 * @brief Fire the weapon
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Weapon")
	void Fire();

private:
	/**
	 * @brief A reference to the owner character
	 */
	UPROPERTY()
	AUSKCharacter* Character;

	/**
	 * @brief Spawn the projectile
	 */
	void SpawnProjectile() const;

	/**
	 * @brief Play the fire animation
	 */
	void PlayFireAnimation() const;
};