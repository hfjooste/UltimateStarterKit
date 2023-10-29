// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponProjectileDecal.generated.h"

/**
 * @brief A decal spawned when a projectile hits something
 */
UCLASS()
class USK_API AWeaponProjectileDecal : public AActor
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Should the decal automatically be destroyed?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon Projectile Decal")
	bool bAutomaticallyDestroy = true;

	/**
	 * @brief The lifetime of the decal
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Weapon Projectile Decal",
		meta=(EditCondition = "bAutomaticallyDestroy", EditConditionHides))
	float Lifetime = 10.0f;

	/**
	 * @brief Create a new instance of the AWeaponProjectile actor
	 */
	AWeaponProjectileDecal();

protected:
	/**
	 * @brief Overridable native event for when play begins for this actor
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Destroy the decal actor
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ultimate Starter Kit|Weapon Projectile Decal")
	void DestroyDecal();
};