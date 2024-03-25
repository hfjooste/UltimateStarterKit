// Created by Henry Jooste

#include "USKCharacterAnimationInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "USK/Logger/Log.h"

/**
 * @brief Executed when begin play is called on the owning component
 */
void UUSKCharacterAnimationInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	USK_LOG_TRACE("Initializing character animation instance");
	Character = dynamic_cast<AUSKCharacter*>(TryGetPawnOwner());
}

/**
 * @brief Native update override point
 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
 */
void UUSKCharacterAnimationInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!IsValid(Character))
	{
		USK_LOG_WARNING("Character is not valid");
		return;
	}

	const FQuat CharacterRotation = Character->GetActorRotation().Quaternion();
	const FVector CharacterVelocity = Character->GetMovementComponent()->Velocity;
	const FVector DirectionVelocity = UKismetMathLibrary::Quat_RotateVector(CharacterRotation, CharacterVelocity);
	const float NewMovementSpeed = UKismetMathLibrary::VSizeXY(CharacterVelocity);
	const FVector2D NewMovementDirection = Character->GetCharacterMovement()->bOrientRotationToMovement
		? FVector2D(0.0f, FMath::Abs(NewMovementSpeed))
		: FVector2D(DirectionVelocity.X, DirectionVelocity.Y);
	MovementSpeed = FMath::FInterpTo(MovementSpeed, NewMovementSpeed,
		DeltaSeconds, MovementBlendSpeed);
	MovementDirection = FMath::Vector2DInterpTo(MovementDirection, NewMovementDirection,
		DeltaSeconds, MovementBlendSpeed);
	IsInAir = Character->GetMovementComponent()->IsFalling();
	bIsCrouching = !IsInAir && Character->IsCrouching();
	bIsEndingCrouch = Character->IsEndingCrouch();
	bIsProning = !IsInAir && Character->IsProning();
	bIsEndingProne = Character->IsEndingProne();
	bIsSliding = !IsInAir && Character->IsSliding();
	bIsEndingSlide = Character->IsEndingSlide();
    bIsStomping = Character->IsStomping();
	StompBlendValue = FMath::Lerp(StompBlendValue, bIsStomping ? 1.0f : 0.0f, DeltaSeconds * MovementBlendSpeed);
    bIsStompStarting = Character->IsStompStarting();
	LeanCameraRoll = Character->GetLeanCameraRoll() * LeanCameraRotationModifier;
	LookAtCenterRotation = Character->GetLookAtCenterRotation();
	bIsAiming = Character->IsAiming();
	AimRotation = Character->HasWeapon() ? Character->GetControlRotation().Pitch * -1.0f : 0.0f;
	WeaponSway = Character->GetWeaponSway();

	if (!Character->IsDoubleJumping)
	{
		IsDoubleJumping = false;
		return;
	}

	if (!IsDoubleJumping)
	{
		IsDoubleJumping = true;
		return;
	}

	USK_LOG_TRACE("Resetting character double jump");
	Character->IsDoubleJumping = false;
}

