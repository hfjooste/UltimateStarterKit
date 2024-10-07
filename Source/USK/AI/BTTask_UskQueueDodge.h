// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USKBTTaskNode.h"
#include "BTTask_UskQueueDodge.generated.h"

/**
 * @brief Behaviour tree task node used to queue a dodge
 */
UCLASS(Category = "Ultimate Starter Kit", meta = (DisplayName = "Queue Dodge"))
class USK_API UBTTask_UskQueueDodge : public UUSKBTTaskNode
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The blackboard key used to store the queued dodge state
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector QueuedDodgeKey;

	/**
	 * @brief The blackboard key used to store the queued dodge config name
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector QueuedDodgeConfigNameKey;

	/**
	 * @brief The name of the dodge configurations to queue
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FName DodgeConfigName;

	/**
	 * @brief Constructor for the task node
	 */
	UBTTask_UskQueueDodge();

protected:
	/**
	 * @brief Start executing the task
	 * @param OwnerComp A reference to the behaviour tree executing the task
	 * @param NodeMemory Memory block used to store runtime data
	 * @return The result of the task (Succeeded, Failed or InProgress)
	 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
