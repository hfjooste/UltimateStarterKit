// Created by Henry Jooste

#include "Effect.h"
#include "USK/Logger/Log.h"

/**
 * @brief Create a new instance of the AEffect actor
 */
AEffect::AEffect()
{
    PrimaryActorTick.bCanEverTick = true;
}

/**
 * @brief Overridable native event for when play begins for this actor
 */
void AEffect::BeginPlay()
{
	if (DeactivateDelay <= 0.0f)
	{
		DeactivateEffect();
		return;
	}

	FTimerHandle DeactivateTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(DeactivateTimerHandle, this, &AEffect::DeactivateEffect,
        DeactivateDelay, false);
}

/**
 * @brief Deactivate the effect
 */
void AEffect::DeactivateEffect()
{
    USK_LOG_TRACE("Deactivating effect");

    TArray<UActorComponent*> Components;
	GetComponents(Components);
	for (UActorComponent* Component : Components)
	{
		Component->Deactivate();
	}

	if (DestroyDelay <= 0.0f)
	{
		DestroyEffect();
		return;
	}

    FTimerHandle DestroyTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AEffect::DestroyEffect,
        DestroyDelay, false);
}

/**
 * @brief Destroy the actor
 */
void AEffect::DestroyEffect()
{
    USK_LOG_TRACE("Destroying effect");
    Destroy();
}