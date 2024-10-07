// Created by Henry Jooste

#include "BTDecorator_UskCanSeeTarget.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "USK/Character/USKEnemyCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the decorator
 */
UBTDecorator_UskCanSeeTarget::UBTDecorator_UskCanSeeTarget()
{
	NodeName = "Can See Target";
	bNotifyTick = false;
}

/**
 * @brief Calculate the raw condition value
 * @param OwnerComp The owner behavior tree component
 * @param NodeMemory Memory block used to store runtime data
 * @return A boolean value indicating if the condition is met
 */
bool UBTDecorator_UskCanSeeTarget::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(Blackboard))
	{
		USK_LOG_ERROR("Blackboard is invalid");
		return false;
	}

	const AUSKEnemyCharacter* EnemyCharacter = dynamic_cast<AUSKEnemyCharacter*>(
		Blackboard->GetValueAsObject(OwnerKey.SelectedKeyName));
	if (!IsValid(EnemyCharacter))
	{
		USK_LOG_ERROR("Enemy character is invalid");
		return false;
	}

	const FVector TraceStart = EnemyCharacter->GetActorLocation() + FVector(0.0f, 0.0f,
		EnemyCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	const FVector TraceEnd = Blackboard->GetValueAsVector(TargetLocationKey.SelectedKeyName);
	
	FHitResult HitResult;
	if (!UKismetSystemLibrary::LineTraceSingle(EnemyCharacter, TraceStart, TraceEnd,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false, TArray<AActor*>(), EDrawDebugTrace::None, HitResult, true))
	{
		return true;
	}

	return IgnoredClasses.Contains(HitResult.GetActor()->GetClass());
}
