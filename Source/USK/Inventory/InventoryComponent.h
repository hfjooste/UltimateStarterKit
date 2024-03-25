// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USK/Core/USKGameInstance.h"
#include "InventoryComponent.generated.h"

struct FInventoryItem;

/**
 * @brief Actor component responsible for tracking data in an inventory
 */
UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class USK_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	/**
	 * @brief Event used to notify other classes every time an item in the inventory was updated
	 * @param Id The ID of the item that was updated
	 * @param Amount The new amount of the item
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInventoryItemUpdated, FName, Id, int, Amount);
	
public:
	/**
	 * @brief The ID of the inventory used when saving/loading the data
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Inventory")
	FName InventoryId;

	/**
	 * @brief Should the data in the inventory automatically be saved/loaded
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Inventory")
	bool AutoSave = true;

	/**
	 * @brief Should a maximum amount be enforced for each item?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Inventory")
	bool EnforceMaxAmount;

	/**
	 * @brief The maximum amount of each item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Inventory",
		meta=(EditCondition = "EnforceMaxAmount", EditConditionHides))
	int MaxAmount = 99;

	/**
	 * @brief Event used to notify other classes every time an item in the inventory was updated
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Inventory|Events")
	FInventoryItemUpdated OnInventoryItemUpdated;

	/**
	 * @brief Get all the item currently in the inventory
	 * @return An array of all the items in the inventory
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Inventory")
	TArray<FInventoryItem> GetItems() const;

	/**
	 * @brief Add an item to the inventory
	 * @param Id The ID of the item to add
	 * @param Amount The amount to add
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Inventory")
	void AddItem(FName Id, int Amount);

	/**
	 * @brief Remove an item from the inventory
	 * @param Id The ID of the item to remove
	 * @param Amount The amount to remove
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Inventory")
	void RemoveItem(FName Id, int Amount);

	/**
	 * @brief Remove all the items with the specified ID
	 * @param Id The ID of the item to remove
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Inventory")
	void RemoveAll(FName Id);

	/**
	 * @brief Remove all items from the inventory
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Inventory")
	void Clear();

	/**
	 * @brief Load the inventory data
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Inventory")
	void LoadInventory();

	/**
	 * @brief Save the inventory data
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Inventory")
	void SaveInventory();

protected:
	/**
	 * @brief Overridable native event for when play begins for this actor
	 */
	virtual void BeginPlay() override;

private:
	/**
	 * @brief A reference to the game instance used to save/load the inventory data
	 */
	UPROPERTY()
	UUSKGameInstance* GameInstance;

	/**
	 * @brief The map of all items in the inventory
	 */
	TMap<FName, int> Items;	
};
