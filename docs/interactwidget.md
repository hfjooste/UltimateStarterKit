## Introduction
The widget displayed when the player can interact with an object

## Dependencies
The <code>InteractWidget</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Required Widgets
You need to add the following before you can compile the <code>InteractWidget</code> widget:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>BeforeTextBlock</td>
		<td>The text block used to display the text before the input indicator</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>AfterTextBlock</td>
		<td>The text block used to display the text after the input indicator</td>
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
		<td>Show the interact widget</td>
		<td><strong>BeforeText (FText)</strong><br/>The text displayed before the input indicator<br/><br/><strong>AfterText (FText)</strong><br/>The text displayed after the input indicator</td>
		<td></td>
	</tr>
	<tr>
		<td>Hide</td>
		<td>Hide the interact widget</td>
		<td></td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>InteractWidget</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > UI > Show</li>
	<li>Ultimate Starter Kit > UI > Hide</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>InteractWidget</code> can now be used in any of your C++ files:
```c++
#include "USK/Widgets/InteractWidget.h"

void ATestActor::Test()
{
	// InteractWidget is a pointer to the UInteractWidget
	InteractWidget->Show(BeforeText, AfterText);
	InteractWidget->Hide();
}
```
