// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemData.h"
#include "InventoryMenuItem.h"
#include "InventorySize.h"
#include "Math/Vector2D.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UInventoryComponent;
struct FInventoryItem;

/**
 * @brief The widget responsible for displaying the inventory
 */
UCLASS()
class USK_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	/**
	 * @brief Event used to notify other classes every time an inventory item is selected
	 * @param Name The ID of the selected inventory item
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryItemSelected, FName, Id);
	
public:
	/**
	 * @brief The widget responsible for displaying the highlighted item's name
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UTextBlock* NameText;

	/**
	 * @brief The widget responsible for displaying the highlighted item's description
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UTextBlock* DescriptionText;

	/**
	 * @brief The widget responsible for displaying the highlighted item's image
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* PreviewImage;

	/**
	 * @brief The widget responsible for displaying the highlighted item's amount
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UTextBlock* AmountText;

	/**
	 * @brief The menu responsible for controlling all the menu items
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UMenu* InventoryMenu;

	/**
	 * @brief The inventory menu item class used to display the inventory items
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Inventory")
	TSubclassOf<UInventoryMenuItem> MenuItemClass;

	/**
	 * @brief The data table containing all the information about the inventory items
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Inventory")
	UDataTable* ItemData;

	/**
	 * @brief The size restrictions of the inventory
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Inventory")
	EInventorySize InventorySize;

	/**
	 * @brief The amount of rows in the inventory
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Inventory",
		meta=(EditCondition = "InventorySize != EInventorySize::FixedColumns", EditConditionHides))
	int Rows;

	/**
	 * @brief The amount of columns in the inventory
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Inventory",
		meta=(EditCondition = "InventorySize != EInventorySize::FixedRows", EditConditionHides))
	int Columns;

	/**
	 * @brief Event used to notify other classes every time an inventory item is selected
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Inventory|Events")
	FInventoryItemSelected OnInventoryItemSelected;

	/**
	 * @brief Load a specific inventory
	 * @param InventoryComponent The inventory to load
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Inventory")
	void LoadInventory(UInventoryComponent* InventoryComponent);

	/**
	 * @brief Update the preview of the inventory
	 * @param Item The item to preview
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Inventory")
	void UpdatePreview(const FInventoryItem Item) const;

	/**
	 * @brief Update the highlighted index
	 * @param Column The column index of the item that is highlighted
	 * @param Row The row index of the item that is highlighted
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Inventory")
	void UpdateHighlightedIndex(int Column, int Row);

	/**
	 * @brief Select an inventory item
	 * @param Id The ID of the item to select
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Inventory")
	void SelectItem(FName Id) const;

	/**
	 * @brief Get the inventory managed by the widget
	 * @return The inventory managed by the widget
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Inventory")
	UInventoryComponent* GetInventory() const;

	/**
	 * @brief Refresh a specific item in the inventory
	 * @param Id The ID of the item to refresh
	 * @param Amount The amount of the item
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Inventory")
	void RefreshItem(FName Id, int Amount);

	/**
	 * @brief Refresh the entire inventory
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Inventory")
	void RefreshInventory();

private:
	/**
	 * @brief A reference to the inventory managed by the widget
	 */
	UPROPERTY()
	UInventoryComponent* Inventory;

	/**
	 * @brief The grid of inventory items
	 */
	TArray<TArray<UInventoryMenuItem*>> InventoryGrid;

	/**
	 * @brief Get the data for a specific inventory item
	 * @param Id The ID of the inventory item
	 * @return The data for the inventory item
	 */
	FInventoryItemData* GetInventoryItemData(const FName Id) const;

	/**
	 * @brief The column index of the item that is highlighted
	 */
	int HighlightedColumn;

	/**
	 * @brief The row index of the item that is highlighted
	 */
	int HighlightedRow;

	/**
	 * @brief Update the preview name
	 * @param Name The name of the highlighted item
	 */
	void UpdateName(const FText& Name) const;

	/**
	 * @brief Update the preview description
	 * @param Description The description of the highlighted item
	 */
	void UpdateDescription(const FText& Description) const;

	/**
	 * @brief Update the preview image
	 * @param Image The image of the highlighted item
	 */
	void UpdatePreviewImage(UTexture2D* Image) const;

	/**
	 * @brief Update the preview amount
	 * @param Amount The amount of the highlighted item
	 */
	void UpdateAmount(int Amount) const;

	/**
	 * @brief Initialize the grid of inventory items
	 * @param ItemCount The amount of items included in the grid
	 */
	void InitializeGrid(int ItemCount);

	/**
	 * @brief Get the required size of the grid
	 * @param ItemCount The amount of items included in the grid
	 * @return The required size of the grid
	 */
	FVector2D GetRequiredGridSize(int ItemCount) const;
};
