// Created by Henry Jooste

#include "BTTask_UskUpdateState.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "USK/Character/USKEnemyCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the task node
 */
UBTTask_UskUpdateState::UBTTask_UskUpdateState()
{
	NodeName = "Update State";
}

/**
 * @brief Start executing the task
 * @param OwnerComp A reference to the behaviour tree executing the task
 * @param NodeMemory Memory block used to store runtime data
 * @return The result of the task (Succeeded, Failed or InProgress)
 */
EBTNodeResult::Type UBTTask_UskUpdateState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(Blackboard))
	{
		USK_LOG_ERROR("Blackboard is invalid");
		return EBTNodeResult::Failed;
	}

	const AUSKEnemyCharacter* EnemyCharacter = dynamic_cast<AUSKEnemyCharacter*>(
		Blackboard->GetValueAsObject(OwnerKey.SelectedKeyName));
	if (!IsValid(EnemyCharacter))
	{
		USK_LOG_ERROR("Enemy character is invalid");
		return EBTNodeResult::Failed;
	}

	const AActor* TargetActor = dynamic_cast<AActor*>(Blackboard->GetValueAsObject(TargetActorKey.SelectedKeyName));
	if (!IsValid(TargetActor))
	{
		USK_LOG_ERROR("Target actor is invalid");
		return EBTNodeResult::Failed;
	}

	const FVector TargetLocation = TargetActor->GetActorLocation();
	Blackboard->SetValueAsVector(TargetLocationKey.SelectedKeyName, TargetLocation);

	const bool TargetReached =
		FMath::IsNearlyEqual(EnemyCharacter->GetActorLocation().X, TargetLocation.X, EnemyCharacter->AcceptanceRadius) &&
		FMath::IsNearlyEqual(EnemyCharacter->GetActorLocation().Y, TargetLocation.Y, EnemyCharacter->AcceptanceRadius);
	Blackboard->SetValueAsBool(TargetReachedKey.SelectedKeyName, TargetReached);
	return EBTNodeResult::Succeeded;
}
