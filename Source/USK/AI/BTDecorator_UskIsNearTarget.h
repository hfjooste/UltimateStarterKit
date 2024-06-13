// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_UskIsNearTarget.generated.h"

/**
 * @brief Decorator used to check if the AI is near the target
 */
UCLASS(Category = "Ultimate Starter Kit", meta = (DisplayName = "Is Near Target"))
class USK_API UBTDecorator_UskIsNearTarget : public UBTDecorator
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
	 * @brief A boolean value indicating if the Z difference should be checked
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	bool bCheckZDifference = false;

	/**
	 * @brief The maximum distance the AI can be from the target
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	float MaxDistance = 500.0f;

	/**
	 * @brief Constructor for the decorator
	 */
	UBTDecorator_UskIsNearTarget();

protected:
	/**
	 * @brief Calculate the raw condition value
	 * @param OwnerComp The owner behavior tree component
	 * @param NodeMemory Memory block used to store runtime data
	 * @return A boolean value indicating if the condition is met
	 */
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
