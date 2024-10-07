// Created by Henry Jooste

#include "BTTask_UskQueueDodge.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "USK/Character/USKEnemyCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the task node
 */
UBTTask_UskQueueDodge::UBTTask_UskQueueDodge()
{
	NodeName = "Queue Dodge";
}

/**
 * @brief Start executing the task
 * @param OwnerComp A reference to the behaviour tree executing the task
 * @param NodeMemory Memory block used to store runtime data
 * @return The result of the task (Succeeded, Failed or InProgress)
 */
EBTNodeResult::Type UBTTask_UskQueueDodge::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(Blackboard))
	{
		USK_LOG_ERROR("Blackboard is invalid");
		return EBTNodeResult::Failed;
	}

	Blackboard->SetValueAsBool(QueuedDodgeKey.SelectedKeyName, true);
	Blackboard->SetValueAsName(QueuedDodgeConfigNameKey.SelectedKeyName, DodgeConfigName);
	return EBTNodeResult::Succeeded;
}
