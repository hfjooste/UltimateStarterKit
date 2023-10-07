// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "USK/Items/CollectableItem.h"
#include "WeaponAmmoItem.generated.h"

/**
 * @brief A weapon ammo item that can be picked up by a character
 */
UCLASS()
class USK_API AWeaponAmmoItem : public ACollectableItem
{
	GENERATED_BODY()

public:
	/**
	 * @brief The amount of ammo to add to the weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Item")
	int Ammo = 10;
	
	/**
	 * @brief Should the ammo be added to any weapon?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Item")
	bool bAddToAnyWeapon = false;
	
	/**
	 * @brief The weapons that can use this ammo
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Item",
		meta=(EditCondition = "!bAddToAnyWeapon", EditConditionHides))
	TArray<TSubclassOf<AWeapon>> AllowedWeapons;

	/**
	 * @brief Check if the item can be collected
	 * @param Collector A pointer to the actor that is trying to collect the item
	 * @return A boolean value indicating if the item can be collected
	 */
	virtual bool CanCollectItem_Implementation(AActor* Collector) const override;

	/**
	 * @brief Called after the item is collected
	 * @param Collector A pointer to the actor that collected the item
	 */
	virtual void OnItemCollected_Implementation(AActor* Collector) override;
};
