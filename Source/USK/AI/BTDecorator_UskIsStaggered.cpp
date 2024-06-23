﻿// Created by Henry Jooste

#include "BTDecorator_UskIsStaggered.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "USK/Character/USKEnemyCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the decorator
 */
UBTDecorator_UskIsStaggered::UBTDecorator_UskIsStaggered()
{
	NodeName = "Is Staggered";
	bNotifyTick = false;
}

/**
 * @brief Calculate the raw condition value
 * @param OwnerComp The owner behavior tree component
 * @param NodeMemory Memory block used to store runtime data
 * @return A boolean value indicating if the condition is met
 */
bool UBTDecorator_UskIsStaggered::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(Blackboard))
	{
		USK_LOG_ERROR("Blackboard is invalid");
		return false;
	}

	const AUSKEnemyCharacter* EnemyCharacter = dynamic_cast<AUSKEnemyCharacter*>(
		Blackboard->GetValueAsObject(OwnerKey.SelectedKeyName));
	if (!IsValid(EnemyCharacter))
	{
		USK_LOG_ERROR("Enemy character is invalid");
		return false;
	}

	return EnemyCharacter->IsStaggered();
}