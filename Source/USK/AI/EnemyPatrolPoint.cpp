// Created by Henry Jooste

#include "EnemyPatrolPoint.h"

/**
 * @brief Overridable native event for when play begins for this actor
 */
void AEnemyPatrolPoint::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle DestroyTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, [this]
	{
		Destroy();
	}, DestroyDelay, false);
}