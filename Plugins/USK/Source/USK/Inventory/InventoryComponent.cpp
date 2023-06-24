// Created by Henry Jooste

#include "InventoryComponent.h"

#include "InventoryItem.h"
#include "Kismet/GameplayStatics.h"
#include "USK/Logger/Log.h"

/**
 * @brief Overridable native event for when play begins for this actor
 */
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	UGameInstance* CurrentGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	GameInstance = dynamic_cast<UUSKGameInstance*>(CurrentGameInstance);

	if (AutoSave)
	{
		LoadInventory();
	}
}

/**
 * @brief Get all the item currently in the inventory
 * @return An array of all the items in the inventory
 */
TArray<FInventoryItem> UInventoryComponent::GetItems() const
{
	TArray<FName> Ids;
	TArray<int> Amounts;
	Items.GenerateKeyArray(Ids);
	Items.GenerateValueArray(Amounts);
	
	TArray<FInventoryItem> InventoryItems;
	for (int Index = 0; Index < Items.Num(); Index++)
	{
		FInventoryItem Item;
		Item.Id = Ids[Index];
		Item.Amount = Amounts[Index];
		InventoryItems.Add(Item);
	}

	return InventoryItems;
}

/**
 * @brief Add an item to the inventory
 * @param Id The ID of the item to add
 * @param Amount The amount to add
 */
void UInventoryComponent::AddItem(const FName Id, const int Amount)
{	
	if (Items.Contains(Id))
	{
		Items[Id] += Amount;
	}
	else
	{
		Items.Add(Id, Amount);
	}

	if (EnforceMaxAmount && Items[Id] > MaxAmount)
	{
		Items[Id] = MaxAmount;
	}

	if (Items[Id] <= 0)
	{
		RemoveAll(Id);
	}
	else
	{
		OnInventoryItemUpdated.Broadcast(Id, Items[Id]);
	}

	if (AutoSave)
	{
		SaveInventory();
	}
}

/**
 * @brief Remove an item from the inventory
 * @param Id The ID of the item to remove
 * @param Amount The amount to remove
 */
void UInventoryComponent::RemoveItem(const FName Id, const int Amount)
{
	AddItem(Id, -Amount);
}

/**
 * @brief Remove all the items with the specified ID
 * @param Id The ID of the item to remove
 */
void UInventoryComponent::RemoveAll(const FName Id)
{
	if (!Items.Contains(Id))
	{
		return;
	}

	Items.Remove(Id);
	OnInventoryItemUpdated.Broadcast(Id, 0);
	
	if (AutoSave)
	{
		SaveInventory();
	}
}

/**
 * @brief Remove all items from the inventory
 */
void UInventoryComponent::Clear()
{
	TArray<FName> Ids;
	Items.GenerateKeyArray(Ids);

	for (const FName Id : Ids)
	{
		OnInventoryItemUpdated.Broadcast(Id, 0);
	}
	
	Items.Empty();
	if (AutoSave)
	{
		SaveInventory();
	}
}

/**
 * @brief Load the inventory data
 */
void UInventoryComponent::LoadInventory()
{
	if (!IsValid(GameInstance))
	{
		USK_LOG_ERROR("Unable to load inventory. Game instance is not valid");
		return;
	}
	
	UUSKSaveGame* SaveData = GameInstance->GetSaveData();
	if (!IsValid(SaveData))
	{
		USK_LOG_ERROR("Unable to load inventory. Save data is not valid");
		return;
	}

	Items.Empty();
	FInventoryData* InventoryData = SaveData->InventoryData.Find(InventoryId);
	if (InventoryData == nullptr)
	{
		USK_LOG_WARNING("Unable to load inventory. No inventory data found");
		return;
	}

	for (int Index = 0; Index < InventoryData->Items.Num(); Index++)
	{
		const FInventoryItem Item = (*InventoryData).Items[Index];
		Items.Add(Item.Id, Item.Amount);
		OnInventoryItemUpdated.Broadcast(Item.Id, Item.Amount);
	}

	USK_LOG_INFO("Inventory loaded");
}

/**
 * @brief Save the inventory data
 */
void UInventoryComponent::SaveInventory()
{
	if (!IsValid(GameInstance))
	{
		USK_LOG_ERROR("Unable to save inventory. Game instance is not valid");
		return;
	}
	
	UUSKSaveGame* SaveData = GameInstance->GetSaveData();
	if (!IsValid(SaveData))
	{
		USK_LOG_ERROR("Unable to save inventory. Save data is not valid");
		return;
	}

	if (SaveData->InventoryData.Contains(InventoryId))
	{
		SaveData->InventoryData.Remove(InventoryId);
	}

	FInventoryData Data;
	Data.Items = GetItems();
	SaveData->InventoryData.Add(InventoryId, Data);
	GameInstance->SaveData();

	USK_LOG_INFO("Inventory saved");
}