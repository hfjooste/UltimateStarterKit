// Created by Henry Jooste

#include "AttackableObjectComponent.h"

/**
 * @brief Notify subscribers that the object was attacked
 * @param Attacker A reference to the attacker
 */
void UAttackableObjectComponent::NotifyAttack(AActor* Attacker) const
{
	OnAttacked.Broadcast(Attacker);
}