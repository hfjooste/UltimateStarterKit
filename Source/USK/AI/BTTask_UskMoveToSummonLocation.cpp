// Created by Henry Jooste

#include "BTTask_UskMoveToSummonLocation.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "USK/Character/USKEnemyCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the task node
 */
UBTTask_UskMoveToSummonLocation::UBTTask_UskMoveToSummonLocation()
{
	NodeName = "Move To Summon Location";
}

/**
 * @brief Start executing the task
 * @param OwnerComp A reference to the behaviour tree executing the task
 * @param NodeMemory Memory block used to store runtime data
 * @return The result of the task (Succeeded, Failed or InProgress)
 */
EBTNodeResult::Type UBTTask_UskMoveToSummonLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	if (!Blackboard->IsVectorValueSet(SummonLocationKey.SelectedKeyName))
	{
		const FVector NewSummonLocation = GetLastReachableLocation(EnemyCharacter, EnemyCharacter->GetSummonLocation());
		Blackboard->SetValueAsVector(SummonLocationKey.SelectedKeyName, NewSummonLocation);
	}

	const FVector SummonLocation = Blackboard->GetValueAsVector(SummonLocationKey.SelectedKeyName);
	const float Distance = FVector::Dist(EnemyCharacter->GetActorLocation(), SummonLocation);
	if (Distance <= FocusLocationRadius)
	{
		FocusLocation(EnemyCharacter, SummonLocation);
	}

	bool TargetReached;
	if (!MoveToLocation(EnemyCharacter, SummonLocation, AcceptanceRadius, TargetReached))
	{
		USK_LOG_ERROR("Failed to move to location");
		return EBTNodeResult::Failed;
	}

	if (TargetReached)
	{
		ClearFocus(EnemyCharacter);
	}
	
	return EBTNodeResult::Succeeded;
}
