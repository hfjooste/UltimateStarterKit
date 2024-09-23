// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USKBTTaskNode.h"
#include "BTTask_UskMoveToSummonLocation.generated.h"

/**
 * @brief Behaviour tree task node used to make the enemy character move towards the summon location
 */
UCLASS(Category = "Ultimate Starter Kit", meta = (DisplayName = "Move To Summon Location"))
class USK_API UBTTask_UskMoveToSummonLocation : public UUSKBTTaskNode
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The blackboard key used to store the owner
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector OwnerKey;

	/**
	 * @brief The blackboard key used to store the summon location
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector SummonLocationKey;

	/**
	 * @brief The radius around the point that the character must reach to consider the point reached
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	float AcceptanceRadius = 500.0f;

	/**
	 * @brief The radius around the point where the character will start focusing the location
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	float FocusLocationRadius = 700.0f;

	/**
	 * @brief Constructor for the task node
	 */
	UBTTask_UskMoveToSummonLocation();

protected:
	/**
	 * @brief Start executing the task
	 * @param OwnerComp A reference to the behaviour tree executing the task
	 * @param NodeMemory Memory block used to store runtime data
	 * @return The result of the task (Succeeded, Failed or InProgress)
	 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
