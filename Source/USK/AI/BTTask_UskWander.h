// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USKBTTaskNode.h"
#include "BTTask_UskWander.generated.h"

/**
 * @brief Behaviour tree task node used to make the enemy character wander
 */
UCLASS(Category = "Ultimate Starter Kit", meta = (DisplayName = "Wander"))
class USK_API UBTTask_UskWander : public UUSKBTTaskNode
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The blackboard key used to store the owner
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector OwnerKey;

	/**
	 * @brief The blackboard key used to store the wander initialized value
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector WanderInitializedKey;

	/**
	 * @brief The blackboard key used to store the wander location
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector WanderLocationKey;

	/**
	 * @brief The blackboard key used to store the wander pause delay
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector WanderPauseDelayKey;

	/**
	 * @brief The blackboard key used to store the start location
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector StartLocationKey;

	/**
	 * @brief Constructor for the task node
	 */
	UBTTask_UskWander();

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
	 * @brief Update the wander location
	 * @param Blackboard The blackboard component
	 * @param EnemyCharacter The enemy character
	 */
	void UpdateLocation(UBlackboardComponent* Blackboard, AUSKEnemyCharacter* EnemyCharacter) const;

	/**
	 * @brief Called after the target location is reached
	 * @param Blackboard The blackboard component
	 * @param EnemyCharacter The enemy character
	 */
	void OnTargetReached(UBlackboardComponent* Blackboard, const AUSKEnemyCharacter* EnemyCharacter) const;
};
