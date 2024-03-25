// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "USK/Character/USKCharacter.h"
#include "Weapon.h"
#include "WeaponUtils.generated.h"

/**
 * @brief A Blueprint Function Library class used to manage weapons
 */
UCLASS()
class USK_API UWeaponUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Equip a weapon to a character
	 * @param Owner The owner character
	 * @param WeaponClass The weapon class to equip
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Weapons")
	static void EquipWeapon(AUSKCharacter* Owner, TSubclassOf<AWeapon> WeaponClass);	
};