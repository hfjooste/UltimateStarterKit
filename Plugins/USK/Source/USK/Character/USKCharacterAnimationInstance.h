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
	 * @brief The name of the bone used to blend the character's animations
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Blending")
	FName BlendBoneName;

	/**
	 * @brief Whether to blend bone rotations in mesh space or in local space
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Blending")
	bool bMeshSpaceRotationBlend;

	/**
	 * @brief Whether to blend bone scales in mesh space or in local space
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Blending")
	bool bMeshSpaceScaleBlend;

	/**
	 * @brief Should we incorporate the per-bone blend weight of the root bone when lending root motion?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Blending")
	bool bBlendRootMotionBasedOnRootBone = true;

	/**
	 * @brief Should directional movement animations be used?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Blending")
	bool bEnableDirectionalMovementAnimations;
		
	/**
	 * @brief The base animation used when the character is in the idle state
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base")
	UAnimSequence* IdleBaseAnimation;
	
    /**
     * @brief The base animation used when the character is walking
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
    	meta=(EditCondition = "!bEnableDirectionalMovementAnimations", EditConditionHides))
    UAnimSequence* WalkBaseAnimation;

	/**
	 * @brief The base animation used when the character is walking forward
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* WalkForwardBaseAnimation;

	/**
	 * @brief The base animation used when the character is walking backwards
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* WalkBackwardsBaseAnimation;

	/**
	 * @brief The base animation used when the character is walking left
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* WalkLeftBaseAnimation;

	/**
	 * @brief The base animation used when the character is walking right
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* WalkRightBaseAnimation;

	/**
	 * @brief The base animation used when the character is running
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "!bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* RunBaseAnimation;
	
	/**
	 * @brief The base animation used when the character is running forward
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* RunForwardBaseAnimation;

	/**
	 * @brief The base animation used when the character is running backwards
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* RunBackwardsBaseAnimation;

	/**
	 * @brief The base animation used when the character is running left
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* RunLeftBaseAnimation;

	/**
	 * @brief The base animation used when the character is running right
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* RunRightBaseAnimation;

	/**
	 * @brief The base animation used when the character is sprinting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "!bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* SprintBaseAnimation;

	/**
	 * @brief The base animation used when the character is sprinting forward
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* SprintForwardBaseAnimation;

	/**
	 * @brief The base animation used when the character is sprinting backwards
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* SprintBackwardsBaseAnimation;

	/**
	 * @brief The base animation used when the character is sprinting left
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* SprintLeftBaseAnimation;

	/**
	 * @brief The base animation used when the character is sprinting right
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* SprintRightBaseAnimation;

	/**
	 * @brief The base animation used when the character is jumping
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base")
	UAnimSequence* JumpBaseAnimation;

	/**
	 * @brief The base animation used when the character is double jumping
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base")
	UAnimSequence* DoubleJumpBaseAnimation;

	/**
	 * @brief The base animation used when the character is falling
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base")
	UAnimSequence* FallBaseAnimation;

	/**
	 * @brief The base animation used when the character is landing
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base")
	UAnimSequence* LandBaseAnimation;

	/**
	 * @brief The base animation used when the character starts crouching
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base")
	UAnimSequence* CrouchStartBaseAnimation;

	/**
	 * @brief The base animation used when the character stops crouching
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base")
	UAnimSequence* CrouchEndBaseAnimation;

	/**
	 * @brief The base animation used when the character is crouching and idle
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base")
	UAnimSequence* CrouchIdleBaseAnimation;

	/**
	 * @brief The base animation used when the character is crouching and walking
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "!bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* CrouchWalkBaseAnimation;

	/**
	 * @brief The base animation used when the character is crouching and walking forward
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* CrouchWalkForwardBaseAnimation;

	/**
	 * @brief The base animation used when the character is crouching and walking backwards
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* CrouchWalkBackwardsBaseAnimation;

	/**
	 * @brief The base animation used when the character is crouching and walking left
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* CrouchWalkLeftBaseAnimation;

	/**
	 * @brief The base animation used when the character is crouching and walking right
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base",
		meta=(EditCondition = "bEnableDirectionalMovementAnimations", EditConditionHides))
	UAnimSequence* CrouchWalkRightBaseAnimation;

	/**
	 * @brief The base animation used when the character starts proning
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base")
	UAnimSequence* ProneStartBaseAnimation;

	/**
	 * @brief The base animation used when the character stops proning
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base")
	UAnimSequence* ProneEndBaseAnimation;

	/**
	 * @brief The base animation used when the character is proning and idle
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base")
	UAnimSequence* ProneIdleBaseAnimation;

	/**
	 * @brief The base animation used when the character is proning and moving
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base")
	UAnimSequence* ProneMoveBaseAnimation;

	/**
	 * @brief The base animation used when the character is starting to stomp
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base")
	UAnimSequence* StompStartBaseAnimation;

	/**
	 * @brief The base animation used when the character is falling after a stomp
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base")
	UAnimSequence* StompFallBaseAnimation;

	/**
	 * @brief The base animation used when the character is landing after a stomp
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base")
	UAnimSequence* StompLandBaseAnimation;

	/**
	 * @brief The base animation used when the character starts sliding
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base")
	UAnimSequence* SlideStartBaseAnimation;

	/**
	 * @brief The base animation used when the character stops sliding
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base")
	UAnimSequence* SlideEndBaseAnimation;

	/**
	 * @brief The base animation used when the character is sliding
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Base")
	UAnimSequence* SlideLoopBaseAnimation;
	
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
	 * @brief The animation used when the character starts proning while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* ProneStartAnimation;

	/**
	 * @brief The animation used when the character stops proning while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* ProneEndAnimation;

	/**
	 * @brief The animation used when the character is proning and idle while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* ProneIdleAnimation;

	/**
	 * @brief The animation used when the character is proning and moving while unarmed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Unarmed")
	UAnimSequence* ProneMoveAnimation;

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
	 * @brief The animation used when the character starts proning with a one handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
	UAnimSequence* ProneStartWeaponOneHandedAnimation;

	/**
	 * @brief The animation used when the character stops proning with a one handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
	UAnimSequence* ProneEndWeaponOneHandedAnimation;

	/**
	 * @brief The animation used when the character is proning and idle with a one handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
	UAnimSequence* ProneIdleWeaponOneHandedAnimation;

	/**
	 * @brief The animation used when the character is proning and moving with a one handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed")
	UAnimSequence* ProneMoveWeaponOneHandedAnimation;

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
	 * @brief The animation used when the character starts proning with a one handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
	UAnimSequence* ProneStartWeaponAimOneHandedAnimation;

	/**
	 * @brief The animation used when the character stops proning with a one handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
	UAnimSequence* ProneEndWeaponAimOneHandedAnimation;

	/**
	 * @brief The animation used when the character is proning and idle with a one handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
	UAnimSequence* ProneIdleWeaponAimOneHandedAnimation;

	/**
	 * @brief The animation used when the character is proning and moving with a one handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon One Handed|Aim")
	UAnimSequence* ProneMoveWeaponAimOneHandedAnimation;

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
	 * @brief The animation used when the character starts proning with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* ProneStartWeaponTwoHandedAnimation;

	/**
	 * @brief The animation used when the character stops proning with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* ProneEndWeaponTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is proning and idle with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* ProneIdleWeaponTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is proning and moving with a two handed weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed")
	UAnimSequence* ProneMoveWeaponTwoHandedAnimation;

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
	 * @brief The animation used when the character starts proning with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* ProneStartWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character stops proning with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* ProneEndWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is proning and idle with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* ProneIdleWeaponAimTwoHandedAnimation;

	/**
	 * @brief The animation used when the character is proning and moving with a two handed weapon while aiming
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Animations|Weapon Two Handed|Aim")
	UAnimSequence* ProneMoveWeaponAimTwoHandedAnimation;

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
	 * @brief The movement speed of the character
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Movement")
	float MovementSpeed;

	/**
	 * @brief The movement direction of the character multiplied by the movement speed
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Movement")
	FVector2D MovementDirection;

	/**
	 * @brief Is the character currently crouching?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Movement|Crouching")
	bool bIsCrouching;

	/**
	 * @brief Is the character currently proning?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Movement|Proning")
	bool bIsProning;

	/**
	 * @brief Is the character currently stomping?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Movement|Stomping")
	bool bIsStomping;

	/**
	 * @brief The value used to blend stomp animations
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Movement|Stomping")
	float StompBlendValue;

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
	 * @brief Is the character busy ending the prone?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Movement|Proning")
	bool bIsEndingProne;

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
	 * @brief The rotation applied to the character while aiming
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Aiming")
	float AimRotation;

	/**
	 * @brief The rotation applied to the character to look at the center of the screen
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Aiming")
	float LookAtCenterRotation;

	/**
	 * @brief The bone to rotate while the player is aiming up or down using the first person camera perspective
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Aiming")
	FName AimBoneName;

	/**
	 * @brief The bone to rotate to simulate weapon sway
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Weapons")
	FName WeaponSwayBoneName;

	/**
	 * @brief The weapon sway rotation applied to the character
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Weapons")
	FRotator WeaponSway;

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
	 * @brief Get the base idle animation
	 * @return The idle animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetIdleBaseAnimation() const;

	/**
	 * @brief Get the base walk animation
	 * @return The walk animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetWalkBaseAnimation() const;

	/**
	 * @brief Get the base walk forward animation
	 * @return The walk forward animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetWalkForwardBaseAnimation() const;

	/**
	 * @brief Get the base walk backwards animation
	 * @return The walk backwards animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetWalkBackwardsBaseAnimation() const;

	/**
	 * @brief Get the base walk left animation
	 * @return The walk left animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetWalkLeftBaseAnimation() const;

	/**
	 * @brief Get the base walk right animation
	 * @return The walk right animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetWalkRightBaseAnimation() const;

	/**
	 * @brief Get the base run animation
	 * @return The run animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetRunBaseAnimation() const;
	
	/**
	 * @brief Get the base run forward animation
	 * @return The run forward animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetRunForwardBaseAnimation() const;

	/**
	 * @brief Get the base run backwards animation
	 * @return The run backwards animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetRunBackwardsBaseAnimation() const;

	/**
	 * @brief Get the base run left animation
	 * @return The run left animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetRunLeftBaseAnimation() const;

	/**
	 * @brief Get the base run right animation
	 * @return The run right animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetRunRightBaseAnimation() const;

	/**
	 * @brief Get the base sprint animation
	 * @return The sprint animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetSprintBaseAnimation() const;
	
	/**
	 * @brief Get the base sprint forward animation
	 * @return The sprint forward animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetSprintForwardBaseAnimation() const;

	/**
	 * @brief Get the base sprint backwards animation
	 * @return The sprint backwards animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetSprintBackwardsBaseAnimation() const;

	/**
	 * @brief Get the base sprint left animation
	 * @return The sprint left animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetSprintLeftBaseAnimation() const;

	/**
	 * @brief Get the base sprint right animation
	 * @return The sprint right animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetSprintRightBaseAnimation() const;

	/**
	 * @brief Get the base jump animation
	 * @return The jump animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetJumpBaseAnimation() const;

	/**
	 * @brief Get the base double jump animation
	 * @return The double jump animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetDoubleJumpBaseAnimation() const;

	/**
	 * @brief Get the base fall animation
	 * @return The fall animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetFallBaseAnimation() const;

	/**
	 * @brief Get the base land animation
	 * @return The land animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetLandBaseAnimation() const;

	/**
	 * @brief Get the base crouch start animation
	 * @return The crouch start animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetCrouchStartBaseAnimation() const;

	/**
	 * @brief Get the base crouch end animation
	 * @return The crouch end animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetCrouchEndBaseAnimation() const;

	/**
	 * @brief Get the base crouch idle animation
	 * @return The crouch idle animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetCrouchIdleBaseAnimation() const;

	/**
	 * @brief Get the base crouch walk animation
	 * @return The crouch walk animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetCrouchWalkBaseAnimation() const;
	
	/**
	 * @brief Get the base crouch walk forward animation
	 * @return The crouch walk forward animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetCrouchWalkForwardBaseAnimation() const;

	/**
	 * @brief Get the base crouch walk backwards animation
	 * @return The crouch walk backwards animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetCrouchWalkBackwardsBaseAnimation() const;

	/**
	 * @brief Get the base crouch walk left animation
	 * @return The crouch walk left animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetCrouchWalkLeftBaseAnimation() const;

	/**
	 * @brief Get the base crouch walk right animation
	 * @return The crouch walk right animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetCrouchWalkRightBaseAnimation() const;

	/**
	 * @brief Get the base prone start animation
	 * @return The prone start animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetProneStartBaseAnimation() const;

	/**
	 * @brief Get the base prone end animation
	 * @return The prone end animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetProneEndBaseAnimation() const;

	/**
	 * @brief Get the base prone idle animation
	 * @return The prone idle animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetProneIdleBaseAnimation() const;

	/**
	 * @brief Get the base prone walk animation
	 * @return The prone walk animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetProneMoveBaseAnimation() const;

	/**
	 * @brief Get the base stomp start animation
	 * @return The stomp start animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetStompStartBaseAnimation() const;

	/**
	 * @brief Get the base stomp fall animation
	 * @return The stomp fall animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetStompFallBaseAnimation() const;

	/**
	 * @brief Get the base stomp land animation
	 * @return The stomp land animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetStompLandBaseAnimation() const;

	/**
	 * @brief Get the base slide start animation
	 * @return The slide start animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetSlideStartBaseAnimation() const;

	/**
	 * @brief Get the base slide end animation
	 * @return The slide end animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetSlideEndBaseAnimation() const;

	/**
	 * @brief Get the base slide loop animation
	 * @return The slide loop animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetSlideLoopBaseAnimation() const;

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
	 * @brief Get the prone start animation based on the current armed state
	 * @return The prone start animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetProneStartAnimation() const;

	/**
	 * @brief Get the prone end animation based on the current armed state
	 * @return The prone end animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetProneEndAnimation() const;

	/**
	 * @brief Get the prone idle animation based on the current armed state
	 * @return The prone idle animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetProneIdleAnimation() const;

	/**
	 * @brief Get the prone walk animation based on the current armed state
	 * @return The prone walk animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetProneMoveAnimation() const;

	/**
	 * @brief Get the stomp start animation based on the current armed state
	 * @return The stomp start animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetStompStartAnimation() const;

	/**
	 * @brief Get the stomp fall animation based on the current armed state
	 * @return The stomp fall animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetStompFallAnimation() const;

	/**
	 * @brief Get the stomp fall animation based on the current armed state
	 * @return The stomp fall animation to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe), Category = "Animations")
	UAnimSequence* GetStompLandAnimation() const;

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
