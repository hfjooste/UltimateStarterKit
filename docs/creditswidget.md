## Introduction
Widget used to display multiple animated credits entries using different alignment options and durations

## Dependencies
The <code>CreditsWidget</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Required Widgets
You need to add the following before you can compile the <code>CreditsWidget</code> widget:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>Root</td>
		<td>The root container of the widget</td>
		<td>UPanelWidget*</td>
	</tr>
	<tr>
		<td>Container</td>
		<td>The container used to display the credits entries</td>
		<td>UPanelWidget*</td>
	</tr>
	<tr>
		<td>Text</td>
		<td>The text block used to display the text of the credits entry</td>
		<td>UTextBlock*</td>
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
		<td>Title</td>
		<td>The text block used to display the title of the credits entry</td>
		<td>UTextBlock*</td>
	</tr>
</table>

## Optional Animations
You can add the following widgets to enable extra functionality:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
	</tr>
	<tr>
		<td>ShowAnimation</td>
		<td>The animation played each time a new entry is shown</td>
	</tr>
	<tr>
		<td>HideAnimation</td>
		<td>The animation played at the end of each entry</td>
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
		<td>ShowAnimation</td>
		<td>The animation played each time a new entry is shown</td>
		<td>UWidgetAnimation*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>HideAnimation</td>
		<td>The animation played at the end of each entry</td>
		<td>UWidgetAnimation*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>AutoStart</td>
		<td>Should the credits automatically be started when the widget is constructed?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>RemoveOnCompletion</td>
		<td>Should the widget automatically be removed from the viewport when the credits are finished?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>StartDelay</td>
		<td>The delay in seconds before the first credits entry is shown after starting</td>
		<td>float</td>
		<td>1.0f</td>
	</tr>
	<tr>
		<td>DelayBetweenEntries</td>
		<td>The delay in seconds between the previous hide animation and the next show animation</td>
		<td>float</td>
		<td>3.0f</td>
	</tr>
	<tr>
		<td>Credits</td>
		<td>The array of credits entries to be displayed</td>
		<td>TArray&lt;FCreditsEntry&gt;</td>
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
		<td>OnCreditsFinished</td>
		<td>Event used to notify other classes when the credits are finished</td>
		<td></td>
	</tr>
	<tr>
		<td>OnCreditsNextEntryStarted</td>
		<td>Event used to notify other classes every time a next entry is started</td>
		<td><strong>Name (int)</strong><br/>The index of the entry that was started</td>
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
		<td>Start</td>
		<td>Start showing the credits</td>
		<td></td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>CreditsWidget</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > UI > Start</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>CreditsWidget</code> can now be used in any of your C++ files:
```c++
#include "USK/Widgets/CreditsWidget.h"

void ATestActor::Test()
{
	// CreditsWidget is a pointer to the UCreditsWidget
	CreditsWidget->Start();
}
```
