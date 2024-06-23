// Created by Henry Jooste

#include "BTDecorator_UskIsTargetDead.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "USK/Character/USKCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the decorator
 */
UBTDecorator_UskIsTargetDead::UBTDecorator_UskIsTargetDead()
{
	NodeName = "Is Target Dead";
	bNotifyTick = false;
}

/**
 * @brief Calculate the raw condition value
 * @param OwnerComp The owner behavior tree component
 * @param NodeMemory Memory block used to store runtime data
 * @return A boolean value indicating if the condition is met
 */
bool UBTDecorator_UskIsTargetDead::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(Blackboard))
	{
		USK_LOG_ERROR("Blackboard is invalid");
		return false;
	}

	const AUSKCharacter* TargetCharacter = dynamic_cast<AUSKCharacter*>(
		Blackboard->GetValueAsObject(TargetActorKey.SelectedKeyName));
	if (!IsValid(TargetCharacter))
	{
		USK_LOG_ERROR("Target character is invalid");
		return false;
	}

	return TargetCharacter->IsDead();
}
