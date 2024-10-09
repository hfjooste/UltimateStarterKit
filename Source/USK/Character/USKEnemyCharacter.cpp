// Created by Henry Jooste

#include "USKEnemyCharacter.h"

#include "AIController.h"
#include "Algo/RandomShuffle.h"
#include "USK/Components/AttackableObjectComponent.h"
#include "USK/AI/EnemyPatrolPoint.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the enemy character
 */
AUSKEnemyCharacter::AUSKEnemyCharacter()
{
	AttackCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Collider"));
	AttackableObjectComponent = CreateDefaultSubobject<UAttackableObjectComponent>(TEXT("Attackable Object Component"));
	
	AttackCollider->SetupAttachment(GetMesh(), AttackColliderAttachBoneName);
	AttackCollider->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

/**
 * @brief Overridable native event for when play begins for this actor
 */
void AUSKEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AttackCollider->OnComponentBeginOverlap.AddDynamic(this, &AUSKEnemyCharacter::OnAttackColliderOverlap);
	UpdateSpawnState(bUseSpawningAnimation);
	SetActorHiddenInGame(bUseSpawningAnimation);
	
	InitializePatrolPoints();	
	if (IsValid(BehaviorTree))
	{
		AAIController* AiController = dynamic_cast<AAIController*>(GetController());
		if (IsValid(AiController))
		{
			AiController->RunBehaviorTree(BehaviorTree);
		}
	}
}

/**
 * @brief Overridable native event for when the actor is being destroyed
 */
void AUSKEnemyCharacter::BeginDestroy()
{
	Super::BeginDestroy();
	RushAttackCooldownTimerHandle.Invalidate();
}

/**
 * @brief Get the array of patrol point locations
 * @return The array of patrol point locations
 */
TArray<FVector> AUSKEnemyCharacter::GetPatrolPointLocations()
{
	return PatrolPointLocations;
}

/**
 * @brief Update the spawning state of the enemy
 * @param NewValue The new spawning state value
 */
void AUSKEnemyCharacter::UpdateSpawnState(const bool NewValue)
{
	bIsSpawning = NewValue;
}

/**
 * @brief Check if the enemy is busy spawning
 * @return A boolean value indicating if the enemy is busy spawning
 */
bool AUSKEnemyCharacter::IsSpawning() const
{
	return bIsSpawning;
}

/**
 * @brief Update the dead state of the enemy
 * @param NewValue The new dead state value
 */
void AUSKEnemyCharacter::UpdateDeadState(const bool NewValue)
{
	bIsDead = NewValue;
}

/**
 * @brief Check if the enemy is dead
 * @return A boolean value indicating if the enemy is dead
 */
bool AUSKEnemyCharacter::IsDead() const
{
	return bIsDead;
}

/**
 * @brief Start the staggered state of the enemy
 * @param StaggerDuration The duration of the staggered state
 */
void AUSKEnemyCharacter::StartStaggeredState(const float StaggerDuration)
{
	bIsStaggered = true;
	
	GetWorld()->GetTimerManager().ClearTimer(StaggerTimerHandle);
	if (StaggerDuration <= 0.0f)
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(StaggerTimerHandle, this,
		&AUSKEnemyCharacter::EndStaggeredState, StaggerDuration, false);
}

/**
 * @brief End the staggered state of the enemy
 */
void AUSKEnemyCharacter::EndStaggeredState()
{
	bIsStaggered = false;
}

/**
 * @brief Check if the enemy is staggered
 * @return A boolean value indicating if the enemy is staggered
 */
bool AUSKEnemyCharacter::IsStaggered() const
{
	return bIsStaggered;
}

/**
 * @brief Start attacking the target
 * @param AttackType The type of attack to start
 */
void AUSKEnemyCharacter::StartAttacking(const EEnemyAttackType AttackType)
{
	if (CurrentAttackType != EEnemyAttackType::None)
	{
		return;
	}

	CurrentAttackType = AttackType;

	UAnimMontage* AnimationMontage = nullptr;
	switch (CurrentAttackType)
	{
	case EEnemyAttackType::Melee:
		AnimationMontage = MeleeAttackAnimationMontages[
			FMath::RandRange(0, MeleeAttackAnimationMontages.Num() - 1)];
		break;
	case EEnemyAttackType::Ranged:
		AnimationMontage = RangedAttackAnimationMontages[
			FMath::RandRange(0, RangedAttackAnimationMontages.Num() - 1)];
		break;
	case EEnemyAttackType::Rush:
		AnimationMontage = RushAttackAnimationMontages[
			FMath::RandRange(0, RushAttackAnimationMontages.Num() - 1)];
		break;
	case EEnemyAttackType::None:
	default:
		USK_LOG_WARNING("Invalid attack started");
		break;
	}

	if (!IsValid(AnimationMontage))
	{
		USK_LOG_WARNING("Attack animation montage is invalid");
		return;
	}

	PlayAnimMontage(AnimationMontage);
	if (AttackType == EEnemyAttackType::Rush)
	{
		bCanPerformRushAttack = false;
		StartDodging(RushAttackDodgeConfig);
		
		if (RushAttackCooldown > 0.0f)
		{
			GetWorld()->GetTimerManager().SetTimer(RushAttackCooldownTimerHandle, this,
				&AUSKEnemyCharacter::AllowRushAttack, RushAttackCooldown, false);
		}
	}

	FTimerHandle EndAttackTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(EndAttackTimerHandle, this,
		&AUSKEnemyCharacter::StopAttacking, AnimationMontage->GetPlayLength(), false);
}

