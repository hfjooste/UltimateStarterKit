// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USKBTTaskNode.h"
#include "BTTask_UskFlyChaseTarget.generated.h"

/**
 * @brief Behaviour tree task node used to make the enemy character chase the target actor while flying
 */
UCLASS(Category = "Ultimate Starter Kit", meta = (DisplayName = "Fly Chase Target"))
class USK_API UBTTask_UskFlyChaseTarget : public UUSKBTTaskNode
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
	 * @brief The minimum index of the grid used to find possible locations
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	int GridIndexMin = -1;

	/**
	 * @brief The maximum index of the grid used to find possible locations
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	int GridIndexMax = 1;

	/**
	 * @brief The size of each block in the grid used to find possible locations
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	float GridBlockSize = 50.0f;

	/**
	 * @brief The minimum distance from the ground that the enemy character should maintain
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	float MinDistanceFromGround = 500.0f;

	/**
	 * @brief The minimum Z location of the enemy while flying
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	float MinZLocation = -1000000.0f;

	/**
	 * @brief The maximum Z location of the enemy while flying
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	float MaxZLocation = 1000000.0f;

	/**
	 * @brief Should the velocity of the enemy character be reset when the target is lost?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	bool bResetVelocityWhenTargetLost = true;

	/**
	 * @brief The speed at which the velocity of the enemy character should be updated
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	float VelocityUpdateInterpSpeed = 10.0f;

	/**
	 * @brief The object types that are considered obstacles
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|AI")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObstacleObjectTypes;

	/**
	 * @brief Constructor for the task node
	 */
	UBTTask_UskFlyChaseTarget();

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
	 * @brief Get the possible locations that the enemy character can move to
	 * @param EnemyCharacter The enemy character
	 * @return The possible locations
	 */
	TArray<FVector> GetPossibleLocations(AUSKEnemyCharacter* EnemyCharacter) const;

	/**
	 * @brief Get the offset from the ground that the enemy character should maintain
	 * @param EnemyCharacter The enemy character
	 * @return The offset from the ground
	 */
	float GetGroundOffset(AUSKEnemyCharacter* EnemyCharacter) const;

	/**
	 * @brief Find the best location for the enemy character to move to
	 * @param EnemyCharacter The enemy character
	 * @param PossibleLocations The possible locations
	 * @param TargetLocation The target location
	 * @param BestLocation The best location
	 * @return A boolean value indicating if the best location was found
	 */
	bool FindBestLocation(AUSKEnemyCharacter* EnemyCharacter, TArray<FVector> PossibleLocations,
		const FVector& TargetLocation, FVector& BestLocation) const;

	/**
	 * @brief Check if the location is valid
	 * @param EnemyCharacter The enemy character
	 * @param Location The location to check
	 * @return A boolean value indicating if the location is valid
	 */
	bool IsLocationValid(AUSKEnemyCharacter* EnemyCharacter, const FVector& Location) const;

	/**
	 * @brief Check if the enemy can see the target from a specific location
	 * @param EnemyCharacter The enemy character
	 * @param Location The location to check
	 * @param TargetLocation The target location
	 * @return A boolean value indicating if the enemy can see the target
	 */
	bool CanSeeTargetLocation(AUSKEnemyCharacter* EnemyCharacter, const FVector& Location,
		const FVector& TargetLocation) const;
};
