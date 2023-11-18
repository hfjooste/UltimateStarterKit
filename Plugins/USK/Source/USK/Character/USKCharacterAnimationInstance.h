// Created by Henry Jooste

#pragma once

#include "Animation/AnimInstance.h"
#include "USKCharacter.h"
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
	 * @brief The animation used when the character is sprinting while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* SprintAnimation;

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
	 * @brief The animation used when the character starts crouching while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* CrouchStartAnimation;

	/**
	 * @brief The animation used when the character stops crouching while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* CrouchEndAnimation;

	/**
	 * @brief The animation used when the character is crouching and idle while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* CrouchIdleAnimation;

	/**
	 * @brief The animation used when the character is crouching and walking while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* CrouchWalkAnimation;

	/**
	 * @brief The animation used when the character is starting to stomp while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* StompStartAnimation;

	/**
	 * @brief The animation used when the character is falling after a stomp while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* StompFallAnimation;

	/**
	 * @brief The animation used when the character is landing after a stomp while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* StompLandAnimation;

	/**
	 * @brief The animation used when the character starts sliding while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* SlideStartAnimation;

	/**
	 * @brief The animation used when the character stops sliding while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* SlideEndAnimation;

	/**
	 * @brief The animation used when the character is sliding while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* SlideLoopAnimation;

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
	 * @brief The animation used when the character is sprinting with a one handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
	UAnimSequence* SprintWeaponOneHandedAnimation;

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
	UAnimSequence* LandWeaponOneHandedAnimation;

	/**
	 * @brief The animation used when the character starts crouching with a one handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
	UAnimSequence* CrouchStartWeaponOneHandedAnimation;

	/**
	 * @brief The animation used when the character stops crouching with a one handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
	UAnimSequence* CrouchEndWeaponOneHandedAnimation;

	/**
	 * @brief The animation used when the character is crouching and idle with a one handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
	UAnimSequence* CrouchIdleWeaponOneHandedAnimation;

	/**
	 * @brief The animation used when the character is crouching and walking with a one handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
	UAnimSequence* CrouchWalkWeaponOneHandedAnimation;

	/**
	 * @brief The animation used when the character is starting to stomp with a one handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
	UAnimSequence* StompStartWeaponOneHandedAnimation;

	/**
	 * @brief The animation used when the character is falling after a stomp with a one handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
	UAnimSequence* StompFallWeaponOneHandedAnimation;

	/**
	 * @brief The animation used when the character is landing after a stomp with a one handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
	UAnimSequence* StompLandWeaponOneHandedAnimation;

	/**
	 * @brief The animation used when the character starts sliding with a one handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
	UAnimSequence* SlideStartWeaponOneHandedAnimation;

	/**
	 * @brief The animation used when the character stops sliding with a one handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
	UAnimSequence* SlideEndWeaponOneHandedAnimation;

	/**
	 * @brief The animation used when the character is sliding with a one handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
	UAnimSequence* SlideLoopWeaponOneHandedAnimation;

	    /**
     * @brief The animation used when the character is in the idle state with a one handed weapon while aiming
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
    UAnimSequence* IdleWeaponAimOneHandedAnimation;

    /**
     * @brief The animation used when the character is walking with a one handed weapon while aiming
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
    UAnimSequence* WalkWeaponAimOneHandedAnimation;

    /**
     * @brief The animation used when the character is running with a one handed weapon while aiming
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
    UAnimSequence* RunWeaponAimOneHandedAnimation;

	/**
	 * @brief The animation used when the character is sprinting with a one handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
	UAnimSequence* SprintWeaponAimOneHandedAnimation;

    /**
     * @brief The animation used when the character is jumping with a one handed weapon while aiming
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
    UAnimSequence* JumpWeaponAimOneHandedAnimation;

    /**
     * @brief The animation used when the character is double jumping with a one handed weapon while aiming
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
    UAnimSequence* DoubleJumpWeaponAimOneHandedAnimation;

    /**
     * @brief The animation used when the character is falling with a one handed weapon while aiming
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
    UAnimSequence* FallWeaponAimOneHandedAnimation;

	/**
	 * @brief The animation used when the character is landing with a one handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
	UAnimSequence* LandWeaponAimOneHandedAnimation;

	/**
	 * @brief The animation used when the character starts crouching with a one handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
	UAnimSequence* CrouchStartWeaponAimOneHandedAnimation;

	/**
	 * @brief The animation used when the character stops crouching with a one handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
	UAnimSequence* CrouchEndWeaponAimOneHandedAnimation;

	/**
	 * @brief The animation used when the character is crouching and idle with a one handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
	UAnimSequence* CrouchIdleWeaponAimOneHandedAnimation;

	/**
	 * @brief The animation used when the character is crouching and walking with a one handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
	UAnimSequence* CrouchWalkWeaponAimOneHandedAnimation;

	/**
	 * @brief The animation used when the character is starting to stomp with a one handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
	UAnimSequence* StompStartWeaponAimOneHandedAnimation;

	/**
	 * @brief The animation used when the character is falling after a stomp with a one handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
	UAnimSequence* StompFallWeaponAimOneHandedAnimation;

	/**
	 * @brief The animation used when the character is landing after a stomp with a one handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
	UAnimSequence* StompLandWeaponAimOneHandedAnimation;

	/**
	 * @brief The animation used when the character starts sliding with a one handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
	UAnimSequence* SlideStartWeaponAimOneHandedAnimation;

	/**
	 * @brief The animation used when the character stops sliding with a one handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
	UAnimSequence* SlideEndWeaponAimOneHandedAnimation;

	/**
	 * @brief The animation used when the character is sliding with a one handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
	UAnimSequence* SlideLoopWeaponAimOneHandedAnimation;

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
	 * @brief The animation used when the character is sprinting with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* SprintWeaponTwoHandedAnimation;

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
	 * @brief The animation used when the character starts crouching with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* CrouchStartWeaponTwoHandedAnimation;

	/**
	 * @brief The animation used when the character stops crouching with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* CrouchEndWeaponTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is crouching and idle with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* CrouchIdleWeaponTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is crouching and walking with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* CrouchWalkWeaponTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is starting to stomp with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* StompStartWeaponTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is falling after a stomp with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* StompFallWeaponTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is landing after a stomp with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* StompLandWeaponTwoHandedAnimation;

	/**
	 * @brief The animation used when the character starts sliding with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* SlideStartWeaponTwoHandedAnimation;

	/**
	 * @brief The animation used when the character stops sliding with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* SlideEndWeaponTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is sliding with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* SlideLoopWeaponTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is in the idle state with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* IdleWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is walking with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* WalkWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is running with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* RunWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is sprinting with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* SprintWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is jumping with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* JumpWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is double jumping with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* DoubleJumpWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is falling with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* FallWeaponAimTwoHandedAnimation;

    /**
     * @brief The animation used when the character is landing with a two handed weapon while aiming
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
    UAnimSequence* LandWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character starts crouching with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* CrouchStartWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character stops crouching with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* CrouchEndWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is crouching and idle with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* CrouchIdleWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is crouching and walking with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* CrouchWalkWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is starting to stomp with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* StompStartWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is falling after a stomp with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* StompFallWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is landing after a stomp with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* StompLandWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character starts sliding with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* SlideStartWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character stops sliding with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* SlideEndWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is sliding with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* SlideLoopWeaponAimTwoHandedAnimation;

	/**
	 * @brief The blend speed used when updating the movement speed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement")
	float MovementBlendSpeed = 10.0f;
	
	/**
	 * @brief The movement speed fo the character
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Movement")
	float MovementSpeed;

	/**
	 * @brief Is the character currently crouching?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Movement|Crouching")
	bool bIsCrouching;

	/**
	 * @brief Is the character currently stomping?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Movement|Stomping")
	bool bIsStomping;

	/**
	 * @brief Is the character starting the stomp?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Movement|Stomping")
	bool bIsStompStarting;

	/**
	 * @brief Is the character busy ending the crouch?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Movement|Crouching")
	bool bIsEndingCrouch;

	/**
	 * @brief Is the character currently in the air?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Jump")
	bool IsInAir;

	/**
	 * @brief Is the character double jumping?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Jump")
	bool IsDoubleJumping;

	/**
	 * @brief The modifier applied to the lean camera rotation
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Leaning")
	float LeanCameraRotationModifier = 1.0f;

	/**
	 * @brief The lean camera roll
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Leaning")
	float LeanCameraRoll;

	/**
	 * @brief The bone to rotate while the character is leaning
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Leaning")
	FName LeanBoneName;

	/**
	 * @brief Is the character currently sliding?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Sliding")
	bool bIsSliding;

	/**
	 * @brief Is the character busy ending the slide?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Sliding")
	bool bIsEndingSlide;

	/**
	 * @brief Is the character aiming?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Aiming")
	bool bIsAiming;

	/**
	 * @brief Is the character aiming?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Aiming")
	float AimRotation;

	/**
	 * @brief The bone to rotate while the player is aiming up or down using the first person camera perspective
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Aiming")
	FName AimBoneName;

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
	 * @brief Get the sprint animation based on the current armed state
	 * @return The sprint animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetSprintAnimation() const;

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

	/**
	 * @brief Get the crouch start animation based on the current armed state
	 * @return The crouch start animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetCrouchStartAnimation() const;

	/**
	 * @brief Get the crouch end animation based on the current armed state
	 * @return The crouch end animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetCrouchEndAnimation() const;

	/**
	 * @brief Get the crouch idle animation based on the current armed state
	 * @return The crouch idle animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetCrouchIdleAnimation() const;

	/**
	 * @brief Get the crouch walk animation based on the current armed state
	 * @return The crouch walk animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetCrouchWalkAnimation() const;

	/**
	 * @brief Get the stomp start animation based on the current armed state
	 * @return The stomp start animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetStompStartAnimation() const;

	/**
	 * @brief Get the slide start animation based on the current armed state
	 * @return The slide start animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetSlideStartAnimation() const;

	/**
	 * @brief Get the slide end animation based on the current armed state
	 * @return The slide end animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetSlideEndAnimation() const;

	/**
	 * @brief Get the slide loop animation based on the current armed state
	 * @return The slide loop animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetSlideLoopAnimation() const;

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
