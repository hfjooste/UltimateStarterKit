// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "AttackableObjectComponent.generated.h"

/**
 * @brief Component used to allow objects to be attacked
 */
UCLASS()
class USK_API UAttackableObjectComponent : public UActorComponent
{
	GENERATED_BODY()

	/**
	 * @brief Event used to notify other classes when the object is attacked
	 * @param Attacker A reference to the attacker
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttackedDelegate, AActor*, Attacker);
	
public:
	/**
	 * @brief Event used to notify other classes when the object is attacked
	 */
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Ultimate Starter Kit|Components")
	FAttackedDelegate OnAttacked;

	/**
	 * @brief Notify subscribers that the object was attacked
	 * @param Attacker A reference to the attacker
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Components")
	void NotifyAttack(AActor* Attacker) const;
};