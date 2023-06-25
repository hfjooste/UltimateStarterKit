// Created by Henry Jooste

#include "InventoryWidget.h"

#include "InventoryComponent.h"
#include "InventoryItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridSlot.h"
#include "USK/Widgets/MenuItem.h"
#include "USK/Logger/Log.h"
#include "USK/Widgets/Menu.h"

/**
 * @brief Load a specific inventory
 * @param InventoryComponent The inventory to load
 */
void UInventoryWidget::LoadInventory(UInventoryComponent* InventoryComponent)
{
	if (!IsValid(InventoryComponent))
	{
		USK_LOG_ERROR("Inventory component is not valid");
		return;
	}
	
	Inventory = InventoryComponent;
	RefreshInventory();

	Inventory->OnInventoryItemUpdated.AddDynamic(this, &UInventoryWidget::RefreshItem);
}

/**
 * @brief Update the preview of the inventory
 * @param Item The item to preview
 */
void UInventoryWidget::UpdatePreview(const FInventoryItem Item) const
{
	const FInventoryItemData* Data = GetInventoryItemData(Item.Id);
	if (Data == nullptr || Item.Amount <= 0)
	{
		UpdateName(FText::GetEmpty());
		UpdateDescription(FText::GetEmpty());
		UpdatePreviewImage(nullptr);
		UpdateAmount(0);
		return;
	}
	
	UpdateName(Data->Name);
	UpdateDescription(Data->Description);
	UpdatePreviewImage(Data->PreviewImage);
	UpdateAmount(Item.Amount);
}

/**
 * @brief Update the highlighted index
 * @param Column The column index of the item that is highlighted
 * @param Row The row index of the item that is highlighted
 */
void UInventoryWidget::UpdateHighlightedIndex(const int Column, const int Row)
{
	HighlightedColumn = Column;
	HighlightedRow = Row;
}

/**
 * @brief Select an inventory item
 * @param Id The ID of the item to select
 */
void UInventoryWidget::SelectItem(const FName Id) const
{
	OnInventoryItemSelected.Broadcast(Id);
}

/**
 * @brief Get the inventory managed by the widget
 * @return The inventory managed by the widget
 */
UInventoryComponent* UInventoryWidget::GetInventory() const
{
	return Inventory;
}

/**
 * @brief Refresh a specific item in the inventory
 * @param Id The ID of the item to refresh
 * @param Amount The amount of the item
 */
void UInventoryWidget::RefreshItem(const FName Id, const int Amount)
{
	for (TArray<UInventoryMenuItem*> InventoryRow : InventoryGrid)
	{
		for (UInventoryMenuItem* InventoryItem : InventoryRow)
		{
			if (InventoryItem->GetInventoryItem().Id == Id)
			{
				InventoryItem->UpdateAmount(Amount);
				if (InventoryItem->IsHighlighted())
				{
					FInventoryItem Item;
					Item.Id = Id;
					Item.Amount = Amount;
					UpdatePreview(Item);
				}

				if (Amount <= 0)
				{
					RefreshInventory();
				}
				
				return;
			}
		}
	}
}

/**
 * @brief Refresh the entire inventory
 */
void UInventoryWidget::RefreshInventory()
{
	TArray<FInventoryItem> InventoryItems = Inventory->GetItems();
	InitializeGrid(InventoryItems.Num());
	const FVector2D GridSize = GetRequiredGridSize(InventoryItems.Num());

	int ItemIndex = -1;	
	for (int Y = 0; Y < GridSize.Y; Y++)
	{
		for (int X = 0; X < GridSize.X; X++)
		{
			ItemIndex++;
			InventoryGrid[X][Y]->UpdateInventoryGridPosition(X, Y);
			
			if (ItemIndex >= InventoryItems.Num())
			{
				InventoryGrid[X][Y]->InitializeEmptyInventoryItem(this);
				continue;
			}
			
			const FInventoryItem InventoryItem = InventoryItems[ItemIndex];
			const FInventoryItemData* Data = GetInventoryItemData(InventoryItem.Id);
			if (Data == nullptr)
			{
				InventoryGrid[X][Y]->InitializeEmptyInventoryItem(this);
				continue;
			}

			InventoryGrid[X][Y]->InitializeInventoryItem(this, InventoryItem, *Data);
		}
	}

	InventoryMenu->RequestHighlight(InventoryGrid[HighlightedColumn][HighlightedRow]);
}

/**
 * @brief Get the data for a specific inventory item
 * @param Id The ID of the inventory item
 * @return The data for the inventory item
 */
FInventoryItemData* UInventoryWidget::GetInventoryItemData(const FName Id) const
{
	return ItemData->FindRow<FInventoryItemData>(Id, TEXT(""), true);
}

