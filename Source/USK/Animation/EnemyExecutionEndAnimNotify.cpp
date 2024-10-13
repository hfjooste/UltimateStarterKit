// Created by Henry Jooste

#include "EnemyExecutionEndAnimNotify.h"

#include "USK/Character/USKEnemyCharacter.h"

/**
 * @brief Called when the anim notify is triggered
 * @param MeshComp The mesh component that triggered the notify
 * @param Animation The animation that triggered the notify
 * @param EventReference The reference to the notify event
 */
void UEnemyExecutionEndAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	AUSKEnemyCharacter* EnemyCharacter = dynamic_cast<AUSKEnemyCharacter*>(MeshComp->GetOwner());
	if (IsValid(EnemyCharacter))
	{
		EnemyCharacter->CompleteExecution(BoneName, bHideBone);
	}
}
