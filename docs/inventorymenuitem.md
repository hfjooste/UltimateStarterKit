## Introduction
The menu item used to display an inventory item

## Dependencies
The <code>InventoryMenuItem</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Optional Widgets
You can add the following widgets to enable extra functionality:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>InventoryImage</td>
		<td>The image of the inventory item</td>
		<td>UImage*</td>
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
		<td>InitializeEmptyInventoryItem</td>
		<td>Initialize an empty inventory item</td>
		<td><strong>Widget (UInventoryWidget*)</strong><br/>The widget that owns this menu item</td>
		<td></td>
	</tr>
	<tr>
		<td>InitializeInventoryItem</td>
		<td>Initialize a non-empty inventory item</td>
		<td><strong>Widget (UInventoryWidget*)</strong><br/>The widget that owns this menu item<br/><br/><strong>Item (FInventoryItem)</strong><br/>The item tracked by this menu item<br/><br/><strong>Data (FInventoryItemData)</strong><br/>The data for this menu item</td>
		<td></td>
	</tr>
	<tr>
		<td>UpdateInventoryGridPosition</td>
		<td>Update the grid position of the inventory menu item</td>
		<td><strong>CurrentColumn (int)</strong><br/>The current column of the inventory menu item<br/><br/><strong>CurrentRow (int)</strong><br/>The current row of the inventory menu item</td>
		<td></td>
	</tr>
	<tr>
		<td>GetInventoryItem</td>
		<td>Get the inventory item tracked by this menu item</td>
		<td></td>
		<td><strong>FInventoryItem</strong><br/>The inventory item tracked by this menu item</td>
	</tr>
	<tr>
		<td>UpdateAmount</td>
		<td>Update the amount of the inventory item</td>
		<td><strong>Amount (int)</strong><br/>The new amount of the inventory item</td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>InventoryMenuItem</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Inventory > Initialize Empty Inventory Item</li>
	<li>Ultimate Starter Kit > Inventory > Initialize Inventory Item</li>
	<li>Ultimate Starter Kit > Inventory > Update Inventory Grid Position</li>
	<li>Ultimate Starter Kit > Inventory > Get Inventory Item</li>
	<li>Ultimate Starter Kit > Inventory > Update Amount</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>InventoryMenuItem</code> can now be used in any of your C++ files:
```c++
#include "USK/Inventory/InventoryMenuItem.h"

void ATestActor::Test()
{
	// InventoryMenuItem is a pointer to the UInventoryMenuItem
	InventoryMenuItem->InitializeEmptyInventoryItem(Widget);
	InventoryMenuItem->InitializeInventoryItem(Widget, Item, Data);
	InventoryMenuItem->UpdateInventoryGridPosition(CurrentColumn, CurrentRow);
	FInventoryItem InventoryItem = InventoryMenuItem->GetInventoryItem();
	InventoryMenuItem->UpdateAmount(Amount);
}
```
