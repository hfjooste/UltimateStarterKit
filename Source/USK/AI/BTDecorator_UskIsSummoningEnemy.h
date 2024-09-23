// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_UskIsSummoningEnemy.generated.h"

/**
 * @brief Decorator used to check if the enemy is summoning other enemies
 */
UCLASS(Category = "Ultimate Starter Kit", meta = (DisplayName = "Is Summoning Enemy"))
class USK_API UBTDecorator_UskIsSummoningEnemy : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The blackboard key used to store the summon delay
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector SummonDelayKey;

	/**
	 * @brief Constructor for the decorator
	 */
	UBTDecorator_UskIsSummoningEnemy();

protected:
	/**
	 * @brief Calculate the raw condition value
	 * @param OwnerComp The owner behavior tree component
	 * @param NodeMemory Memory block used to store runtime data
	 * @return A boolean value indicating if the condition is met
	 */
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
