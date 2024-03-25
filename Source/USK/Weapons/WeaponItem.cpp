// Created by Henry Jooste

#include "WeaponItem.h"

#include "WeaponUtils.h"
#include "USK/Character/USKCharacter.h"

/**
 * @brief Called after the item is collected
 * @param Collector A pointer to the actor that collected the item
 */
void AWeaponItem::OnItemCollected_Implementation(AActor* Collector)
{
	Super::OnItemCollected_Implementation(Collector);
	AUSKCharacter* Character = dynamic_cast<AUSKCharacter*>(Collector);
	UWeaponUtils::EquipWeapon(Character, WeaponClass);
}
