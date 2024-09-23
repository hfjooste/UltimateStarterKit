// Created by Henry Jooste

#include "BTTask_UskSummonEnemy.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "USK/Character/USKEnemyCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the task node
 */
UBTTask_UskSummonEnemy::UBTTask_UskSummonEnemy()
{
	NodeName = "Summon Enemy";
}

/**
 * @brief Start executing the task
 * @param OwnerComp A reference to the behaviour tree executing the task
 * @param NodeMemory Memory block used to store runtime data
 * @return The result of the task (Succeeded, Failed or InProgress)
 */
EBTNodeResult::Type UBTTask_UskSummonEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	Blackboard->SetValueAsFloat(SummonDelayKey.SelectedKeyName, EnemyCharacter->SummonEnemy());
	Blackboard->SetValueAsVector(SummonLocationKey.SelectedKeyName,
		GetLastReachableLocation(EnemyCharacter, EnemyCharacter->GetSummonLocation()));
	return EBTNodeResult::Succeeded;
}
