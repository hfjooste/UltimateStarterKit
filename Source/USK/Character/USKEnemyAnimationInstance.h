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
	 * @brief The animation played when the character is spawning
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations")
	UAnimSequence* SpawnAnimation;
	
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
	 * @brief The animation played when the character is waiting to be executed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations")
	UAnimSequence* WaitingForExecutionAnimation;

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
	 * @brief Start the spawning animation
	 */
	UFUNCTION(BlueprintCallable, Category = "Animations")
	void SpawningStarted() const;

	/**
	 * @brief End the spawning animation
	 */
	UFUNCTION(BlueprintCallable, Category = "Animations")
	void SpawningCompleted() const;

	/**
	 * @brief Check if the character is busy spawning
	 * @return A boolean value indicating if the character is busy spawning
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	bool IsSpawning() const;

	/**
	 * @brief Check if the character is waiting to be executed
	 * @return A boolean value indicating if the character is waiting to be executed
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	bool IsWaitingForExecution() const;

	/**
	 * @brief Get the movement speed of the character
	 * @return The movement speed of the character
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	float GetMovementSpeed() const;

private:
	/**
	 * @brief A reference to the enemy character
	 */
	UPROPERTY()
	AUSKEnemyCharacter* EnemyCharacter;

	/**
	 * @brief Is the character busy spawning?
	 */
	bool bIsSpawning;

	/**
	 * @brief Is the character waiting to be executed?
	 */
	bool bIsWaitingForExecution;

	/**
	 * @brief The movement speed of the character
	 */
	float MovementSpeed;
};
