﻿// Created by Henry Jooste

#include "InventoryMenuItem.h"

#include "InventoryWidget.h"
#include "Components/Image.h"
#include "USK/Logger/Log.h"

/**
 * @brief Initialize an empty inventory item
 * @param Widget The widget that owns this menu item
 */
void UInventoryMenuItem::InitializeEmptyInventoryItem(UInventoryWidget* Widget)
{
	bIsEmpty = true;
	InventoryWidget = Widget;
	OnHighlighted.AddDynamic(this, &UInventoryMenuItem::UpdateInventoryPreview);
	OnSelected.AddDynamic(this, &UInventoryMenuItem::OnInventoryItemSelected);

	SetText(FText::GetEmpty());
	if (IsValid(InventoryImage))
	{
		InventoryImage->SetVisibility(ESlateVisibility::Collapsed);
	}
}

/**
 * @brief Initialize a non-empty inventory item
 * @param Widget The widget that owns this menu item
 * @param Item The item tracked by this menu item
 * @param Data The data for this menu item
 */
void UInventoryMenuItem::InitializeInventoryItem(UInventoryWidget* Widget, FInventoryItem Item, FInventoryItemData Data)
{
	InitializeEmptyInventoryItem(Widget);

	bIsEmpty = false;
	InventoryItem = Item;
	SetText(Data.Name);
	
	if (IsValid(InventoryImage))
	{
		InventoryImage->SetBrushFromTexture(Data.InventoryImage);
		InventoryImage->SetVisibility(ESlateVisibility::Visible);
	}
}

/**
 * @brief Get the inventory item tracked by this menu item
 * @return The inventory item tracked by this menu item
 */
FInventoryItem UInventoryMenuItem::GetInventoryItem()
{
	return InventoryItem;
}

/**
 * @brief Update the amount of the inventory item
 * @param Amount The new amount of the inventory item
 */
void UInventoryMenuItem::UpdateAmount(const int Amount)
{
	if (bIsEmpty)
	{
		USK_LOG_ERROR("Unable to update an empty item");
		return;
	}

	InventoryItem.Amount = Amount;
	if (Amount <= 0)
	{
		SetText(FText::GetEmpty());
		if (IsValid(InventoryImage))
		{
			InventoryImage->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

/**
 * @brief Update the inventory preview
 */
void UInventoryMenuItem::UpdateInventoryPreview()
{
	if (!IsValid(InventoryWidget))
	{
		USK_LOG_ERROR("Inventory Widget is not valid");
		return;
	}

	InventoryWidget->UpdatePreview(InventoryItem);
}

/**
 * @brief Called after the inventory item is selected
 */
void UInventoryMenuItem::OnInventoryItemSelected()
{
	if (bIsEmpty)
	{
		return;
	}
	
	if (!IsValid(InventoryWidget))
	{
		USK_LOG_ERROR("Inventory Widget is not valid");
		return;
	}

	InventoryWidget->SelectItem(InventoryItem.Id);
}