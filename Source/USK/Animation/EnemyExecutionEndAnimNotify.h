// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "EnemyExecutionEndAnimNotify.generated.h"

/**
 * @brief Animation notify used to end enemy executions
 */
UCLASS()
class USK_API UEnemyExecutionEndAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The name of the bone where the damage is applied
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit")
	FName BoneName;

	/**
	 * @brief Should the bone be hidden after the execution?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit")
	bool bHideBone;
	
	/**
	 * @brief Called when the anim notify is triggered
	 * @param MeshComp The mesh component that triggered the notify
	 * @param Animation The animation that triggered the notify
	 * @param EventReference The reference to the notify event
	 */
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;
};
