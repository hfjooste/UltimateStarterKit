// Created by Henry Jooste

#include "BTTask_UskFocusTarget.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "USK/Character/USKEnemyCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the task node
 */
UBTTask_UskFocusTarget::UBTTask_UskFocusTarget()
{
	NodeName = "Focus Target";
}

/**
 * @brief Start executing the task
 * @param OwnerComp A reference to the behaviour tree executing the task
 * @param NodeMemory Memory block used to store runtime data
 * @return The result of the task (Succeeded, Failed or InProgress)
 */
EBTNodeResult::Type UBTTask_UskFocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	AActor* TargetActor = dynamic_cast<AActor*>(Blackboard->GetValueAsObject(TargetActorKey.SelectedKeyName));
	if (!IsValid(TargetActor))
	{
		USK_LOG_ERROR("Target actor is invalid");
		return EBTNodeResult::Failed;
	}

	FocusActor(EnemyCharacter, TargetActor);
	return EBTNodeResult::Succeeded;
}
