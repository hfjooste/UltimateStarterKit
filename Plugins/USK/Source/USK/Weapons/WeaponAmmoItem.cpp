// Created by Henry Jooste

#include "WeaponAmmoItem.h"

#include "USK/Character/USKCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Called after the item is collected
 * @param Collector A pointer to the actor that collected the item
 */
void AWeaponAmmoItem::OnItemCollected_Implementation(AActor* Collector)
{
	Super::OnItemCollected_Implementation(Collector);

	const AUSKCharacter* Character = dynamic_cast<AUSKCharacter*>(Collector);
	if (!IsValid(Character))
	{
		USK_LOG_ERROR("Collector is not a valid character");
		return;
	}
	
	AWeapon* Weapon = Character->GetWeapon();
	if (!IsValid(Weapon))
	{
		USK_LOG_INFO("Character doesn't have a weapon");
		return;
	}

	if (bAddToAnyWeapon)
	{
		Weapon->AddAmmo(Ammo);
		return;
	}

	for (const TSubclassOf<AWeapon> WeaponClass : AllowedWeapons)
	{
		if (Weapon->IsA(WeaponClass))
		{
			Weapon->AddAmmo(Ammo);
			return;
		}
	}
}
