// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EnemyWanderArea.generated.h"

/**
 * @brief An area in the world that an enemy can wander around in
 */
UCLASS()
class USK_API AEnemyWanderArea : public AActor
{
	GENERATED_BODY()

	/**
	 * @brief The area in which the enemy can wander
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UBoxComponent* WanderArea;
	
public:
	/**
	 * @brief Constructor for the enemy wander area
	 */
	AEnemyWanderArea();

	/**
	 * @brief Get a random location in the wander area
	 * @return A random location in the wander area
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|AI")
	FVector GetRandomLocationInArea() const;
};
