## Introduction
The widget displayed for the current quest point

## Dependencies
The <code>QuestWidget</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Required Widgets
You need to add the following before you can compile the <code>QuestWidget</code> widget:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>QuestTitleText</td>
		<td>The text block used to quest title</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>QuestDetailsText</td>
		<td>The text block used to quest details</td>
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
		<td>The animation played when the widget is shown</td>
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
		<td>The animation played when the widget is shown</td>
		<td>UWidgetAnimation*</td>
		<td><code>nullptr</code></td>
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
		<td>Show</td>
		<td>Show the quest widget</td>
		<td><strong>Quest (UQuest*)</strong><br/>The current quest<br/><br/><strong>Point (int)</strong><br/>The current quest point</td>
		<td></td>
	</tr>
	<tr>
		<td>Hide</td>
		<td>Hide the quest widget</td>
		<td></td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>QuestWidget</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > UI > Show</li>
	<li>Ultimate Starter Kit > UI > Hide</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>QuestWidget</code> can now be used in any of your C++ files:
```c++
#include "USK/Widgets/QuestWidget.h"

void ATestActor::Test()
{
	// QuestWidget is a pointer to the UQuestWidget
	QuestWidget->Show(Quest, Point);
	QuestWidget->Hide();
}
```