/**
 * @brief Stop attacking the target
 */
void AUSKEnemyCharacter::StopAttacking()
{
	CurrentAttackType = EEnemyAttackType::None;
}

/**
 * @brief Called when the attack is started
 */
void AUSKEnemyCharacter::OnAttackStarted()
{
	if (CurrentAttackType == EEnemyAttackType::Melee || CurrentAttackType == EEnemyAttackType::Rush)
	{
		AttackedActors.Empty();
		AttackCollider->AttachToComponent(GetMesh(),
			FAttachmentTransformRules::SnapToTargetIncludingScale, AttackColliderAttachBoneName);
		AttackCollider->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	}
}

/**
 * @brief Called when the attack is stopped
 */
void AUSKEnemyCharacter::OnAttackStopped()
{
	AttackCollider->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	AttackedActors.Empty();
}

/**
 * @brief Get the current attack type of the enemy
 * @return The current attack type of the enemy
 */
EEnemyAttackType AUSKEnemyCharacter::GetCurrentAttackType() const
{
	return CurrentAttackType;
}

/**
 * @brief Teleport the enemy out of the level
 */
void AUSKEnemyCharacter::TeleportOut()
{
}

/**
 * @brief Teleport the enemy into the level
 */
void AUSKEnemyCharacter::TeleportIn()
{
}

/**
 * @brief Get the location to summon an enemy
 * @return The location to summon an enemy
 */
FVector AUSKEnemyCharacter::GetSummonLocation()
{
	return FVector::ZeroVector;
}

/**
 * @brief Summon an enemy
 * @return The duration of the summon sequence
 */
float AUSKEnemyCharacter::SummonEnemy()
{
	return 0.01f;
}

/**
 * @brief Cancel summoning of an enemy
 */
void AUSKEnemyCharacter::CancelSummoningEnemy()
{
}

/**
 * @brief Start the dodge sequence
 * @param DodgeConfig The config used to dodge
 */
void AUSKEnemyCharacter::StartDodging(FDodgeConfig DodgeConfig)
{
	bIsDodging = true;
}

/**
 * @brief Stop the dodge sequence
 */
void AUSKEnemyCharacter::StopDodging()
{
	bIsDodging = false;
}

/**
 * @brief Check if the enemy is dodging
 * @return A boolean value indicating if the enemy is dodging
 */
bool AUSKEnemyCharacter::IsDodging() const
{
	return bIsDodging;
}

/**
 * @brief Check if the enemy can perform a rush attack
 * @return A boolean value indicating if the enemy can perform a rush attack
 */
bool AUSKEnemyCharacter::CanPerformRushAttack() const
{
	return bCanPerformRushAttack;
}

/**
 * @brief Initialize the patrol points
 */
void AUSKEnemyCharacter::InitializePatrolPoints()
{
	for (const AEnemyPatrolPoint* PatrolPoint : PatrolPoints)
	{
		PatrolPointLocations.Add(PatrolPoint->GetActorLocation());
	}

	if (PatrolType == EPatrolType::ReverseDirection)
	{
		for (int Index = PatrolPointLocations.Num() - 2; Index > 0; --Index)
		{
			PatrolPointLocations.Add(PatrolPoints[Index]->GetActorLocation());
		}
	}

	if (PatrolType == EPatrolType::RandomLocation)
	{
		Algo::RandomShuffle(PatrolPointLocations);
	}
}

/**
 * @brief Event when this component overlaps another actor
 * @param OverlappedComponent The component that triggered the event
 * @param OtherActor The other actor that caused the overlap event
 * @param OtherComp The other component that caused the overlap event
 * @param OtherBodyIndex The index of the other body that caused the overlap event
 * @param bFromSweep A boolean value indicating if the overlap event was caused by a sweep 
 * @param SweepResult The result of the sweep that caused the overlap event
 */
void AUSKEnemyCharacter::OnAttackColliderOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsDead() || OtherActor == this || AttackedActors.Contains(OtherActor))
	{
		return;
	}

	const UAttackableObjectComponent* OtherAttackableObjectComponent = dynamic_cast<UAttackableObjectComponent*>(
		OtherActor->GetComponentByClass(UAttackableObjectComponent::StaticClass()));
	if (IsValid(OtherAttackableObjectComponent))
	{
		AttackedActors.Add(OtherActor);
		OtherAttackableObjectComponent->NotifyAttack(this);
	}	
}

/**
 * @brief Allow the enemy to perform a rush attack
 */
void AUSKEnemyCharacter::AllowRushAttack()
{
	bCanPerformRushAttack = true;
}
