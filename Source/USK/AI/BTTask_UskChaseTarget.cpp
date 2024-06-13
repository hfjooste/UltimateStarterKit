// Created by Henry Jooste

#include "BTTask_UskChaseTarget.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "USK/Character/USKEnemyCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the task node
 */
UBTTask_UskChaseTarget::UBTTask_UskChaseTarget()
{
	NodeName = "Chase Target";
}

/**
 * @brief Start executing the task
 * @param OwnerComp A reference to the behaviour tree executing the task
 * @param NodeMemory Memory block used to store runtime data
 * @return The result of the task (Succeeded, Failed or InProgress)
 */
EBTNodeResult::Type UBTTask_UskChaseTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
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

	bool TargetReached;
	const FVector TargetLocation = Blackboard->GetValueAsVector(TargetLocationKey.SelectedKeyName);
	if (!MoveToLocation(EnemyCharacter, TargetLocation, 0.01f, TargetReached))
	{
		USK_LOG_ERROR("Failed to move to location");
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Succeeded;
}
