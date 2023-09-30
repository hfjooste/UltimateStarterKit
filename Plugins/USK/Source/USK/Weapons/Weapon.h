// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
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
	
public:
	/**
	 * @brief The type of weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon")
	EWeaponType WeaponType;

	/**
	 * @brief The projectile spawned by the weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon")
	TSubclassOf<AWeaponProjectile> ProjectileClass;

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
	 * @brief The muzzle offset of the weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon")
	FVector MuzzleOffset;

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