// Created by Henry Jooste

#include "BTTask_UskWander.h"

#include "EnemyWanderArea.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "USK/Character/USKEnemyCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the task node
 */
UBTTask_UskWander::UBTTask_UskWander()
{
	NodeName = "Wander";
}

/**
 * @brief Start executing the task
 * @param OwnerComp A reference to the behaviour tree executing the task
 * @param NodeMemory Memory block used to store runtime data
 * @return The result of the task (Succeeded, Failed or InProgress)
 */
EBTNodeResult::Type UBTTask_UskWander::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	const bool CanWanderRandomly = EnemyCharacter->bUseRandomWanderLocation &&
		(EnemyCharacter->bWanderRandomX || EnemyCharacter->bWanderRandomY || EnemyCharacter->bWanderRandomZ);
	const bool CanWanderInArea = !EnemyCharacter->bUseRandomWanderLocation &&
		(EnemyCharacter->WanderAreaIndex >= 0 && EnemyCharacter->WanderAreaIndex < EnemyCharacter->WanderAreas.Num());
	if (!CanWanderRandomly && !CanWanderInArea)
	{
		USK_LOG_ERROR("Invalid wander location setup");
		return EBTNodeResult::Failed;
	}

	if (!Blackboard->GetValueAsBool(WanderInitializedKey.SelectedKeyName))
	{
		UpdateLocation(Blackboard, EnemyCharacter);
		Blackboard->SetValueAsBool(WanderInitializedKey.SelectedKeyName, true);
	}

	if (EnemyCharacter->bPauseWhenLocationReached)
	{
		const float RemainingDelay = Blackboard->GetValueAsFloat(WanderPauseDelayKey.SelectedKeyName);
		if (RemainingDelay > 0.0f)
		{
			Blackboard->SetValueAsFloat(WanderPauseDelayKey.SelectedKeyName,
				RemainingDelay - GetWorld()->GetDeltaSeconds());
			return EBTNodeResult::Succeeded;
		}
	}

	const FVector TargetLocation = Blackboard->GetValueAsVector(WanderLocationKey.SelectedKeyName);
	
	bool TargetReached;
	if (!MoveToLocation(EnemyCharacter, TargetLocation, EnemyCharacter->AcceptanceRadius, TargetReached))
	{
		USK_LOG_ERROR("Failed to move to location");
		return EBTNodeResult::Failed;
	}

	if (TargetReached)
	{
		UpdateLocation(Blackboard, EnemyCharacter);
		OnTargetReached(Blackboard, EnemyCharacter);
	}
	
	return EBTNodeResult::Succeeded;
}

/**
 * @brief Update the wander location
 * @param Blackboard The blackboard component
 * @param EnemyCharacter The enemy character
 */
void UBTTask_UskWander::UpdateLocation(UBlackboardComponent* Blackboard, AUSKEnemyCharacter* EnemyCharacter) const
{
	FVector TargetLocation = Blackboard->GetValueAsVector(StartLocationKey.SelectedKeyName);
	if (EnemyCharacter->bUseRandomWanderLocation)
	{
		const float TargetX = EnemyCharacter->bWanderRandomX
			? FMath::RandRange(EnemyCharacter->RandomWanderXRange.X, EnemyCharacter->RandomWanderXRange.Y)
			: 0.0f;
		const float TargetY = EnemyCharacter->bWanderRandomY
			? FMath::RandRange(EnemyCharacter->RandomWanderYRange.X, EnemyCharacter->RandomWanderYRange.Y)
			: 0.0f;
		const float TargetZ = EnemyCharacter->bWanderRandomZ
			? FMath::RandRange(EnemyCharacter->RandomWanderZRange.X, EnemyCharacter->RandomWanderZRange.Y)
			: 0.0f;
		TargetLocation += FVector(TargetX, TargetY, TargetZ);
	}
	else
	{
		TargetLocation = EnemyCharacter->WanderAreas[EnemyCharacter->WanderAreaIndex]->GetRandomLocationInArea();
	}

	Blackboard->SetValueAsVector(WanderLocationKey.SelectedKeyName, TargetLocation);
}

/**
 * @brief Called after the target location is reached
 * @param Blackboard The blackboard component
 * @param EnemyCharacter The enemy character
 */
void UBTTask_UskWander::OnTargetReached(UBlackboardComponent* Blackboard, const AUSKEnemyCharacter* EnemyCharacter) const
{
	if (EnemyCharacter->bPauseWhenLocationReached)
    {
    	Blackboard->SetValueAsFloat(WanderPauseDelayKey.SelectedKeyName, EnemyCharacter->PauseDelay);
    }	
}
