// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USKBTTaskNode.h"
#include "BTTask_UskUpdateState.generated.h"

/**
 * @brief Behaviour tree task node used to update the state of the AI
 */
UCLASS(Category = "Ultimate Starter Kit", meta = (DisplayName = "Update State"))
class UBTTask_UskUpdateState : public UUSKBTTaskNode
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The blackboard key used to store the owner
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector OwnerKey;

	/**
	 * @brief The blackboard key used to store the target actor
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector TargetActorKey;

	/**
	 * @brief The blackboard key used to store the target location
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector TargetLocationKey;

	/**
	 * @brief The blackboard key used to store whether the target has been reached
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector TargetReachedKey;

	/**
	 * @brief Constructor for the task node
	 */
	UBTTask_UskUpdateState();

protected:
	/**
	 * @brief Start executing the task
	 * @param OwnerComp A reference to the behaviour tree executing the task
	 * @param NodeMemory Memory block used to store runtime data
	 * @return The result of the task (Succeeded, Failed or InProgress)
	 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
