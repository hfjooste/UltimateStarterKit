// Created by Henry Jooste

#pragma once

#include "Animation/AnimInstance.h"
#include "USKCharacter.h"
#include "USK/Weapons/WeaponType.h"
#include "USKCharacterAnimationInstance.generated.h"

/**
 * @brief Base animation instance for USK characters
 */
UCLASS()
class USK_API UUSKCharacterAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	/**
	 * @brief The animation used when the character is in the idle state while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* IdleAnimation;

	/**
	 * @brief The animation used when the character is walking while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* WalkAnimation;

	/**
	 * @brief The animation used when the character is running while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* RunAnimation;

	/**
	 * @brief The animation used when the character is jumping while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* JumpAnimation;

	/**
	 * @brief The animation used when the character is double jumping while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* DoubleJumpAnimation;

	/**
	 * @brief The animation used when the character is falling while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* FallAnimation;

	/**
	 * @brief The animation used when the character is landing while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* LandAnimation;

    /**
     * @brief The animation used when the character is in the idle state with a one handed weapon
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
    UAnimSequence* IdleWeaponOneHandedAnimation;

    /**
     * @brief The animation used when the character is walking with a one handed weapon
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
    UAnimSequence* WalkWeaponOneHandedAnimation;

    /**
     * @brief The animation used when the character is running with a one handed weapon
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
    UAnimSequence* RunWeaponOneHandedAnimation;

    /**
     * @brief The animation used when the character is jumping with a one handed weapon
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
    UAnimSequence* JumpWeaponOneHandedAnimation;

    /**
     * @brief The animation used when the character is double jumping with a one handed weapon
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
    UAnimSequence* DoubleJumpWeaponOneHandedAnimation;

    /**
     * @brief The animation used when the character is falling with a one handed weapon
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
    UAnimSequence* FallWeaponOneHandedAnimation;

	/**
	 * @brief The animation used when the character is landing with a one handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
	UAnimSequence* LandOneHandedAnimation;

	/**
	 * @brief The animation used when the character is in the idle state with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* IdleWeaponTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is walking with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* WalkWeaponTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is running with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* RunWeaponTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is jumping with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* JumpWeaponTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is double jumping with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* DoubleJumpWeaponTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is falling with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* FallWeaponTwoHandedAnimation;

    /**
     * @brief The animation used when the character is landing with a two handed weapon
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
    UAnimSequence* LandWeaponTwoHandedAnimation;

	/**
	 * @brief The movement speed fo the character
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character")
	float MovementSpeed;

	/**
	 * @brief Is the character currently in the air?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character")
	bool IsInAir;

	/**
	 * @brief Is the character double jumping?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character")
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

	/**
	 * @brief Get the idle animation based on the current armed state
	 * @return The idle animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetIdleAnimation() const;

	/**
	 * @brief Get the walk animation based on the current armed state
	 * @return The walk animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetWalkAnimation() const;

	/**
	 * @brief Get the run animation based on the current armed state
	 * @return The run animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetRunAnimation() const;

	/**
	 * @brief Get the jump animation based on the current armed state
	 * @return The jump animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetJumpAnimation() const;

	/**
	 * @brief Get the double jump animation based on the current armed state
	 * @return The double jump animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetDoubleJumpAnimation() const;

	/**
	 * @brief Get the fall animation based on the current armed state
	 * @return The fall animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetFallAnimation() const;

	/**
	 * @brief Get the land animation based on the current armed state
	 * @return The land animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetLandAnimation() const;

private:
	/**
	 * @brief A reference to the character using this animation instance
	 */
	UPROPERTY()
	AUSKCharacter* Character;

	/**
	 * @brief Get an animation based on the current armed state
	 * @param UnarmedAnimation The unarmed animation
	 * @param WeaponOneHandedAnimation The one handed weapon animation
	 * @param WeaponTwoHandedAnimation The two handed weapon animation
	 * @return The animation to play
	 */
	UAnimSequence* GetAnimation(UAnimSequence* UnarmedAnimation, UAnimSequence* WeaponOneHandedAnimation,
		UAnimSequence* WeaponTwoHandedAnimation) const;
};
