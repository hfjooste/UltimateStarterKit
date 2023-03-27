## Introduction
A component that is used to easily manage/track different types of actor data

## Dependencies
The <code>TrackableDataComponent</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
	<li><a href="../gameinstance">Game Instance</a>: Used to monitor for input device changes and handle saving/loading game data</li>
</ul>

## Data
The data to track is configured by adding items to the <code>Data</code> map. The component should be added to the actor/character containing the data

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
		<td>Data</td>
		<td>The map of data to track</td>
		<td>TMap&lt;FName, FTrackableData&gt;</td>
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
		<td>OnValueZero</td>
		<td>Event used to notify other classes every time the data value reaches 0</td>
		<td><strong>Name (FName)</strong><br/>The name of the data item</td>
	</tr>
	<tr>
		<td>OnValueUpdated</td>
		<td>Event used to notify other classes every time the data value is updated</td>
		<td><strong>Name (FName)</strong><br/>The name of the data item<br/><br/><strong>Value (FName)</strong><br/>The current value of the data item<br/><br/><strong>ValuePercentage (FName)</strong><br/>The percentage of the current value compared to the max value of the data item</td>
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
		<td>GetValue</td>
		<td>Get the amount of the data</td>
		<td><strong>Name (const FName)</strong><br/>The name of the data item</td>
		<td><strong>float</strong><br/>The current amount of the data item</td>
	</tr>
	<tr>
		<td>GetValuePercentage</td>
		<td>Get the value of the data as a percentage of to the max value</td>
		<td><strong>Name (const FName)</strong><br/>The name of the data item</td>
		<td><strong>float</strong><br/>The value of the data as a percentage of to the max value</td>
	</tr>
	<tr>
		<td>Add</td>
		<td>Add an amount to the data</td>
		<td><strong>Name (const FName)</strong><br/>The name of the data item<br/><br/><strong>Amount (const float)</strong><br/>The amount to add</td>
		<td><strong>float</strong><br/>The new amount of the data item</td>
	</tr>
	<tr>
		<td>Remove</td>
		<td>Remove an amount from the data</td>
		<td><strong>Name (const FName)</strong><br/>The name of the data item<br/><br/><strong>Amount (const float)</strong><br/>The amount to remove</td>
		<td><strong>float</strong><br/>The new amount of the data item</td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>TrackableDataComponent</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Trackable Data > Get Value</li>
	<li>Ultimate Starter Kit > Trackable Data > Get Value Percentage</li>
	<li>Ultimate Starter Kit > Trackable Data > Add</li>
	<li>Ultimate Starter Kit > Trackable Data > Remove</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>TrackableDataComponent</code> can now be used in any of your C++ files:
```c++
#include "USK/Data/TrackableDataComponent.h"

void ATestActor::Test()
{
	// TrackableDataComponent is a pointer to the UTrackableDataComponent
	float Value = TrackableDataComponent->GetValue(Name);
	float ValuePercentage = TrackableDataComponent->GetValuePercentage(Name);
	float AddValue = TrackableDataComponent->Add(Name, Amount);
	float RemoveValue = TrackableDataComponent->Remove(Name, Amount);
}
```
