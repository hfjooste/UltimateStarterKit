## Introduction
Actor component responsible for tracking data in an inventory

## Dependencies
The <code>InventoryComponent</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
	<li><a href="../gameinstance">Game Instance</a>: Used to monitor for input device changes and handle saving/loading game data</li>
</ul>

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
		<td>InventoryId</td>
		<td>The ID of the inventory used when saving/loading the data</td>
		<td>FName</td>
		<td></td>
	</tr>
	<tr>
		<td>AutoSave</td>
		<td>Should the data in the inventory automatically be saved/loaded</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>EnforceMaxAmount</td>
		<td>Should a maximum amount be enforced for each item?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>MaxAmount</td>
		<td>The maximum amount of each item</td>
		<td>int</td>
		<td>99</td>
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
		<td>OnInventoryItemUpdated</td>
		<td>Event used to notify other classes every time an item in the inventory was updated</td>
		<td><strong>Id (FName)</strong><br/>The ID of the item that was updated<br/><br/><strong>Amount (FName)</strong><br/>The new amount of the item</td>
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
		<td>GetItems</td>
		<td>Get all the item currently in the inventory</td>
		<td></td>
		<td><strong>TArray&lt;FInventoryItem&gt;</strong><br/>An array of all the items in the inventory</td>
	</tr>
	<tr>
		<td>AddItem</td>
		<td>Add an item to the inventory</td>
		<td><strong>Id (FName)</strong><br/>The ID of the item to add<br/><br/><strong>Amount (int)</strong><br/>The amount to add</td>
		<td></td>
	</tr>
	<tr>
		<td>RemoveItem</td>
		<td>Remove an item from the inventory</td>
		<td><strong>Id (FName)</strong><br/>The ID of the item to remove<br/><br/><strong>Amount (int)</strong><br/>The amount to remove</td>
		<td></td>
	</tr>
	<tr>
		<td>RemoveAll</td>
		<td>Remove all the items with the specified ID</td>
		<td><strong>Id (FName)</strong><br/>The ID of the item to remove</td>
		<td></td>
	</tr>
	<tr>
		<td>Clear</td>
		<td>Remove all items from the inventory</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>LoadInventory</td>
		<td>Load the inventory data</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>SaveInventory</td>
		<td>Save the inventory data</td>
		<td></td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>InventoryComponent</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Inventory > Get Items</li>
	<li>Ultimate Starter Kit > Inventory > Add Item</li>
	<li>Ultimate Starter Kit > Inventory > Remove Item</li>
	<li>Ultimate Starter Kit > Inventory > Remove All</li>
	<li>Ultimate Starter Kit > Inventory > Clear</li>
	<li>Ultimate Starter Kit > Inventory > Load Inventory</li>
	<li>Ultimate Starter Kit > Inventory > Save Inventory</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>InventoryComponent</code> can now be used in any of your C++ files:
```c++
#include "USK/Inventory/InventoryComponent.h"

void ATestActor::Test()
{
	// InventoryComponent is a pointer to the UInventoryComponent
	TArray<FInventoryItem> Items = InventoryComponent->GetItems();
	InventoryComponent->AddItem(Id, Amount);
	InventoryComponent->RemoveItem(Id, Amount);
	InventoryComponent->RemoveAll(Id);
	InventoryComponent->Clear();
	InventoryComponent->LoadInventory();
	InventoryComponent->SaveInventory();
}
```
