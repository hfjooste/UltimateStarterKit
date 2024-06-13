// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "EnemyAttackType.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "USK/AI/PatrolType.h"
#include "USKEnemyCharacter.generated.h"

class AEnemyWanderArea;
class AEnemyPatrolPoint;

/**
 * @brief Base class for all enemy characters
 */
UCLASS()
class USK_API AUSKEnemyCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The behavior tree to use for the enemy character
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	UBehaviorTree* BehaviorTree;

	/**
	 * @brief The class of the actor the enemy will target
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	TSubclassOf<AActor> TargetActorClass;

	/**
	 * @brief Should the AI be paused when the target location is reached?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	bool bPauseWhenLocationReached = true;

	/**
	 * @brief The delay in seconds before the AI starts moving again
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI",
		meta=(EditCondition = "PauseWhenLocationReached", EditConditionHides))
	float PauseDelay = 3.0f;

	/**
	 * @brief The radius around the target location before it is considered reached
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	float AcceptanceRadius = 100.0f;

	/**
	 * @brief An array of areas where the enemy can wander
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI|Wander")
	TArray<AEnemyWanderArea*> WanderAreas;

	/**
	 * @brief Should the enemy wander randomly?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI|Wander")
	bool bUseRandomWanderLocation = true;

	/**
	 * @brief Should a random X location be used for wandering?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI|Wander",
		meta=(EditCondition = "bUseRandomWanderLocation", EditConditionHides))
	bool bWanderRandomX = true;

	/**
	 * @brief The range of random X locations used when picking a new wander location
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI|Wander",
		meta=(EditCondition = "bUseRandomWanderLocation && bWanderRandomX", EditConditionHides))
	FVector2D RandomWanderXRange = FVector2D(-2500.0f, 2500.0f);

	/**
	 * @brief Should a random Y location be used for wandering?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI|Wander",
		meta=(EditCondition = "bUseRandomWanderLocation", EditConditionHides))
	bool bWanderRandomY = true;

	/**
	 * @brief The range of random Y locations used when picking a new wander location
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI|Wander",
		meta=(EditCondition = "bUseRandomWanderLocation && bWanderRandomY", EditConditionHides))
	FVector2D RandomWanderYRange = FVector2D(-2500.0f, 2500.0f);

	/**
	 * @brief Should a random Z location be used for wandering?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI|Wander",
		meta=(EditCondition = "bUseRandomWanderLocation", EditConditionHides))
	bool bWanderRandomZ = false;

	/**
	 * @brief The range of random Z locations used when picking a new wander location
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI|Wander",
		meta=(EditCondition = "bUseRandomWanderLocation && bWanderRandomZ", EditConditionHides))
	FVector2D RandomWanderZRange = FVector2D(0.0f, 2500.0f);

	/**
	 * @brief The index of the wander area to use when wandering
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI|Wander",
		meta=(EditCondition = "!bUseRandomWanderLocation", EditConditionHides))
	int WanderAreaIndex = 0;

	/**
	 * @brief The array of patrol points the enemy will move between
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI|Patrol")
	TArray<AEnemyPatrolPoint*> PatrolPoints;

	/**
	 * @brief The type of patrol movement the enemy will use
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI|Patrol")
	EPatrolType PatrolType;

	/**
	 * @brief Get the array of patrol point locations
	 * @return The array of patrol point locations
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|AI")
	TArray<FVector> GetPatrolPointLocations();

	/**
	 * @brief Update the dead state of the enemy
	 * @param NewValue The new dead state value
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|AI")
	void UpdateDeadState(bool NewValue);

	/**
	 * @brief Check if the enemy is dead
	 * @return A boolean value indicating if the enemy is dead
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|AI")
	bool IsDead() const;

	/**
	 * @brief Start attacking the target
	 * @param AttackType The type of attack to start
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|AI")
	void StartAttacking(EEnemyAttackType AttackType);

	/**
	 * @brief Stop attacking the target
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|AI")
	void StopAttacking();

	/**
	 * @brief Check if the enemy is attacking
	 * @return A boolean value indicating if the enemy is attacking
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|AI")
	bool IsAttacking() const;

protected:
	/**
	 * @brief Overridable native event for when play begins for this actor
	 */
	virtual void BeginPlay() override;

private:
	/**
	 * @brief The array of patrol point locations
	 */
	TArray<FVector> PatrolPointLocations;

	/**
	 * @brief Is the enemy dead?
	 */
	bool bIsDead;

	/**
	 * @brief Is the enemy attacking?
	 */
	bool bIsAttacking;

	/**
	 * @brief Initialize the patrol points
	 */
	void InitializePatrolPoints();
};
