// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "InventoryItemData.h"
#include "USK/Widgets/MenuItem.h"
#include "InventoryMenuItem.generated.h"

class UInventoryWidget;

/**
 * @brief The menu item used to display an inventory item
 */
UCLASS()
class USK_API UInventoryMenuItem : public UMenuItem
{
	GENERATED_BODY()

public:
	/**
	 * @brief The image of the inventory item
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* InventoryImage;

	/**
	 * @brief Initialize an empty inventory item
	 * @param Widget The widget that owns this menu item
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Inventory")
	void InitializeEmptyInventoryItem(UInventoryWidget* Widget);

	/**
	 * @brief Initialize a non-empty inventory item
	 * @param Widget The widget that owns this menu item
	 * @param Item The item tracked by this menu item
	 * @param Data The data for this menu item
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Inventory")
	void InitializeInventoryItem(UInventoryWidget* Widget, FInventoryItem Item, FInventoryItemData Data);

	/**
	 * @brief Update the grid position of the inventory menu item
	 * @param CurrentColumn The current column of the inventory menu item
	 * @param CurrentRow The current row of the inventory menu item
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Inventory")
	void UpdateInventoryGridPosition(int CurrentColumn, int CurrentRow);

	/**
	 * @brief Get the inventory item tracked by this menu item
	 * @return The inventory item tracked by this menu item
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Inventory")
	FInventoryItem GetInventoryItem();

	/**
	 * @brief Update the amount of the inventory item
	 * @param Amount The new amount of the inventory item
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Inventory")
	void UpdateAmount(int Amount);

private:
	/**
	 * @brief A reference to the widget that owns this menu item
	 */
	UPROPERTY()
	UInventoryWidget* InventoryWidget;

	/**
	 * @brief The inventory item tracked by this menu item
	 */
	FInventoryItem InventoryItem;

	/**
	 * @brief Is the menu item empty?
	 */
	bool bIsEmpty;

	/**
	 * @brief The column of the inventory item
	 */
	int Column;

	/**
	 * @brief The row of the inventory item
	 */
	int Row;

	/**
	 * @brief Called after the inventory item is highlighted
	 */
	UFUNCTION()
	void OnInventoryItemHighlighted();

	/**
	 * @brief Called after the inventory item is selected
	 */
	UFUNCTION()
	void OnInventoryItemSelected();
};
