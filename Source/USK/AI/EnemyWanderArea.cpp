// Created by Henry Jooste

#include "EnemyWanderArea.h"

/**
 * @brief Constructor for the enemy wander area
 */
AEnemyWanderArea::AEnemyWanderArea()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	WanderArea = CreateDefaultSubobject<UBoxComponent>(TEXT("WanderArea"));
	WanderArea->SetupAttachment(RootComponent);
}

/**
 * @brief Get a random location in the wander area
 * @return A random location in the wander area
 */
FVector AEnemyWanderArea::GetRandomLocationInArea() const
{
	const FVector Origin = WanderArea->Bounds.Origin;
	const FVector Extent = WanderArea->Bounds.BoxExtent;

	return FVector(FMath::RandRange(Origin.X - Extent.X, Origin.X + Extent.X),
		FMath::RandRange(Origin.Y - Extent.Y, Origin.Y + Extent.Y),
		FMath::RandRange(Origin.Z - Extent.Z, Origin.Z + Extent.Z));
}
