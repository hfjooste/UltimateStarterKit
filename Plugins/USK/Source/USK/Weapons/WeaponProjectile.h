// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponProjectile.generated.h"

/**
 * @brief The projectile spawned by weapons
 */
UCLASS()
class USK_API AWeaponProjectile : public AActor
{
	GENERATED_BODY()

	/**
	 * @brief The collision component used by the projectile
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Weapon Projectile",
		meta=(AllowPrivateAccess = "true"))
	class USphereComponent* CollisionComponent;

	/**
	 * @brief The projectile movement component used to move the projectile
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Weapon Projectile",
		meta=(AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovementComponent;

public:
	/**
	 * @brief Should the projectile be destroyed after hitting something?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon Projectile")
	bool bDestroyOnHit = true;

	/**
	 * @brief The impulse applied to the component that was hit
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon Projectile")
	float HitImpulse;
	
	/**
	 * @brief Create a new instance of the AWeaponProjectile actor
	 */
	AWeaponProjectile();

	/**
	 * @brief Get the collision component used by the projectile
	 * @return The collision component used by the projectile
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Weapon Projectile")
	USphereComponent* GetCollisionComponent() const;

	/**
	 * @brief Get the projectile movement component used to move the projectile
	 * @return The projectile movement component used to move the projectile
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Weapon Projectile")
	UProjectileMovementComponent* GetProjectileMovementComponent() const;

protected:
	/**
	 * @brief Called after the projectile hits something
	 * @param HitComponent The component responsible for the hit
	 * @param OtherActor The actor that was hit
	 * @param OtherComponent The component that was hit
	 * @param NormalImpulse The normal impulse of the hit
	 * @param HitResult Result describing the hit
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Ultimate Starter Kit|Weapon Projectile")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse, const FHitResult& HitResult);
};
