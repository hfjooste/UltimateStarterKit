// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USKBTTaskNode.h"
#include "BTTask_UskReducePauseDelay.generated.h"

/**
 * @brief Behaviour tree task node used to reduce the pause delay
 */
UCLASS(Category = "Ultimate Starter Kit", meta = (DisplayName = "Reduce Pause Delay"))
class USK_API UBTTask_UskReducePauseDelay : public UUSKBTTaskNode
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The blackboard key used to store the pause delay
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector PauseDelayKey;

	/**
	 * @brief Constructor for the task node
	 */
	UBTTask_UskReducePauseDelay();

protected:
	/**
	 * @brief Start executing the task
	 * @param OwnerComp A reference to the behaviour tree executing the task
	 * @param NodeMemory Memory block used to store runtime data
	 * @return The result of the task (Succeeded, Failed or InProgress)
	 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
