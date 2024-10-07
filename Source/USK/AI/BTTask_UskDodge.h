// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USKBTTaskNode.h"
#include "USK/Character/DodgeConfig.h"
#include "BTTask_UskDodge.generated.h"

/**
 * @brief Behaviour tree task node used to make the enemy start dodging
 */
UCLASS(Category = "Ultimate Starter Kit", meta = (DisplayName = "Dodge"))
class USK_API UBTTask_UskDodge : public UUSKBTTaskNode
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The blackboard key used to store the owner
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector OwnerKey;

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
	 * @brief The dodge configurations used by the enemy
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	TMap<FName, FDodgeConfig> DodgeConfig;

	/**
	 * @brief Constructor for the task node
	 */
	UBTTask_UskDodge();

protected:
	/**
	 * @brief Start executing the task
	 * @param OwnerComp A reference to the behaviour tree executing the task
	 * @param NodeMemory Memory block used to store runtime data
	 * @return The result of the task (Succeeded, Failed or InProgress)
	 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
