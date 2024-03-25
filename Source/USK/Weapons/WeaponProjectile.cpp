// Created by Henry Jooste

#include "WeaponProjectile.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "USK/Audio/AudioUtils.h"
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
	if (IsValid(OtherComponent) && !FMath::IsNearlyZero(HitImpulse) && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(GetVelocity() * HitImpulse, GetActorLocation());
	}

	ProcessHitReaction(OtherActor, HitResult);
	SpawnDecal(OtherActor, HitResult);
	
	if (bDestroyOnHit)
	{
		Destroy();	
	}
}

/**
 * @brief Process the hit reaction of the projectile
 * @param OtherActor The actor that was hit
 * @param HitResult The result describing the hit
 */
void AWeaponProjectile::ProcessHitReaction(AActor* OtherActor, const FHitResult& HitResult)
{
	FWeaponProjectileHitData HitReaction = DefaultHitReaction;
	for (const TTuple<TSubclassOf<AActor>, FWeaponProjectileHitData> HitReactionData : HitReactions)
	{
		if (OtherActor->IsA(HitReactionData.Key))
		{
			HitReaction = HitReactionData.Value;
			break;
		}
	}

	if (IsValid(HitReaction.HitParticleFx))
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitReaction.HitParticleFx,
			HitResult.Location + HitReaction.HitParticleFxTransform.GetLocation(),
			HitReaction.HitParticleFxTransform.Rotator(), HitReaction.HitParticleFxTransform.GetScale3D());
	}
	
	UAudioUtils::PlayRandomSound(OtherActor, HitReaction.HitSfx);
}

/**
 * @brief Spawn a decal at the hit location
 * @param OtherActor The actor that was hit
 * @param HitResult The result describing the hit
 */
void AWeaponProjectile::SpawnDecal(const AActor* OtherActor, const FHitResult& HitResult)
{
	TSubclassOf<AWeaponProjectileDecal> Decal = DefaultDecal;
	for (const TTuple<TSubclassOf<AActor>, TSubclassOf<AWeaponProjectileDecal>> DecalData : Decals)
	{
		if (OtherActor->IsA(DecalData.Key))
		{
			Decal = DecalData.Value;
			break;
		}
	}

	if (!IsValid(Decal))
	{
		return;
	}

	USK_LOG_TRACE("Spawning projectile decal");
	const FTransform DecalTransform = FTransform(HitResult.ImpactNormal.Rotation(), HitResult.ImpactPoint);
	GetWorld()->SpawnActor<AWeaponProjectileDecal>(Decal, DecalTransform);
}
