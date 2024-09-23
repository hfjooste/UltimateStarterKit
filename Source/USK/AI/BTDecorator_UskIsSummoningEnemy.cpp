// Created by Henry Jooste

#include "BTDecorator_UskIsSummoningEnemy.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the decorator
 */
UBTDecorator_UskIsSummoningEnemy::UBTDecorator_UskIsSummoningEnemy()
{
	NodeName = "Is Summoning Enemy";
	bNotifyTick = false;
}

/**
 * @brief Calculate the raw condition value
 * @param OwnerComp The owner behavior tree component
 * @param NodeMemory Memory block used to store runtime data
 * @return A boolean value indicating if the condition is met
 */
bool UBTDecorator_UskIsSummoningEnemy::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(Blackboard))
	{
		USK_LOG_ERROR("Blackboard is invalid");
		return false;
	}

	const float Delay = Blackboard->GetValueAsFloat(SummonDelayKey.SelectedKeyName);
	return !FMath::IsNearlyZero(Delay) && Delay > 0.0f;
}
