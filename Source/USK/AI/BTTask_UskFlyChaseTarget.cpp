// Created by Henry Jooste

#include "BTTask_UskFlyChaseTarget.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "USK/Character/USKEnemyCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the task node
 */
UBTTask_UskFlyChaseTarget::UBTTask_UskFlyChaseTarget()
{
	NodeName = "Fly Chase Target";
}

/**
 * @brief Start executing the task
 * @param OwnerComp A reference to the behaviour tree executing the task
 * @param NodeMemory Memory block used to store runtime data
 * @return The result of the task (Succeeded, Failed or InProgress)
 */
EBTNodeResult::Type UBTTask_UskFlyChaseTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(Blackboard))
	{
		USK_LOG_ERROR("Blackboard is invalid");
		return EBTNodeResult::Failed;
	}

	AUSKEnemyCharacter* EnemyCharacter = dynamic_cast<AUSKEnemyCharacter*>(
		Blackboard->GetValueAsObject(OwnerKey.SelectedKeyName));
	if (!IsValid(EnemyCharacter))
	{
		USK_LOG_ERROR("Enemy character is invalid");
		return EBTNodeResult::Failed;
	}

	UCharacterMovementComponent* MovementComponent = EnemyCharacter->GetCharacterMovement();
	if (!IsValid(MovementComponent))
	{
		USK_LOG_ERROR("Enemy character's movement component is invalid");
		return EBTNodeResult::Failed;
	}

	const FVector TargetLocation = Blackboard->GetValueAsVector(TargetLocationKey.SelectedKeyName);
	const TArray<FVector> PossibleLocations = GetPossibleLocations(EnemyCharacter);
	const FVector CurrentVelocity = MovementComponent->Velocity;
	FVector TargetVelocity = CurrentVelocity;

	FVector BestLocation;
	if (FindBestLocation(EnemyCharacter, PossibleLocations, TargetLocation, BestLocation))
	{
		TargetVelocity = UKismetMathLibrary::GetDirectionUnitVector(
			EnemyCharacter->GetActorLocation(), BestLocation) * MovementComponent->MaxFlySpeed;
	}

	MovementComponent->Velocity = UKismetMathLibrary::VInterpTo(CurrentVelocity, TargetVelocity,
		GetWorld()->GetDeltaSeconds(), VelocityUpdateInterpSpeed);
	return EBTNodeResult::Succeeded;
}

/**
 * @brief Get the possible locations that the enemy character can move to
 * @param EnemyCharacter The enemy character
 * @return The possible locations
 */
TArray<FVector> UBTTask_UskFlyChaseTarget::GetPossibleLocations(AUSKEnemyCharacter* EnemyCharacter) const
{
	TArray<FVector> PossibleLocations;
	const float GroundOffset = GetGroundOffset(EnemyCharacter);
	const FVector CurrentLocation = EnemyCharacter->GetActorLocation() + FVector(0.0f, 0.0f, GroundOffset);
	
	for (int X = GridIndexMin; X <= GridIndexMax; ++X)
	{
		for (int Y = GridIndexMin; Y <= GridIndexMax; ++Y)
		{
			for (int Z = GridIndexMin; Z <= GridIndexMax; ++Z)
			{
				PossibleLocations.Add(CurrentLocation + (FVector(X, Y, Z) * GridBlockSize * 2.0f));
			}
		}
	}

	return PossibleLocations;
}

/**
 * @brief Get the offset from the ground that the enemy character should maintain
 * @param EnemyCharacter The enemy character
 * @return The offset from the ground
 */
float UBTTask_UskFlyChaseTarget::GetGroundOffset(AUSKEnemyCharacter* EnemyCharacter) const
{
	const FVector CurrentLocation = EnemyCharacter->GetActorLocation();
	const FVector TargetLocation = CurrentLocation - FVector(0.0f, 0.0f, MinDistanceFromGround);
	
	FHitResult HitResult;
	if (!UKismetSystemLibrary::LineTraceSingle(GetWorld(), CurrentLocation, TargetLocation,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
		{ EnemyCharacter }, EDrawDebugTrace::None, HitResult, true))
	{
		return 0.0f;
	}

	return MinDistanceFromGround - HitResult.Distance;
}

/**
 * @brief Find the best location for the enemy character to move to
 * @param EnemyCharacter The enemy character
 * @param PossibleLocations The possible locations
 * @param TargetLocation The target location
 * @param BestLocation The best location
 * @return A boolean value indicating if the best location was found
 */
bool UBTTask_UskFlyChaseTarget::FindBestLocation(AUSKEnemyCharacter* EnemyCharacter,
	TArray<FVector> PossibleLocations, const FVector& TargetLocation, FVector& BestLocation) const
{
	bool BestLocationFound = false;
	bool AnyLocationFound = false;
	float BestLocationDistance = FLT_MAX;
	FVector BestInvalidLocation = BestLocation;
	
	for (FVector Location : PossibleLocations)
	{
		if (!IsLocationValid(EnemyCharacter, Location))
		{
			continue;
		}

		const float Distance = UKismetMathLibrary::Vector_Distance(Location, TargetLocation);
		if (Distance >= BestLocationDistance)
		{
			continue;
		}

		if (!CanSeeTargetLocation(EnemyCharacter, Location, TargetLocation))
		{
			BestInvalidLocation = Location;
			AnyLocationFound = true;
			continue;
		}

		BestLocationDistance = Distance;
		BestLocation = Location;
		BestLocationFound = true;
		AnyLocationFound = true;
	}

	if (!AnyLocationFound)
	{
		return false;
	}

	if (!BestLocationFound)
	{
		BestLocation = BestInvalidLocation;
	}

	return true;
}

/**
 * @brief Check if the location is valid
 * @param EnemyCharacter The enemy character
 * @param Location The location to check
 * @return A boolean value indicating if the location is valid
 */
bool UBTTask_UskFlyChaseTarget::IsLocationValid(AUSKEnemyCharacter* EnemyCharacter, const FVector& Location) const
{
	TArray<AActor*> OverlappingActors;
	return !UKismetSystemLibrary::BoxOverlapActors(GetWorld(), Location, FVector(GridBlockSize),
		ObstacleObjectTypes, AActor::StaticClass(), { EnemyCharacter }, OverlappingActors);
}

/**
 * @brief Check if the enemy can see the target from a specific location
 * @param EnemyCharacter The enemy character
 * @param Location The location to check
 * @param TargetLocation The target location
 * @return A boolean value indicating if the enemy can see the target
 */
bool UBTTask_UskFlyChaseTarget::CanSeeTargetLocation(AUSKEnemyCharacter* EnemyCharacter,
	const FVector& Location, const FVector& TargetLocation) const
{
	FHitResult HitResult;
	return !UKismetSystemLibrary::LineTraceSingle(GetWorld(), Location, TargetLocation,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
		{ EnemyCharacter }, EDrawDebugTrace::None, HitResult, true);
}
