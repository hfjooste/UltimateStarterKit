## Introduction
An item that can be collected by an actor

## Dependencies
The <code>CollectableItem</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
	<li><a href="../audio">Audio</a>: Used to play sound effects either 2D or at a specified location</li>
</ul>

## Collision
The item requires an actor to overlap with the item before it can be collected. Make sure you have some collider on the actor and that the intended collector can overlap with the item/collider

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
		<td>DestroyOnCollected</td>
		<td>Should the item be destroyed after it has been collected</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>AllowedCollector</td>
		<td>The type of actor that can collect the item</td>
		<td>EAllowedCollector</td>
		<td>EAllowedCollector::PossessedPawn</td>
	</tr>
	<tr>
		<td>AllowedCollectorTypes</td>
		<td>The array of actor types that can collect the item</td>
		<td>TArray&lt;TSubclassOf&lt;AActor&gt;&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>CollectedSoundEffects</td>
		<td>An array of sound effects played when collecting the item</td>
		<td>TArray&lt;USoundBase*&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>CollectedParticleFx</td>
		<td>The particle effects spawned when collecting the item</td>
		<td>UNiagaraSystem*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CollectedParticleFxSpawnOffset</td>
		<td>The offset applied to the location of the collected particles when spawning</td>
		<td>FVector</td>
		<td></td>
	</tr>
	<tr>
		<td>bCompleteQuestPointAfterCollecting</td>
		<td>Should the quest point be completed after the item is collected?</td>
		<td>bool</td>
		<td>true</td>
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
		<td>CanCollectItem</td>
		<td>Check if the item can be collected</td>
		<td><strong>Collector (AActor*)</strong><br/>A pointer to the actor that is trying to collect the item</td>
		<td><strong>bool</strong><br/>A boolean value indicating if the item can be collected</td>
	</tr>
	<tr>
		<td>CollectItem</td>
		<td>Collect the item</td>
		<td><strong>Collector (AActor*)</strong><br/>A pointer to the actor that collected the item</td>
		<td></td>
	</tr>
	<tr>
		<td>OnItemCollected</td>
		<td>Called after the item is collected</td>
		<td><strong>Collector (AActor*)</strong><br/>A pointer to the actor that collected the item</td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>CollectableItem</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Item > Can Collect Item</li>
	<li>Ultimate Starter Kit > Item > Collect Item</li>
	<li>Ultimate Starter Kit > Item > On Item Collected</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>CollectableItem</code> can now be used in any of your C++ files:
```c++
#include "USK/Items/CollectableItem.h"

void ATestActor::Test()
{
	// CollectableItem is a pointer to the ACollectableItem
	bool CanCollectItemValue = CollectableItem->CanCollectItem(Collector);
	CollectableItem->CollectItem(Collector);
	CollectableItem->OnItemCollected(Collector);
}
```
