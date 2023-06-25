## Introduction
The widget responsible for displaying the inventory

## Dependencies
The <code>InventoryWidget</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Required Widgets
You need to add the following before you can compile the <code>InventoryWidget</code> widget:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>InventoryMenu</td>
		<td>The menu responsible for controlling all the menu items</td>
		<td>UMenu*</td>
	</tr>
</table>

## Optional Widgets
You can add the following widgets to enable extra functionality:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>NameText</td>
		<td>The widget responsible for displaying the highlighted item's name</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>DescriptionText</td>
		<td>The widget responsible for displaying the highlighted item's description</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>PreviewImage</td>
		<td>The widget responsible for displaying the highlighted item's image</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>AmountText</td>
		<td>The widget responsible for displaying the highlighted item's amount</td>
		<td>UTextBlock*</td>
	</tr>
</table>

## API Reference
### Properties
<table>
	<tr>
		<th>Property</th>
		<th>Description</th>
		<th>Type</th>
		<th>Default Value</th>
	</tr>
	<tr>
		<td>MenuItemClass</td>
		<td>The inventory menu item class used to display the inventory items</td>
		<td>TSubclassOf&lt;UInventoryMenuItem&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>ItemData</td>
		<td>The data table containing all the information about the inventory items</td>
		<td>UDataTable*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>InventorySize</td>
		<td>The size restrictions of the inventory</td>
		<td>EInventorySize</td>
		<td></td>
	</tr>
	<tr>
		<td>Rows</td>
		<td>The amount of rows in the inventory</td>
		<td>int</td>
		<td></td>
	</tr>
	<tr>
		<td>Columns</td>
		<td>The amount of columns in the inventory</td>
		<td>int</td>
		<td></td>
	</tr>
</table>

### Events
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Params</th>
	</tr>
	<tr>
		<td>OnInventoryItemSelected</td>
		<td>Event used to notify other classes every time an inventory item is selected</td>
		<td><strong>Name (FName)</strong><br/>The ID of the selected inventory item</td>
	</tr>
</table>

### Functions
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Params</th>
		<th>Return</th>
	</tr>
	<tr>
		<td>LoadInventory</td>
		<td>Load a specific inventory</td>
		<td><strong>InventoryComponent (UInventoryComponent*)</strong><br/>The inventory to load</td>
		<td></td>
	</tr>
	<tr>
		<td>UpdatePreview</td>
		<td>Update the preview of the inventory</td>
		<td><strong>Item (FInventoryItem)</strong><br/>The item to preview</td>
		<td></td>
	</tr>
	<tr>
		<td>UpdateHighlightedIndex</td>
		<td>Update the highlighted index</td>
		<td><strong>Column (int)</strong><br/>The column index of the item that is highlighted<br/><br/><strong>Row (int)</strong><br/>The row index of the item that is highlighted</td>
		<td></td>
	</tr>
	<tr>
		<td>SelectItem</td>
		<td>Select an inventory item</td>
		<td><strong>Id (FName)</strong><br/>The ID of the item to select</td>
		<td></td>
	</tr>
	<tr>
		<td>GetInventory</td>
		<td>Get the inventory managed by the widget</td>
		<td></td>
		<td><strong>UInventoryComponent*</strong><br/>The inventory managed by the widget</td>
	</tr>
	<tr>
		<td>RefreshItem</td>
		<td>Refresh a specific item in the inventory</td>
		<td><strong>Id (FName)</strong><br/>The ID of the item to refresh<br/><br/><strong>Amount (int)</strong><br/>The amount of the item</td>
		<td></td>
	</tr>
	<tr>
		<td>RefreshInventory</td>
		<td>Refresh the entire inventory</td>
		<td></td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>InventoryWidget</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Inventory > Load Inventory</li>
	<li>Ultimate Starter Kit > Inventory > Update Preview</li>
	<li>Ultimate Starter Kit > Inventory > Update Highlighted Index</li>
	<li>Ultimate Starter Kit > Inventory > Select Item</li>
	<li>Ultimate Starter Kit > Inventory > Get Inventory</li>
	<li>Ultimate Starter Kit > Inventory > Refresh Item</li>
	<li>Ultimate Starter Kit > Inventory > Refresh Inventory</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>InventoryWidget</code> can now be used in any of your C++ files:
```c++
#include "USK/Inventory/InventoryWidget.h"

void ATestActor::Test()
{
	// InventoryWidget is a pointer to the UInventoryWidget
	InventoryWidget->LoadInventory(InventoryComponent);
	InventoryWidget->UpdatePreview(Item);
	InventoryWidget->UpdateHighlightedIndex(Column, Row);
	InventoryWidget->SelectItem(Id);
	UInventoryComponent* Inventory = InventoryWidget->GetInventory();
	InventoryWidget->RefreshItem(Id, Amount);
	InventoryWidget->RefreshInventory();
}
```
