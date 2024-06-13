// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USKBTTaskNode.h"
#include "BTTask_UskResetPatrolPointPauseDelay.generated.h"

/**
 * @brief Behaviour tree task node used to reset the patrol point pause delay
 */
UCLASS(Category = "Ultimate Starter Kit", meta = (DisplayName = "Reset Patrol Point Pause Delay"))
class USK_API UBTTask_UskResetPatrolPointPauseDelay : public UUSKBTTaskNode
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The blackboard key used to store the patrol point pause delay
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector PatrolPointPauseDelayKey;

	/**
	 * @brief Constructor for the task node
	 */
	UBTTask_UskResetPatrolPointPauseDelay();

protected:
	/**
	 * @brief Start executing the task
	 * @param OwnerComp A reference to the behaviour tree executing the task
	 * @param NodeMemory Memory block used to store runtime data
	 * @return The result of the task (Succeeded, Failed or InProgress)
	 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
