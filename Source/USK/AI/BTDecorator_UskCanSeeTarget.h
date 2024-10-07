// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_UskCanSeeTarget.generated.h"

/**
 * @brief Decorator used to check if the AI can see the target
 */
 UCLASS(Category = "Ultimate Starter Kit", meta = (DisplayName = "Can See Target"))
class USK_API UBTDecorator_UskCanSeeTarget : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The blackboard key used to store the owner
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector OwnerKey;

	/**
	 * @brief The blackboard key used to store the target location
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	FBlackboardKeySelector TargetLocationKey;

	/**
	 * @brief The classes to ignore when checking if the enemy can see the target
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
 	TArray<TSubclassOf<AActor>> IgnoredClasses;

	/**
	 * @brief Constructor for the decorator
	 */
	UBTDecorator_UskCanSeeTarget();

protected:
	/**
	 * @brief Calculate the raw condition value
	 * @param OwnerComp The owner behavior tree component
	 * @param NodeMemory Memory block used to store runtime data
	 * @return A boolean value indicating if the condition is met
	 */
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
