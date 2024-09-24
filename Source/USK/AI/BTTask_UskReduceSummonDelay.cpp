// Created by Henry Jooste

#include "BTTask_UskReduceSummonDelay.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "USK/Character/USKEnemyCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the task node
 */
UBTTask_UskReduceSummonDelay::UBTTask_UskReduceSummonDelay()
{
	bNotifyTick = true;
	NodeName = "Reduce Summon Delay";
}

/**
 * @brief Update the task
 * @param OwnerComp A reference to the behaviour tree executing the task
 * @param NodeMemory Memory block used to store runtime data
 * @param DeltaSeconds The time since the last update
 */
void UBTTask_UskReduceSummonDelay::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(Blackboard))
	{
		USK_LOG_ERROR("Blackboard is invalid");
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (bAbortIfStaggered)
	{
		const AUSKEnemyCharacter* EnemyCharacter = dynamic_cast<AUSKEnemyCharacter*>(
		Blackboard->GetValueAsObject(OwnerKey.SelectedKeyName));
		if (!IsValid(EnemyCharacter))
		{
			USK_LOG_ERROR("Enemy character is invalid");
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return;
		}

		if (EnemyCharacter->IsStaggered())
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return;
		}
	}

	const float CurrentDelay = Blackboard->GetValueAsFloat(SummonDelayKey.SelectedKeyName);
	const float NewDelay = CurrentDelay - DeltaSeconds;
	Blackboard->SetValueAsFloat(SummonDelayKey.SelectedKeyName, NewDelay);
	if (NewDelay <= 0.0f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

/**
 * @brief Start executing the task
 * @param OwnerComp A reference to the behaviour tree executing the task
 * @param NodeMemory Memory block used to store runtime data
 * @return The result of the task (Succeeded, Failed or InProgress)
 */
EBTNodeResult::Type UBTTask_UskReduceSummonDelay::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}
