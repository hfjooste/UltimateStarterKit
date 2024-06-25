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

	bIsSpawning = EnemyCharacter->IsSpawning();
	MovementSpeed = UKismetMathLibrary::VSizeXY(EnemyCharacter->GetVelocity());
}

/**
 * @brief Start the spawning animation
 */
void UUSKEnemyAnimationInstance::SpawningStarted() const
{
	if (IsValid(EnemyCharacter))
	{
		EnemyCharacter->SetActorHiddenInGame(false);
	}
}

/**
 * @brief End the spawning animation
 */
void UUSKEnemyAnimationInstance::SpawningCompleted() const
{
	if (IsValid(EnemyCharacter))
	{
		EnemyCharacter->UpdateSpawnState(false);
	}
}

/**
 * @brief Check if the character is busy spawning
 * @return A boolean value indicating if the character is busy spawning
 */
bool UUSKEnemyAnimationInstance::IsSpawning() const
{
	return bIsSpawning;
}

/**
 * @brief Get the movement speed of the character
 * @return The movement speed of the character
 */
float UUSKEnemyAnimationInstance::GetMovementSpeed() const
{
	return MovementSpeed;
}