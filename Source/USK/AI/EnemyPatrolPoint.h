// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "EnemyPatrolPoint.generated.h"

/**
 * @brief A point in the world that an enemy can patrol to
 */
UCLASS()
class USK_API AEnemyPatrolPoint : public AActor
{
	GENERATED_BODY()

public:
	/**
	 * @brief The delay before the patrol point is destroyed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	float DestroyDelay = 1.0f;

protected:
	/**
	 * @brief Overridable native event for when play begins for this actor
	 */
	virtual void BeginPlay() override;
};