/**
 * @brief Get the base idle animation
 * @return The idle animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetIdleBaseAnimation() const
{
	return IdleBaseAnimation;
}

/**
 * @brief Get the base walk animation
 * @return The walk animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetWalkBaseAnimation() const
{
	return WalkBaseAnimation;
}

/**
 * @brief Get the base walk forward animation
 * @return The walk forward animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetWalkForwardBaseAnimation() const
{
	return WalkForwardBaseAnimation;
}

/**
 * @brief Get the base walk backwards animation
 * @return The walk backwards animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetWalkBackwardsBaseAnimation() const
{
	return WalkBackwardsBaseAnimation;
}

/**
 * @brief Get the base walk left animation
 * @return The walk left animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetWalkLeftBaseAnimation() const
{
	return WalkLeftBaseAnimation;
}

/**
 * @brief Get the base walk right animation
 * @return The walk right animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetWalkRightBaseAnimation() const
{
	return WalkRightBaseAnimation;
}

/**
 * @brief Get the base run animation
 * @return The run animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetRunBaseAnimation() const
{
	return RunBaseAnimation;
}

/**
 * @brief Get the base run forward animation
 * @return The run forward animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetRunForwardBaseAnimation() const
{
	return RunForwardBaseAnimation;
}

/**
 * @brief Get the base run backwards animation
 * @return The run backwards animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetRunBackwardsBaseAnimation() const
{
	return RunBackwardsBaseAnimation;
}

/**
 * @brief Get the base run left animation
 * @return The run left animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetRunLeftBaseAnimation() const
{
	return RunLeftBaseAnimation;
}

/**
 * @brief Get the base run right animation
 * @return The run right animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetRunRightBaseAnimation() const
{
	return RunRightBaseAnimation;
}

/**
 * @brief Get the base sprint animation
 * @return The sprint animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetSprintBaseAnimation() const
{
	return SprintBaseAnimation;
}

/**
 * @brief Get the base sprint forward animation
 * @return The sprint forward animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetSprintForwardBaseAnimation() const
{
	return SprintForwardBaseAnimation;
}

/**
 * @brief Get the base sprint backwards animation
 * @return The sprint backwards animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetSprintBackwardsBaseAnimation() const
{
	return SprintBackwardsBaseAnimation;
}

/**
 * @brief Get the base sprint left animation
 * @return The sprint left animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetSprintLeftBaseAnimation() const
{
	return SprintLeftBaseAnimation;
}

/**
 * @brief Get the base sprint right animation
 * @return The sprint right animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetSprintRightBaseAnimation() const
{
	return SprintRightBaseAnimation;
}

/**
 * @brief Get the base jump animation
 * @return The jump animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetJumpBaseAnimation() const
{
	return JumpBaseAnimation;
}

/**
 * @brief Get the base double jump animation
 * @return The double jump animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetDoubleJumpBaseAnimation() const
{
	return DoubleJumpBaseAnimation;
}

/**
 * @brief Get the base fall animation
 * @return The fall animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetFallBaseAnimation() const
{
	return FallBaseAnimation;
}

/**
 * @brief Get the base land animation
 * @return The land animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetLandBaseAnimation() const
{
	return LandBaseAnimation;
}

/**
 * @brief Get the base crouch start animation
 * @return The crouch start animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetCrouchStartBaseAnimation() const
{
	return CrouchStartBaseAnimation;
}

/**
 * @brief Get the base crouch end animation
 * @return The crouch end animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetCrouchEndBaseAnimation() const
{
	return CrouchEndBaseAnimation;
}

/**
 * @brief Get the base crouch idle animation
 * @return The crouch idle animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetCrouchIdleBaseAnimation() const
{
	return CrouchIdleBaseAnimation;
}

/**
 * @brief Get the base crouch walk animation
 * @return The crouch walk animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetCrouchWalkBaseAnimation() const
{
	return CrouchWalkBaseAnimation;
}

/**
 * @brief Get the base crouch walk forward animation
 * @return The crouch walk forward animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetCrouchWalkForwardBaseAnimation() const
{
	return CrouchWalkForwardBaseAnimation;
}

/**
 * @brief Get the base crouch walk backwards animation
 * @return The crouch walk backwards animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetCrouchWalkBackwardsBaseAnimation() const
{
	return CrouchWalkBackwardsBaseAnimation;
}

/**
 * @brief Get the base crouch walk left animation
 * @return The crouch walk left animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetCrouchWalkLeftBaseAnimation() const
{
	return CrouchWalkLeftBaseAnimation;
}

/**
 * @brief Get the base crouch walk right animation
 * @return The crouch walk right animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetCrouchWalkRightBaseAnimation() const
{
	return CrouchWalkRightBaseAnimation;
}

/**
 * @brief Get the base prone start animation
 * @return The prone start animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetProneStartBaseAnimation() const
{
	return ProneStartBaseAnimation;
}

/**
 * @brief Get the base prone end animation
 * @return The prone end animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetProneEndBaseAnimation() const
{
	return ProneEndBaseAnimation;
}

/**
 * @brief Get the base prone idle animation
 * @return The prone idle animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetProneIdleBaseAnimation() const
{
	return ProneIdleBaseAnimation;
}

/**
 * @brief Get the base prone walk animation
 * @return The prone walk animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetProneMoveBaseAnimation() const
{
	return ProneMoveBaseAnimation;
}

/**
 * @brief Get the base stomp start animation
 * @return The stomp start animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetStompStartBaseAnimation() const
{
	return StompStartBaseAnimation;
}

/**
 * @brief Get the base stomp fall animation
 * @return The stomp fall animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetStompFallBaseAnimation() const
{
	return StompFallBaseAnimation;
}

/**
 * @brief Get the base stomp land animation
 * @return The stomp land animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetStompLandBaseAnimation() const
{
	return StompLandBaseAnimation;
}

/**
 * @brief Get the base slide start animation
 * @return The slide start animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetSlideStartBaseAnimation() const
{
	return SlideStartBaseAnimation;
}

/**
 * @brief Get the base slide end animation
 * @return The slide end animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetSlideEndBaseAnimation() const
{
	return SlideEndBaseAnimation;
}

/**
 * @brief Get the base slide loop animation
 * @return The slide loop animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetSlideLoopBaseAnimation() const
{
	return SlideLoopBaseAnimation;
}

/**
 * @brief Get the idle animation based on the current armed state
 * @return The idle animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetIdleAnimation() const
{
	return bIsAiming
		? GetAnimation(IdleAnimation, IdleWeaponAimOneHandedAnimation, IdleWeaponAimTwoHandedAnimation)
		: GetAnimation(IdleAnimation, IdleWeaponOneHandedAnimation, IdleWeaponTwoHandedAnimation);
}

/**
 * @brief Get the walk animation based on the current armed state
 * @return The walk animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetWalkAnimation() const
{
	return bIsAiming
		? GetAnimation(WalkAnimation, WalkWeaponAimOneHandedAnimation, WalkWeaponAimTwoHandedAnimation)
		: GetAnimation(WalkAnimation, WalkWeaponOneHandedAnimation, WalkWeaponTwoHandedAnimation);
}

/**
 * @brief Get the run animation based on the current armed state
 * @return The run animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetRunAnimation() const
{
	return bIsAiming
		? GetAnimation(RunAnimation, RunWeaponAimOneHandedAnimation, RunWeaponAimTwoHandedAnimation)
		: GetAnimation(RunAnimation, RunWeaponOneHandedAnimation, RunWeaponTwoHandedAnimation);
}

/**
 * @brief Get the sprint animation based on the current armed state
 * @return The sprint animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetSprintAnimation() const
{
	return bIsAiming
		? GetAnimation(SprintAnimation, SprintWeaponAimOneHandedAnimation, SprintWeaponAimTwoHandedAnimation)
		: GetAnimation(SprintAnimation, SprintWeaponOneHandedAnimation, SprintWeaponTwoHandedAnimation);
}

/**
 * @brief Get the jump animation based on the current armed state
 * @return The jump animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetJumpAnimation() const
{
	return bIsAiming
		? GetAnimation(JumpAnimation, JumpWeaponAimOneHandedAnimation, JumpWeaponAimTwoHandedAnimation)
		: GetAnimation(JumpAnimation, JumpWeaponOneHandedAnimation, JumpWeaponTwoHandedAnimation);
}

/**
 * @brief Get the double jump animation based on the current armed state
 * @return The double jump animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetDoubleJumpAnimation() const
{
	return bIsAiming
		? GetAnimation(DoubleJumpAnimation, DoubleJumpWeaponAimOneHandedAnimation, DoubleJumpWeaponAimTwoHandedAnimation)
		: GetAnimation(DoubleJumpAnimation, DoubleJumpWeaponOneHandedAnimation, DoubleJumpWeaponTwoHandedAnimation);
}

/**
 * @brief Get the fall animation based on the current armed state
 * @return The fall animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetFallAnimation() const
{
	return bIsAiming
		? GetAnimation(FallAnimation, FallWeaponAimOneHandedAnimation, FallWeaponAimTwoHandedAnimation)
		: GetAnimation(FallAnimation, FallWeaponOneHandedAnimation, FallWeaponTwoHandedAnimation);
		
}

/**
 * @brief Get the land animation based on the current armed state
 * @return The land animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetLandAnimation() const
{
	return bIsAiming
		? GetAnimation(LandAnimation, LandWeaponAimOneHandedAnimation, LandWeaponAimTwoHandedAnimation)
		: GetAnimation(LandAnimation, LandWeaponOneHandedAnimation, LandWeaponTwoHandedAnimation);
}

/**
 * @brief Get the crouch start animation based on the current armed state
 * @return The crouch start animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetCrouchStartAnimation() const
{
	return bIsAiming
		? GetAnimation(CrouchStartAnimation, CrouchStartWeaponAimOneHandedAnimation, CrouchStartWeaponAimTwoHandedAnimation)
		: GetAnimation(CrouchStartAnimation, CrouchStartWeaponOneHandedAnimation, CrouchStartWeaponTwoHandedAnimation);
}

/**
 * @brief Get the crouch end animation based on the current armed state
 * @return The crouch end animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetCrouchEndAnimation() const
{
	return bIsAiming
		? GetAnimation(CrouchEndAnimation, CrouchEndWeaponAimOneHandedAnimation, CrouchEndWeaponAimTwoHandedAnimation)
		: GetAnimation(CrouchEndAnimation, CrouchEndWeaponOneHandedAnimation, CrouchEndWeaponTwoHandedAnimation);
}

/**
 * @brief Get the crouch idle animation based on the current armed state
 * @return The crouch idle animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetCrouchIdleAnimation() const
{
	return bIsAiming
		? GetAnimation(CrouchIdleAnimation, CrouchIdleWeaponAimOneHandedAnimation, CrouchIdleWeaponAimTwoHandedAnimation)
		: GetAnimation(CrouchIdleAnimation, CrouchIdleWeaponOneHandedAnimation, CrouchIdleWeaponTwoHandedAnimation);
}

/**
 * @brief Get the crouch walk animation based on the current armed state
 * @return The crouch walk animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetCrouchWalkAnimation() const
{
	return bIsAiming
		? GetAnimation(CrouchWalkAnimation, CrouchWalkWeaponAimOneHandedAnimation, CrouchWalkWeaponAimTwoHandedAnimation)
		: GetAnimation(CrouchWalkAnimation, CrouchWalkWeaponOneHandedAnimation, CrouchWalkWeaponTwoHandedAnimation);
}

/**
 * @brief Get the prone start animation based on the current armed state
 * @return The prone start animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetProneStartAnimation() const
{
	return bIsAiming
		? GetAnimation(ProneStartAnimation, ProneStartWeaponAimOneHandedAnimation, ProneStartWeaponAimTwoHandedAnimation)
		: GetAnimation(ProneStartAnimation, ProneStartWeaponOneHandedAnimation, ProneStartWeaponTwoHandedAnimation);
}

/**
 * @brief Get the prone end animation based on the current armed state
 * @return The prone end animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetProneEndAnimation() const
{
	return bIsAiming
    		? GetAnimation(ProneEndAnimation, ProneEndWeaponAimOneHandedAnimation, ProneEndWeaponAimTwoHandedAnimation)
    		: GetAnimation(ProneEndAnimation, ProneEndWeaponOneHandedAnimation, ProneEndWeaponTwoHandedAnimation);
}

/**
 * @brief Get the prone idle animation based on the current armed state
 * @return The prone idle animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetProneIdleAnimation() const
{
	return bIsAiming
		? GetAnimation(ProneIdleAnimation, ProneIdleWeaponAimOneHandedAnimation, ProneIdleWeaponAimTwoHandedAnimation)
		: GetAnimation(ProneIdleAnimation, ProneIdleWeaponOneHandedAnimation, ProneIdleWeaponTwoHandedAnimation);
}

/**
 * @brief Get the prone walk animation based on the current armed state
 * @return The prone walk animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetProneMoveAnimation() const
{
	return bIsAiming
		? GetAnimation(ProneMoveAnimation, ProneMoveWeaponAimOneHandedAnimation, ProneMoveWeaponAimTwoHandedAnimation)
		: GetAnimation(ProneMoveAnimation, ProneMoveWeaponOneHandedAnimation, ProneMoveWeaponTwoHandedAnimation);
}

/**
 * @brief Get the stomp start animation based on the current armed state
 * @return The stomp start animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetStompStartAnimation() const
{
	return bIsAiming
		? GetAnimation(StompStartAnimation, StompStartWeaponAimOneHandedAnimation, StompStartWeaponAimTwoHandedAnimation)
		: GetAnimation(StompStartAnimation, StompStartWeaponOneHandedAnimation, StompStartWeaponTwoHandedAnimation);
}

/**
 * @brief Get the stomp fall animation based on the current armed state
 * @return The stomp fall animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetStompFallAnimation() const
{
	return bIsAiming
		? GetAnimation(StompFallAnimation, StompFallWeaponAimOneHandedAnimation, StompFallWeaponAimTwoHandedAnimation)
		: GetAnimation(StompFallAnimation, StompFallWeaponOneHandedAnimation, StompFallWeaponTwoHandedAnimation);
}

/**
 * @brief Get the stomp fall animation based on the current armed state
 * @return The stomp fall animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetStompLandAnimation() const
{
	return bIsAiming
		? GetAnimation(StompLandAnimation, StompLandWeaponAimOneHandedAnimation, StompLandWeaponAimTwoHandedAnimation)
		: GetAnimation(StompLandAnimation, StompLandWeaponOneHandedAnimation, StompLandWeaponTwoHandedAnimation);
}

/**
 * @brief Get the slide start animation based on the current armed state
 * @return The slide start animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetSlideStartAnimation() const
{
	return bIsAiming
		? GetAnimation(SlideStartAnimation, SlideStartWeaponAimOneHandedAnimation, SlideStartWeaponAimTwoHandedAnimation)
		: GetAnimation(SlideStartAnimation, SlideStartWeaponOneHandedAnimation, SlideStartWeaponTwoHandedAnimation);
}

/**
 * @brief Get the slide end animation based on the current armed state
 * @return The slide end animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetSlideEndAnimation() const
{
	return bIsAiming
		? GetAnimation(SlideEndAnimation, SlideEndWeaponAimOneHandedAnimation, SlideEndWeaponAimTwoHandedAnimation)
		: GetAnimation(SlideEndAnimation, SlideEndWeaponOneHandedAnimation, SlideEndWeaponTwoHandedAnimation);
}

/**
 * @brief Get the slide loop animation based on the current armed state
 * @return The slide loop animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetSlideLoopAnimation() const
{
	return bIsAiming
		? GetAnimation(SlideLoopAnimation, SlideLoopWeaponAimOneHandedAnimation, SlideLoopWeaponAimTwoHandedAnimation)
		: GetAnimation(SlideLoopAnimation, SlideLoopWeaponOneHandedAnimation, SlideLoopWeaponTwoHandedAnimation);
}

/**
 * @brief Get an animation based on the current armed state
 * @param UnarmedAnimation The unarmed animation
 * @param WeaponOneHandedAnimation The one handed weapon animation
 * @param WeaponTwoHandedAnimation The two handed weapon animation
 * @return The animation to play
 */
UAnimSequence* UUSKCharacterAnimationInstance::GetAnimation(UAnimSequence* UnarmedAnimation,
	UAnimSequence* WeaponOneHandedAnimation, UAnimSequence* WeaponTwoHandedAnimation) const
{
	if (!IsValid(Character) || !IsValid(Character->GetWeapon()))
	{
		return UnarmedAnimation;
	}

	switch (Character->GetWeapon()->WeaponType)
	{
	case EWeaponType::WeaponOneHanded:
		return WeaponOneHandedAnimation;
	case EWeaponType::WeaponTwoHanded:
		return WeaponTwoHandedAnimation;
	default:
		USK_LOG_ERROR("Invalid weapon type");
		return nullptr;
	}
}