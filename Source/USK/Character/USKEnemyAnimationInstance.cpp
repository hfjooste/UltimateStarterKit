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
	CurrentAttackType = EnemyCharacter->GetCurrentAttackType();
}

/**
 * @brief Get the movement speed of the player
 * @return The movement speed of the player
 */
float UUSKEnemyAnimationInstance::GetMovementSpeed() const
{
	return MovementSpeed;
}

/**
 * @brief Check if the enemy is performing a melee attack
 * @return A boolean value indicating if the enemy is performing a melee attack
 */
bool UUSKEnemyAnimationInstance::IsMeleeAttacking() const
{
	return CurrentAttackType == EEnemyAttackType::Melee;
}

/**
 * @brief Check if the enemy is performing a ranged attack
 * @return A boolean value indicating if the enemy is performing a ranged attack
 */
bool UUSKEnemyAnimationInstance::IsRangedAttacking() const
{
	return CurrentAttackType == EEnemyAttackType::Ranged;
}

/**
 * @brief Stop attacking the target
 */
void UUSKEnemyAnimationInstance::StopAttacking() const
{
	if (IsValid(EnemyCharacter))
	{
		EnemyCharacter->StopAttacking();
	}
}
