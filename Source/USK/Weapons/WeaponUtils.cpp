// Created by Henry Jooste

#include "WeaponUtils.h"

#include "Engine/World.h"
#include "USK/Character/USKCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Equip a weapon to a character
 * @param Owner The owner character
 * @param WeaponClass The weapon class to equip
 */
void UWeaponUtils::EquipWeapon(AUSKCharacter* Owner, const TSubclassOf<AWeapon> WeaponClass)
{
	if (!IsValid(Owner))
	{
		USK_LOG_ERROR("Owner is not valid");
		return;
	}

	if (!IsValid(WeaponClass))
	{
		USK_LOG_ERROR("Weapon class is not valid");
		return;
	}
	
	AWeapon* CurrentWeapon = Owner->GetWeapon();
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->Unequip();
	}

	AWeapon* Weapon = Owner->GetWorld()->SpawnActor<AWeapon>(WeaponClass);
	if (!IsValid(Weapon))
	{
		USK_LOG_ERROR("Failed to spawn weapon");
		return;
	}

	Weapon->Equip(Owner, true);
	Owner->OnNewWeaponEquipped(Weapon);
}
