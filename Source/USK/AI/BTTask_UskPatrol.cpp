// Created by Henry Jooste

#include "BTTask_UskPatrol.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "USK/Character/USKEnemyCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the task node
 */
UBTTask_UskPatrol::UBTTask_UskPatrol()
{
	NodeName = "Patrol";
}

/**
 * @brief Start executing the task
 * @param OwnerComp A reference to the behaviour tree executing the task
 * @param NodeMemory Memory block used to store runtime data
 * @return The result of the task (Succeeded, Failed or InProgress)
 */
EBTNodeResult::Type UBTTask_UskPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(Blackboard))
	{
		USK_LOG_ERROR("Blackboard is invalid");
		return EBTNodeResult::Failed;
	}

	AUSKEnemyCharacter* EnemyCharacter = dynamic_cast<AUSKEnemyCharacter*>(
		Blackboard->GetValueAsObject(OwnerKey.SelectedKeyName));
	if (!IsValid(EnemyCharacter))
	{
		USK_LOG_ERROR("Enemy character is invalid");
		return EBTNodeResult::Failed;
	}

	if (EnemyCharacter->GetPatrolPointLocations().IsEmpty())
	{
		USK_LOG_ERROR("Patrol points not set up");
		return EBTNodeResult::Failed;
	}

	if (EnemyCharacter->bPauseWhenLocationReached)
	{
		const float RemainingDelay = Blackboard->GetValueAsFloat(PatrolPointPauseDelayKey.SelectedKeyName);
		if (RemainingDelay > 0.0f)
		{
			Blackboard->SetValueAsFloat(PatrolPointPauseDelayKey.SelectedKeyName,
				RemainingDelay - GetWorld()->GetDeltaSeconds());
			return EBTNodeResult::Succeeded;
		}
	}

	const int PatrolPointIndex = Blackboard->GetValueAsInt(PatrolPointIndexKey.SelectedKeyName);
	const FVector PatrolPoint = EnemyCharacter->GetPatrolPointLocations()[PatrolPointIndex];
	
	bool TargetReached;
	if (!MoveToLocation(EnemyCharacter, PatrolPoint, EnemyCharacter->AcceptanceRadius, TargetReached))
	{
		USK_LOG_ERROR("Failed to move to location");
		return EBTNodeResult::Failed;
	}

	if (TargetReached)
	{
		OnTargetReached(Blackboard, EnemyCharacter, PatrolPointIndex);
	}
	
	return EBTNodeResult::Succeeded;
}

/**
 * @brief Called after the target location is reached
 * @param Blackboard The blackboard component
 * @param EnemyCharacter The enemy character
 * @param PatrolPointIndex The current patrol point index
 */
void UBTTask_UskPatrol::OnTargetReached(UBlackboardComponent* Blackboard, AUSKEnemyCharacter* EnemyCharacter,
	const int PatrolPointIndex) const
{
	if (EnemyCharacter->GetPatrolPointLocations().Num() > 1)
	{
		int NextPatrolPointIndex = PatrolPointIndex;
		if (EnemyCharacter->PatrolType == EPatrolType::RandomLocation)
		{
			while (NextPatrolPointIndex == PatrolPointIndex)
			{
				NextPatrolPointIndex = FMath::RandRange(0, EnemyCharacter->GetPatrolPointLocations().Num() - 1);
			} 
		}
		else
		{
			const bool LastPointReached = PatrolPointIndex >= EnemyCharacter->GetPatrolPointLocations().Num() - 1;
			NextPatrolPointIndex = LastPointReached ? 0 : PatrolPointIndex + 1;
		}

		Blackboard->SetValueAsInt(PatrolPointIndexKey.SelectedKeyName, NextPatrolPointIndex);	
	}
	
	if (EnemyCharacter->bPauseWhenLocationReached)
    {
    	Blackboard->SetValueAsFloat(PatrolPointPauseDelayKey.SelectedKeyName, EnemyCharacter->PauseDelay);
    }	
}
