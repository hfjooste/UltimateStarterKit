// Created by Henry Jooste

#include "USKEnemyAnimationInstance.h"

#include "Kismet/KismetMathLibrary.h"
#include "USK/Character/USKEnemyCharacter.h"

/**
 * @brief Executed when begin play is called on the owning component
 */
void UUSKEnemyAnimationInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	EnemyCharacter = dynamic_cast<AUSKEnemyCharacter*>(TryGetPawnOwner());
}

/**
 * @brief Native update override point
 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
 */
void UUSKEnemyAnimationInstance::NativeUpdateAnimation(const float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!IsValid(EnemyCharacter))
	{
		return;
	}

	MovementSpeed = UKismetMathLibrary::VSizeXY(EnemyCharacter->GetVelocity());
}

/**
 * @brief Get the movement speed of the player
 * @return The movement speed of the player
 */
float UUSKEnemyAnimationInstance::GetMovementSpeed() const
{
	return MovementSpeed;
}