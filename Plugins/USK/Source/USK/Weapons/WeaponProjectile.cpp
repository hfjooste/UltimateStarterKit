// Created by Henry Jooste

#include "WeaponProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "USK/Logger/Log.h"

/**
 * @brief Create a new instance of the AWeaponProjectile actor
 */
AWeaponProjectile::AWeaponProjectile()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComponent->OnComponentHit.AddDynamic(this, &AWeaponProjectile::OnHit);
	CollisionComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.0f));
	CollisionComponent->CanCharacterStepUpOn = ECB_No;
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovementComponent->UpdatedComponent = CollisionComponent;
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;

	RootComponent = CollisionComponent;
	InitialLifeSpan = 3.0f;
}

/**
 * @brief Get the collision component used by the projectile
 * @return The collision component used by the projectile
 */
USphereComponent* AWeaponProjectile::GetCollisionComponent() const
{
	return CollisionComponent;
}

/**
 * @brief Get the projectile movement component used to move the projectile
 * @return The projectile movement component used to move the projectile
 */
UProjectileMovementComponent* AWeaponProjectile::GetProjectileMovementComponent() const
{
	return ProjectileMovementComponent;
}

/**
 * @brief Called after the projectile hits something
 * @param HitComponent The component responsible for the hit
 * @param OtherActor The actor that was hit
 * @param OtherComponent The component that was hit
 * @param NormalImpulse The normal impulse of the hit
 * @param HitResult Result describing the hit
 */
void AWeaponProjectile::OnHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult)
{
	if (!IsValid(OtherActor) || OtherActor == this)
	{
		return;
	}

	USK_LOG_TRACE(*FString::Format(TEXT("Projectile hit {0}"), { OtherActor->GetName() }));
	if (IsValid(OtherActor) && IsValid(OtherComponent) && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	}

	if (bDestroyOnHit)
	{
		Destroy();	
	}
}