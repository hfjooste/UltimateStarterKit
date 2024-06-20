// Created by Henry Jooste

#include "USKEnemyCharacter.h"

#include "AIController.h"
#include "Algo/RandomShuffle.h"
#include "USK/Components/AttackableObjectComponent.h"
#include "USK/AI/EnemyPatrolPoint.h"

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
	AttackCollider->AttachToComponent(GetMesh(),
		FAttachmentTransformRules::SnapToTargetIncludingScale, AttackColliderAttachBoneName);
	AttackCollider->OnComponentBeginOverlap.AddDynamic(this, &AUSKEnemyCharacter::OnAttackColliderOverlap);
	
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
 * @brief Get the array of patrol point locations
 * @return The array of patrol point locations
 */
TArray<FVector> AUSKEnemyCharacter::GetPatrolPointLocations()
{
	return PatrolPointLocations;
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
	CurrentAttackType = AttackType;
	if (CurrentAttackType == EEnemyAttackType::Melee)
	{
		AttackCollider->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	}
}

/**
 * @brief Stop attacking the target
 */
void AUSKEnemyCharacter::StopAttacking()
{
	CurrentAttackType = EEnemyAttackType::None;
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
