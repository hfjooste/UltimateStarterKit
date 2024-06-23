﻿// Created by Henry Jooste

#include "BTTask_UskResetPatrolPointPauseDelay.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "USK/Character/USKEnemyCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the task node
 */
UBTTask_UskResetPatrolPointPauseDelay::UBTTask_UskResetPatrolPointPauseDelay()
{
	NodeName = "Reset Patrol Point Pause Delay";
}

/**
 * @brief Start executing the task
 * @param OwnerComp A reference to the behaviour tree executing the task
 * @param NodeMemory Memory block used to store runtime data
 * @return The result of the task (Succeeded, Failed or InProgress)
 */
EBTNodeResult::Type UBTTask_UskResetPatrolPointPauseDelay::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(Blackboard))
	{
		USK_LOG_ERROR("Blackboard is invalid");
		return EBTNodeResult::Failed;
	}

	Blackboard->SetValueAsFloat(PatrolPointPauseDelayKey.SelectedKeyName, FLT_MIN);
	return EBTNodeResult::Succeeded;
}