/**
 * @brief Update the preview name
 * @param Name The name of the highlighted item
 */
void UInventoryWidget::UpdateName(const FText& Name) const
{
	if (!IsValid(NameText))
	{
		USK_LOG_ERROR("Name text not valid");
		return;
	}

	NameText->SetText(Name);
}

/**
 * @brief Update the preview description
 * @param Description The description of the highlighted item
 */
void UInventoryWidget::UpdateDescription(const FText& Description) const
{
	if (!IsValid(DescriptionText))
	{
		USK_LOG_ERROR("Description text not valid");
		return;
	}

	DescriptionText->SetText(Description);
}

/**
 * @brief Update the preview image
 * @param Image The image of the highlighted item
 */
void UInventoryWidget::UpdatePreviewImage(UTexture2D* Image) const
{
	if (!IsValid(PreviewImage))
	{
		USK_LOG_ERROR("Preview image not valid");
		return;
	}

	PreviewImage->SetBrushFromTexture(Image);
	PreviewImage->SetVisibility(Image == nullptr ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
}

/**
 * @brief Update the preview amount
 * @param Amount The amount of the highlighted item
 */
void UInventoryWidget::UpdateAmount(const int Amount) const
{
	if (!IsValid(AmountText))
	{
		USK_LOG_ERROR("Description text not valid");
		return;
	}

	AmountText->SetText(Amount <= 0 ? FText::GetEmpty() : FText::FromString(FString::FromInt(Amount)));
}

/**
 * @brief Initialize the grid of inventory items
 * @param ItemCount The amount of items included in the grid
 */
void UInventoryWidget::InitializeGrid(const int ItemCount)
{
	if (!IsValid(MenuItemClass))
	{
		USK_LOG_ERROR("No menu item class specified");
		return;
	}

	for (TArray<UInventoryMenuItem*> InventoryRow : InventoryGrid)
	{
		for (UInventoryMenuItem* InventoryItem : InventoryRow)
		{
			InventoryItem->RemoveFromParent();
		}
	}
	
	const FVector2D GridSize = GetRequiredGridSize(ItemCount);
	InventoryGrid.Empty();
	for (int X = 0; X < GridSize.X; X++)
	{
		InventoryGrid.Add(TArray<UInventoryMenuItem*>());
		for (int Y = 0; Y < GridSize.Y; Y++)
		{
			UInventoryMenuItem* NewMenuItem = CreateWidget<UInventoryMenuItem>(GetWorld(), MenuItemClass);
			if (!IsValid(NewMenuItem))
			{
				USK_LOG_ERROR("Failed to create choice menu item widget");
				continue;
			}

			NewMenuItem->HorizontalNavigation = EMenuNavigation::HighlightItem;
			NewMenuItem->VerticalNavigation = EMenuNavigation::HighlightItem;
			
			InventoryGrid[X].Add(NewMenuItem);
			InventoryMenu->AddMenuItem(NewMenuItem);

			UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(NewMenuItem->Slot);
			if (!IsValid(GridSlot))
			{
				USK_LOG_ERROR("Failed to set grid column and row");
				continue;
			}

			GridSlot->SetColumn(X);
			GridSlot->SetRow(Y);
		}
	}

	for (int X = 0; X < GridSize.X; X++)
	{
		for (int Y = 0; Y < GridSize.Y; Y++)
		{
			InventoryGrid[X][Y]->MenuItemLeft = X == 0 ? InventoryGrid[GridSize.X - 1][Y] : InventoryGrid[X - 1][Y];
			InventoryGrid[X][Y]->MenuItemRight = X == GridSize.X - 1 ? InventoryGrid[0][Y] : InventoryGrid[X + 1][Y];
			InventoryGrid[X][Y]->MenuItemUp = Y == 0 ? InventoryGrid[X][GridSize.Y - 1] : InventoryGrid[X][Y - 1];
			InventoryGrid[X][Y]->MenuItemDown = Y == GridSize.Y - 1 ? InventoryGrid[X][0] : InventoryGrid[X][Y + 1];
		}
	}
}

/**
 * @brief Get the required size of the grid
 * @param ItemCount The amount of items included in the grid
 * @return The required size of the grid
 */
FVector2D UInventoryWidget::GetRequiredGridSize(const int ItemCount) const
{
	const int MaxColumns = InventorySize != EInventorySize::FixedRows ? Columns :
		FMath::CeilToInt(static_cast<float>(ItemCount) / static_cast<float>(Rows));
	const int MaxRows = InventorySize != EInventorySize::FixedColumns ? Rows :
		FMath::CeilToInt(static_cast<float>(ItemCount) / static_cast<float>(Columns));
	return FVector2D(MaxColumns, MaxRows);
}