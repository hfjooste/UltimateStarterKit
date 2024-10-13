// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_UskIsWaitingForExecution.generated.h"

/**
 * @brief Decorator used to check if the enemy is waiting to be executed
 */
UCLASS(Category = "Ultimate Starter Kit", meta = (DisplayName = "Is Waiting For Execution"))
class USK_API UBTDecorator_UskIsWaitingForExecution : public UBTDecorator
{
	GENERATED_BODY()
	
public:
 	/**
	  * @brief The blackboard key used to store the owner
	  */
 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
 	FBlackboardKeySelector OwnerKey;

	/**
	 * @brief Constructor for the decorator
	 */
	UBTDecorator_UskIsWaitingForExecution();

protected:
	/**
	 * @brief Calculate the raw condition value
	 * @param OwnerComp The owner behavior tree component
	 * @param NodeMemory Memory block used to store runtime data
	 * @return A boolean value indicating if the condition is met
	 */
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
