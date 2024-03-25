// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "USK/Items/CollectableItem.h"
#include "WeaponItem.generated.h"

/**
 * @brief A weapon item that can be picked up by a character
 */
UCLASS()
class USK_API AWeaponItem : public ACollectableItem
{
	GENERATED_BODY()

public:
	/**
	 * @brief The weapon assigned to this item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Item")
	TSubclassOf<AWeapon> WeaponClass;

	/**
	 * @brief Called after the item is collected
	 * @param Collector A pointer to the actor that collected the item
	 */
	virtual void OnItemCollected_Implementation(AActor* Collector) override;
};
