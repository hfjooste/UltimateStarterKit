// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "USK/Character/EnemyAttackType.h"
#include "USKEnemyAnimationInstance.generated.h"

class AUSKEnemyCharacter;

/**
 * @brief The animation instance for the enemy character
 */
UCLASS()
class USK_API UUSKEnemyAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The animation played when the character is idle
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations")
	UAnimSequence* IdleAnimation;

	/**
	 * @brief The animation played when the character is walking
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations")
	UAnimSequence* WalkAnimation;

	/**
	 * @brief The animation played when the character is running
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations")
	UAnimSequence* RunAnimation;

	/**
	 * @brief The animation played when the character is performing a melee attack
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations")
	UAnimSequence* MeleeAttackAnimation;

	/**
	 * @brief The animation played when the character is performing a ranged attack
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations")
	UAnimSequence* RangedAttackAnimation;

protected:	
	/**
	 * @brief Executed when begin play is called on the owning component
	 */
	virtual void NativeBeginPlay() override;

	/**
	 * @brief Native update override point
	 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
	 */
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	/**
	 * @brief Get the movement speed of the player
	 * @return The movement speed of the player
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	float GetMovementSpeed() const;

	/**
	 * @brief Check if the enemy is performing a melee attack
	 * @return A boolean value indicating if the enemy is performing a melee attack
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	bool IsMeleeAttacking() const;

	/**
	 * @brief Check if the enemy is performing a ranged attack
	 * @return A boolean value indicating if the enemy is performing a ranged attack
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	bool IsRangedAttacking() const;

	/**
	 * @brief Stop attacking the target
	 */
	UFUNCTION(BlueprintCallable, Category = "Animations")
	void StopAttacking() const;

private:
	/**
	 * @brief A reference to the enemy character
	 */
	UPROPERTY()
	AUSKEnemyCharacter* EnemyCharacter;

	/**
	 * @brief The movement speed of the player
	 */
	float MovementSpeed;

	/**
	 * @brief The type of attack the enemy is currently performing
	 */
	EEnemyAttackType CurrentAttackType;
};
