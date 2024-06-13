// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USKBTTaskNode.h"
#include "BTTask_UskFocusTarget.generated.h"

/**
 * @brief Behaviour tree task node used to make the enemy character focus the target actor
 */
UCLASS(Category = "Ultimate Starter Kit", meta = (DisplayName = "Focus Target"))
class USK_API UBTTask_UskFocusTarget : public UUSKBTTaskNode
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
	 * @brief Constructor for the task node
	 */
	UBTTask_UskFocusTarget();

protected:
	/**
	 * @brief Start executing the task
	 * @param OwnerComp A reference to the behaviour tree executing the task
	 * @param NodeMemory Memory block used to store runtime data
	 * @return The result of the task (Succeeded, Failed or InProgress)
	 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
