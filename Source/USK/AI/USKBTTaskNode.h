// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "USKBTTaskNode.generated.h"

class AUSKEnemyCharacter;

/**
 * @brief The base behavior tree task node
 */
UCLASS(Abstract)
class USK_API UUSKBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	/**
     * @brief Constructor for the task node
     */
	UUSKBTTaskNode();
	
protected:
	/**
	 * @brief Move the character to a specific location
	 * @param EnemyCharacter The character to move
	 * @param TargetLocation The target location of the character
	 * @param AcceptanceRadius The radius around the point that the character must reach to consider the point reached
	 * @param TargetReached A boolean value indicating if the character reached the target location
	 * @return A boolean value indicating if the character was moved
	 */
	bool MoveToLocation(AUSKEnemyCharacter* EnemyCharacter, const FVector& TargetLocation,
		float AcceptanceRadius, bool& TargetReached) const;

	/**
	 * @brief Stop all movement of the character
	 * @param EnemyCharacter A reference to the character
	 */
	void StopMovement(AUSKEnemyCharacter* EnemyCharacter) const;

	/**
	 * @brief Focus a specific actor
	 * @param EnemyCharacter The character that should focus the actor
	 * @param Target The actor to focus
	 */
	void FocusActor(AUSKEnemyCharacter* EnemyCharacter, AActor* Target);

	/**
	 * @brief Stop focusing
	 * @param EnemyCharacter The character that should stop focusing
	 */
	void ClearFocus(AUSKEnemyCharacter* EnemyCharacter);
};
