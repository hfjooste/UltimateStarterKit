// Created by Henry Jooste

#include "BTTask_UskInitialize.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "USK/Character/USKEnemyCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Constructor for the task node
 */
UBTTask_UskInitialize::UBTTask_UskInitialize()
{
	NodeName = "Initialize AI";
}

/**
 * @brief Start executing the task
 * @param OwnerComp A reference to the behaviour tree executing the task
 * @param NodeMemory Memory block used to store runtime data
 * @return The result of the task (Succeeded, Failed or InProgress)
 */
EBTNodeResult::Type UBTTask_UskInitialize::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!IsValid(Blackboard))
	{
		USK_LOG_ERROR("Blackboard is invalid");
		return EBTNodeResult::Failed;
	}

	const AAIController* AiController = OwnerComp.GetAIOwner();
	if (!IsValid(AiController))
	{
		USK_LOG_ERROR("AI Controller is invalid");
		return EBTNodeResult::Failed;
	}

	AUSKEnemyCharacter* EnemyCharacter = dynamic_cast<AUSKEnemyCharacter*>(AiController->GetPawn());
	if (!IsValid(EnemyCharacter))
	{
		USK_LOG_ERROR("Enemy character is invalid");
		return EBTNodeResult::Failed;
	}

	AActor* TargetActor = UGameplayStatics::GetActorOfClass(GetWorld(), EnemyCharacter->TargetActorClass);
	if (!IsValid(TargetActor))
	{
		USK_LOG_ERROR("Target actor is invalid");
		return EBTNodeResult::Failed;
	}

	Blackboard->SetValueAsBool(InitializedKey.SelectedKeyName, true);
	Blackboard->SetValueAsObject(OwnerKey.SelectedKeyName, EnemyCharacter);
	Blackboard->SetValueAsObject(TargetActorKey.SelectedKeyName, TargetActor);
	Blackboard->SetValueAsVector(StartLocationKey.SelectedKeyName, EnemyCharacter->GetActorLocation());
	return EBTNodeResult::Succeeded;
}
