// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USKBTTaskNode.h"
#include "BTTask_UskPatrol.generated.h"

/**
 * @brief Behaviour tree task node used to make the enemy character patrol
 */
UCLASS(Category = "Ultimate Starter Kit", meta = (DisplayName = "Patrol"))
class USK_API UBTTask_UskPatrol : public UUSKBTTaskNode
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The blackboard key used to store the owner
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector OwnerKey;

	/**
	 * @brief The blackboard key used to store the patrol point index
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector PatrolPointIndexKey;

	/**
	 * @brief The blackboard key used to store the patrol point pause delay
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector PatrolPointPauseDelayKey;

	/**
	 * @brief Constructor for the task node
	 */
	UBTTask_UskPatrol();

protected:
	/**
	 * @brief Start executing the task
	 * @param OwnerComp A reference to the behaviour tree executing the task
	 * @param NodeMemory Memory block used to store runtime data
	 * @return The result of the task (Succeeded, Failed or InProgress)
	 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	/**
	 * @brief Called after the target location is reached
	 * @param Blackboard The blackboard component
	 * @param EnemyCharacter The enemy character
	 * @param PatrolPointIndex The current patrol point index
	 */
	void OnTargetReached(UBlackboardComponent* Blackboard, AUSKEnemyCharacter* EnemyCharacter,
		int PatrolPointIndex) const;
};
