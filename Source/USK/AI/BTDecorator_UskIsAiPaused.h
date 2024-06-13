// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_UskIsAiPaused.generated.h"

/**
 * @brief Decorator used to check if the AI is paused
 */
 UCLASS(Category = "Ultimate Starter Kit", meta = (DisplayName = "Is AI Paused"))
class USK_API UBTDecorator_UskIsAiPaused : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The blackboard key used to store the pause delay
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector PauseDelayKey;

	/**
	 * @brief Constructor for the decorator
	 */
	UBTDecorator_UskIsAiPaused();

protected:
	/**
	 * @brief Calculate the raw condition value
	 * @param OwnerComp The owner behavior tree component
	 * @param NodeMemory Memory block used to store runtime data
	 * @return A boolean value indicating if the condition is met
	 */
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
