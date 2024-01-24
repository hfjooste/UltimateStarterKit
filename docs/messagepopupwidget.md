## Introduction
The widget used to display a message popup

## Dependencies
The <code>MessagePopupWidget</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Required Widgets
You need to add the following before you can compile the <code>MessagePopupWidget</code> widget:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>TitleText</td>
		<td>The text block used to display the title</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>MessageText</td>
		<td>The text block used to display the message</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>ButtonMenu</td>
		<td>The menu used to display the buttons</td>
		<td>UMenu*</td>
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
		<td>The animation used to show the popup</td>
	</tr>
	<tr>
		<td>HideAnimation</td>
		<td>The animation used to hide the popup</td>
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
		<td>The animation used to show the popup</td>
		<td>UWidgetAnimation*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>HideAnimation</td>
		<td>The animation used to hide the popup</td>
		<td>UWidgetAnimation*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ButtonMenuItemClass</td>
		<td>The button menu item class used when creating the buttons</td>
		<td>TSubclassOf&lt;UMenuItem&gt;</td>
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
		<td>OnShown</td>
		<td>Event used to notify other classes that the popup was shown</td>
		<td></td>
	</tr>
	<tr>
		<td>OnHidden</td>
		<td>Event used to notify other classes that the popup was hidden</td>
		<td></td>
	</tr>
	<tr>
		<td>OnPositiveButtonSelected</td>
		<td>Event used to notify other classes that the positive button was selected</td>
		<td></td>
	</tr>
	<tr>
		<td>OnNegativeButtonSelected</td>
		<td>Event used to notify other classes that the negative button was selected</td>
		<td></td>
	</tr>
	<tr>
		<td>OnNeutralButtonSelected</td>
		<td>Event used to notify other classes that the neutral button was selected</td>
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
		<td>Show</td>
		<td>Show the message popup</td>
		<td><strong>Data (FMessagePopupData)</strong><br/>The data used to display the popup</td>
		<td></td>
	</tr>
	<tr>
		<td>Hide</td>
		<td>Hide the message popup</td>
		<td></td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>MessagePopupWidget</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > UI > Show</li>
	<li>Ultimate Starter Kit > UI > Hide</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>MessagePopupWidget</code> can now be used in any of your C++ files:
```c++
#include "USK/Widgets/MessagePopupWidget.h"

void ATestActor::Test()
{
	// MessagePopupWidget is a pointer to the UMessagePopupWidget
	MessagePopupWidget->Show(Data);
	MessagePopupWidget->Hide();
}
```
