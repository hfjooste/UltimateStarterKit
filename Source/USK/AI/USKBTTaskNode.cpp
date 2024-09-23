// Created by Henry Jooste

#include "USKBTTaskNode.h"

#include "AIController.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "USK/Character/USKEnemyCharacter.h"
#include "Navigation/PathFollowingComponent.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the task node
 */
UUSKBTTaskNode::UUSKBTTaskNode()
{
	bNotifyTick = false;
	bNotifyTaskFinished = false;
}

/**
 * @brief Move the character to a specific location
 * @param EnemyCharacter The character to move
 * @param TargetLocation The target location of the character
 * @param AcceptanceRadius The radius around the point that the character must reach to consider the point reached
 * @param TargetReached A boolean value indicating if the character reached the target location
 * @return A boolean value indicating if the character was moved
 */
bool UUSKBTTaskNode::MoveToLocation(AUSKEnemyCharacter* EnemyCharacter, const FVector& TargetLocation,
                                    const float AcceptanceRadius, bool& TargetReached) const
{
	AAIController* Controller = UAIBlueprintHelperLibrary::GetAIController(EnemyCharacter);
	if (!IsValid(Controller))
	{
		USK_LOG_ERROR("AI Controller is invalid");
		TargetReached = false;
		return false;
	}
	
	const UNavigationSystemV1* NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!IsValid(NavigationSystem))
	{
		USK_LOG_ERROR("Navigation system is invalid");
		TargetReached = false;
		return false;
	}
	
	const UNavigationPath* Path = NavigationSystem->FindPathToLocationSynchronously(GetWorld(),
		EnemyCharacter->GetActorLocation(), TargetLocation);		
	if (!IsValid(Path) || !Path->IsValid() || Path->IsPartial())
	{		
		TargetReached = true;
		Controller->StopMovement();
		return true;
	}

	const EPathFollowingRequestResult::Type Result = Controller->MoveToLocation(TargetLocation, AcceptanceRadius,
		false, true, true,
		true, nullptr, false);
	if (Result == EPathFollowingRequestResult::Type::Failed)
	{
		USK_LOG_ERROR("Failed to move to location");
		TargetReached = false;
		return false;
	}
	
	if (FMath::IsNearlyEqual(EnemyCharacter->GetActorLocation().X, TargetLocation.X, AcceptanceRadius) &&
		FMath::IsNearlyEqual(EnemyCharacter->GetActorLocation().Y, TargetLocation.Y, AcceptanceRadius))
	{		
		Controller->StopMovement();
		TargetReached = true;
		return true;
	}

	TargetReached = false;
	return true;
}

/**
 * @brief Stop all movement of the character
 * @param EnemyCharacter A reference to the character
 */
void UUSKBTTaskNode::StopMovement(AUSKEnemyCharacter* EnemyCharacter) const
{
	AAIController* Controller = UAIBlueprintHelperLibrary::GetAIController(EnemyCharacter);
	if (!IsValid(EnemyCharacter))
	{
		USK_LOG_ERROR("AI Controller is invalid");
		return;
	}

	Controller->StopMovement();
}

/**
 * @brief Focus a specific actor
 * @param EnemyCharacter The character that should focus the actor
 * @param Target The actor to focus
 */
void UUSKBTTaskNode::FocusActor(AUSKEnemyCharacter* EnemyCharacter, AActor* Target)
{
	if (!IsValid(Target))
	{
		ClearFocus(EnemyCharacter);
		return;
	}
	
	AAIController* Controller = UAIBlueprintHelperLibrary::GetAIController(EnemyCharacter);
	if (!IsValid(Controller))
	{
		USK_LOG_ERROR("AI Controller is invalid");
		return;
	}

	Controller->SetFocus(Target, EAIFocusPriority::Default);
}

/**
 * @brief Focus a specific location
 * @param EnemyCharacter The character that should focus the location
 * @param Location The location to focus
 */
void UUSKBTTaskNode::FocusLocation(AUSKEnemyCharacter* EnemyCharacter, const FVector& Location)
{	
	AAIController* Controller = UAIBlueprintHelperLibrary::GetAIController(EnemyCharacter);
	if (!IsValid(Controller))
	{
		USK_LOG_ERROR("AI Controller is invalid");
		return;
	}

	Controller->SetFocalPoint(Location, EAIFocusPriority::Default);
}

/**
 * @brief Stop focusing
 * @param EnemyCharacter The character that should stop focusing
 */
void UUSKBTTaskNode::ClearFocus(AUSKEnemyCharacter* EnemyCharacter)
{
	AAIController* Controller = UAIBlueprintHelperLibrary::GetAIController(EnemyCharacter);
	if (!IsValid(Controller))
	{
		USK_LOG_ERROR("AI Controller is invalid");
		return;
	}

	Controller->ClearFocus(EAIFocusPriority::Default);
}

/**
 * @brief Get the last reachable location towards a target location
 * @param EnemyCharacter The character to move
 * @param TargetLocation The target location of the character
 * @return The last reachable location
 */
FVector UUSKBTTaskNode::GetLastReachableLocation(const AUSKEnemyCharacter* EnemyCharacter,
	const FVector& TargetLocation) const
{
	const UNavigationSystemV1* NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!IsValid(NavigationSystem))
	{
		USK_LOG_ERROR("Navigation system is invalid");
		return TargetLocation;
	}

	const UNavigationPath* Path = NavigationSystem->FindPathToLocationSynchronously(GetWorld(),
		EnemyCharacter->GetActorLocation(), TargetLocation);
	if (!Path->IsValid() || Path->PathPoints.IsEmpty())
	{
		USK_LOG_ERROR("Invalid path");
		return TargetLocation;
	}
	
	return Path->PathPoints.Last();
}
