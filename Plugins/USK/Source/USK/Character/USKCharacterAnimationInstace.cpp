// Created by Henry Jooste

#include "USKCharacterAnimationInstance.h"
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
	if (Character == nullptr)
	{
		USK_LOG_WARNING("Character is nullptr");
		return;
	}

	MovementSpeed = UKismetMathLibrary::VSizeXY(Character->GetMovementComponent()->Velocity);
	IsInAir = Character->GetMovementComponent()->IsFalling();

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