// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USKBTTaskNode.h"
#include "BTTask_UskPauseAi.generated.h"

/**
 * @brief Behaviour tree task node used to pause the AI
 */
UCLASS(Category = "Ultimate Starter Kit", meta = (DisplayName = "Pause AI"))
class USK_API UBTTask_UskPauseAi : public UUSKBTTaskNode
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The blackboard key used to store the pause delay
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector PauseDelayKey;

	/**
	 * @brief The new pause delay
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	float Delay = 3.0f;

	/**
	 * @brief Constructor for the task node
	 */
	UBTTask_UskPauseAi();

protected:
	/**
	 * @brief Start executing the task
	 * @param OwnerComp A reference to the behaviour tree executing the task
	 * @param NodeMemory Memory block used to store runtime data
	 * @return The result of the task (Succeeded, Failed or InProgress)
	 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
