// Created by Henry Jooste

#include "WeaponAmmoItem.h"

#include "USK/Character/USKCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Check if the item can be collected
 * @param Collector A pointer to the actor that is trying to collect the item
 * @return A boolean value indicating if the item can be collected
 */
bool AWeaponAmmoItem::CanCollectItem_Implementation(AActor* Collector) const
{
	if (!Super::CanCollectItem_Implementation(Collector))
	{
		return false;
	}

	const AUSKCharacter* Character = dynamic_cast<AUSKCharacter*>(Collector);
	if (!IsValid(Character))
	{
		USK_LOG_ERROR("Collector is not a valid character");
		return false;
	}
	
	const AWeapon* Weapon = Character->GetWeapon();
	if (!IsValid(Weapon))
	{
		USK_LOG_INFO("Character doesn't have a weapon");
		return false;
	}

	if (Weapon->bInfiniteAmmo || Weapon->GetAmmoRemaining() >= Weapon->Ammo)
	{
		USK_LOG_INFO("Current weapon doesn't need ammo");
		return false;
	}

	if (bAddToAnyWeapon)
	{
		return true;
	}

	for (const TSubclassOf<AWeapon> WeaponClass : AllowedWeapons)
	{
		if (Weapon->IsA(WeaponClass))
		{
			return true;
		}
	}

	return false;
}

/**
 * @brief Called after the item is collected
 * @param Collector A pointer to the actor that collected the item
 */
void AWeaponAmmoItem::OnItemCollected_Implementation(AActor* Collector)
{
	Super::OnItemCollected_Implementation(Collector);
	
	const AUSKCharacter* Character = dynamic_cast<AUSKCharacter*>(Collector);
	AWeapon* Weapon = Character->GetWeapon();
	Weapon->AddAmmo(Ammo);
}
