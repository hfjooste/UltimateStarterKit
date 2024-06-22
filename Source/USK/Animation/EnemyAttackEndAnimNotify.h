#pragma once

#include "CoreMinimal.h"
#include "EnemyAttackEndAnimNotify.generated.h"

/**
 * @brief Animation notify used to end enemy attacks
 */
UCLASS()
class USK_API UEnemyAttackEndAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Called when the anim notify is triggered
	 * @param MeshComp The mesh component that triggered the notify
	 * @param Animation The animation that triggered the notify
	 * @param EventReference The reference to the notify event
	 */
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;
};
