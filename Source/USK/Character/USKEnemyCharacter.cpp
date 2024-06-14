// Created by Henry Jooste

#include "USKEnemyCharacter.h"

#include "AIController.h"
#include "Algo/RandomShuffle.h"
#include "USK/AI/EnemyPatrolPoint.h"

/**
 * @brief Overridable native event for when play begins for this actor
 */
void AUSKEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitializePatrolPoints();
	
	if (IsValid(BehaviorTree))
	{
		AAIController* AiController = dynamic_cast<AAIController*>(GetController());
		if (IsValid(AiController))
		{
			AiController->RunBehaviorTree(BehaviorTree);
		}
	}
}

/**
 * @brief Get the array of patrol point locations
 * @return The array of patrol point locations
 */
TArray<FVector> AUSKEnemyCharacter::GetPatrolPointLocations()
{
	return PatrolPointLocations;
}

/**
 * @brief Update the dead state of the enemy
 * @param NewValue The new dead state value
 */
void AUSKEnemyCharacter::UpdateDeadState(const bool NewValue)
{
	bIsDead = NewValue;
}

/**
 * @brief Check if the enemy is dead
 * @return A boolean value indicating if the enemy is dead
 */
bool AUSKEnemyCharacter::IsDead() const
{
	return bIsDead;
}

/**
 * @brief Start attacking the target
 * @param AttackType The type of attack to start
 */
void AUSKEnemyCharacter::StartAttacking(const EEnemyAttackType AttackType)
{
	CurrentAttackType = AttackType;
}

/**
 * @brief Stop attacking the target
 */
void AUSKEnemyCharacter::StopAttacking()
{
	CurrentAttackType = EEnemyAttackType::None;
}

/**
 * @brief Get the current attack type of the enemy
 * @return The current attack type of the enemy
 */
EEnemyAttackType AUSKEnemyCharacter::GetCurrentAttackType() const
{
	return CurrentAttackType;
}

/**
 * @brief Initialize the patrol points
 */
void AUSKEnemyCharacter::InitializePatrolPoints()
{
	for (const AEnemyPatrolPoint* PatrolPoint : PatrolPoints)
	{
		PatrolPointLocations.Add(PatrolPoint->GetActorLocation());
	}

	if (PatrolType == EPatrolType::ReverseDirection)
	{
		for (int Index = PatrolPointLocations.Num() - 2; Index > 0; --Index)
		{
			PatrolPointLocations.Add(PatrolPoints[Index]->GetActorLocation());
		}
	}

	if (PatrolType == EPatrolType::RandomLocation)
	{
		Algo::RandomShuffle(PatrolPointLocations);
	}
}