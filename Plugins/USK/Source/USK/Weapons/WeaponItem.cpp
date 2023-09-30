// Created by Henry Jooste

#include "WeaponItem.h"

#include "USK/Character/USKCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Called after the item is collected
 * @param Collector A pointer to the actor that collected the item
 */
void AWeaponItem::OnItemCollected_Implementation(AActor* Collector)
{
	Super::OnItemCollected_Implementation(Collector);

	AUSKCharacter* Character = dynamic_cast<AUSKCharacter*>(Collector);
	if (!IsValid(Character))
	{
		return;
	}

	AWeapon* CurrentWeapon = Character->GetWeapon();
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->Destroy();
	}

	AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
	if (!IsValid(Weapon))
	{
		USK_LOG_ERROR("Failed to spawn weapon");
		return;
	}

	Weapon->AttachWeapon(Character);
}
