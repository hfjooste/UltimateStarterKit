// Created by Henry Jooste

#include "BTDecorator_UskWasInitialized.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the decorator
 */
UBTDecorator_UskWasInitialized::UBTDecorator_UskWasInitialized()
{
	NodeName = "Was Initialized";
	bNotifyTick = false;
}

/**
 * @brief Calculate the raw condition value
 * @param OwnerComp The owner behavior tree component
 * @param NodeMemory Memory block used to store runtime data
 * @return A boolean value indicating if the condition is met
 */
bool UBTDecorator_UskWasInitialized::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(Blackboard))
	{
		USK_LOG_ERROR("Blackboard is invalid");
		return false;
	}

	return Blackboard->GetValueAsBool(InitializedKey.SelectedKeyName);
}
