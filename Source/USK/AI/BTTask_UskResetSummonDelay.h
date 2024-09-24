// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USKBTTaskNode.h"
#include "BTTask_UskResetSummonDelay.generated.h"

/**
 * @brief Behaviour tree task node used to reset the summon delay to 0
 */
UCLASS(Category = "Ultimate Starter Kit", meta = (DisplayName = "Reset Summon Delay"))
class USK_API UBTTask_UskResetSummonDelay : public UUSKBTTaskNode
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The blackboard key used to store the summon delay
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector SummonDelayKey;

	/**
	 * @brief Constructor for the task node
	 */
	UBTTask_UskResetSummonDelay();

protected:
	/**
	 * @brief Start executing the task
	 * @param OwnerComp A reference to the behaviour tree executing the task
	 * @param NodeMemory Memory block used to store runtime data
	 * @return The result of the task (Succeeded, Failed or InProgress)
	 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
