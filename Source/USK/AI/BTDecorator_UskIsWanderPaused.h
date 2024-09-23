// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_UskIsWanderPaused.generated.h"

/**
 * @brief Decorator used to check if the AI wander is paused
 */
UCLASS(Category = "Ultimate Starter Kit", meta = (DisplayName = "Is Wander Paused"))
class USK_API UBTDecorator_UskIsWanderPaused : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The blackboard key used to store the wander pause delay
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector WanderPauseDelayKey;

	/**
	 * @brief Constructor for the decorator
	 */
	UBTDecorator_UskIsWanderPaused();

protected:
	/**
	 * @brief Calculate the raw condition value
	 * @param OwnerComp The owner behavior tree component
	 * @param NodeMemory Memory block used to store runtime data
	 * @return A boolean value indicating if the condition is met
	 */
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
