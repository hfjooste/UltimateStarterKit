// Created by Henry Jooste

#include "ShadowDecal.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "USK/Logger/Log.h"

/**
 * @brief Create a new instance of the AShadowDecal actor
 */
AShadowDecal::AShadowDecal()
{
	PrimaryActorTick.bCanEverTick = true;
}

/**
 * @brief Initialize the shadow decal
 * @param OwnerCharacter The character owning this shadow decal
 */
void AShadowDecal::Initialize(ACharacter* OwnerCharacter)
{
	USK_LOG_TRACE("Initializing shadow decal");
	Character = OwnerCharacter;

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true);
	AttachToActor(OwnerCharacter, AttachmentRules);
	GetDecal()->SetVisibility(false, true);
}

/**
 * @brief Event called every frame, if ticking is enabled
 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
 */
void AShadowDecal::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (Character == nullptr || !Character->GetMovementComponent()->IsFalling())
	{
		GetDecal()->SetVisibility(false, true);
		return;
	}

	float CapsuleRadius;
	float CapsuleHalfHeight;
	Character->GetCapsuleComponent()->GetUnscaledCapsuleSize(CapsuleRadius, CapsuleHalfHeight);

	const FVector Start = Character->GetActorLocation() -
		FVector(0.0f, 0.0f, CapsuleRadius + CapsuleHalfHeight + 25.0f);
	const FVector End = Character->GetActorLocation() - FVector(0.0f, 0.0f, 10000.0f);
	
	FHitResult HitResult;
	if (!UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, TraceTypeQuery1,
		false, TArray<AActor*>(), EDrawDebugTrace::None, HitResult, true))
	{
		GetDecal()->SetVisibility(false, true);
		return;
	}

	GetDecal()->SetWorldLocation(HitResult.Location);
	GetDecal()->SetVisibility(true, true);	
}
