## Introduction
A widget used to display the collection state of an item by showing/hiding an image

## Dependencies
The <code>CollectableItemIcon</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Required Widgets
You need to add the following before you can compile the <code>CollectableItemIcon</code> widget:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>Icon</td>
		<td>The Icon displayed if the item is collected</td>
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
	<tr>
		<td>RequiredValue</td>
		<td>The required value before the item is considered collected</td>
		<td>float</td>
		<td></td>
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
		<td>UpdateState</td>
		<td>Update the collected state (and visibility) of the icon</td>
		<td><strong>IsCollected (bool)</strong><br/>Is the item collected?</td>
		<td></td>
	</tr>
	<tr>
		<td>UpdateValue</td>
		<td>Update the value of the item and adjust the collected state if necessary</td>
		<td><strong>Value (float)</strong><br/>The current value of the item</td>
		<td></td>
	</tr>
	<tr>
		<td>MonitorTrackableValue</td>
		<td>Monitor the trackable data and automatically update the icon state whenever the value changes</td>
		<td><strong>TrackableDataComponent (UTrackableDataComponent*)</strong><br/>A reference to the TrackableDataComponent<br/><br/><strong>DataName (FName)</strong><br/>The name of the data item to monitor</td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>CollectableItemIcon</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > UI > Update State</li>
	<li>Ultimate Starter Kit > UI > Update Value</li>
	<li>Ultimate Starter Kit > UI > Monitor Trackable Value</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>CollectableItemIcon</code> can now be used in any of your C++ files:
```c++
#include "USK/Widgets/CollectableItemIcon.h"

void ATestActor::Test()
{
	// CollectableItemIcon is a pointer to the UCollectableItemIcon
	CollectableItemIcon->UpdateState(IsCollected);
	CollectableItemIcon->UpdateValue(Value);
	CollectableItemIcon->MonitorTrackableValue(TrackableDataComponent, DataName);
}
```
