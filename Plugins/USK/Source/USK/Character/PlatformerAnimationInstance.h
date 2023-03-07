// Created by Henry Jooste

#pragma once

#include "Animation/AnimInstance.h"
#include "PlatformerCharacter.h"
#include "PlatformerAnimationInstance.generated.h"

/**
 * @brief Base animation instance for a 3D platformer character
 */
UCLASS()
class USK_API UPlatformerAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	/**
	 * @brief The animation used when the character is in the idle state
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ultimate Starter Kit|Platformer Character|Animations")
	UAnimSequence* IdleAnimation;

	/**
	 * @brief The animation used when the character is walking
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ultimate Starter Kit|Platformer Character|Animations")
	UAnimSequence* WalkAnimation;

	/**
	 * @brief The animation used when the character is running
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ultimate Starter Kit|Platformer Character|Animations")
	UAnimSequence* RunAnimation;

	/**
	 * @brief The animation used when the character is jumping
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ultimate Starter Kit|Platformer Character|Animations")
	UAnimSequence* JumpAnimation;

	/**
	 * @brief The animation used when the character is double jumping
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ultimate Starter Kit|Platformer Character|Animations")
	UAnimSequence* DoubleJumpAnimation;

	/**
	 * @brief The animation used when the character is falling
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ultimate Starter Kit|Platformer Character|Animations")
	UAnimSequence* FallAnimation;

	/**
	 * @brief The animation used when the character is landing
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ultimate Starter Kit|Platformer Character|Animations")
	UAnimSequence* LandAnimation;

	/**
	 * @brief The movement speed fo the character
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ultimate Starter Kit|Platformer Character")
	float MovementSpeed;

	/**
	 * @brief Is the character currently in the air?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ultimate Starter Kit|Platformer Character")
	bool IsInAir;

	/**
	 * @brief Is the character double jumping?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ultimate Starter Kit|Platformer Character")
	bool IsDoubleJumping;

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

private:
	/**
	 * @brief A reference to the character using this animation instance
	 */
	UPROPERTY()
	APlatformerCharacter* Character;
};
