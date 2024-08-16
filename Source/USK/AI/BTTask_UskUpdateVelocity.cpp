// Created by Henry Jooste

#include "BTTask_UskUpdateVelocity.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "USK/Character/USKEnemyCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the task node
 */
UBTTask_UskUpdateVelocity::UBTTask_UskUpdateVelocity()
{
	NodeName = "Update Velocity";
}

/**
 * @brief Start executing the task
 * @param OwnerComp A reference to the behaviour tree executing the task
 * @param NodeMemory Memory block used to store runtime data
 * @return The result of the task (Succeeded, Failed or InProgress)
 */
EBTNodeResult::Type UBTTask_UskUpdateVelocity::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	MovementComponent->Velocity = NewVelocity;	
	return EBTNodeResult::Succeeded;
}
