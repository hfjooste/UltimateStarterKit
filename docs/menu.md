## Introduction
A widget used to display menu items and handle navigation between the items

## Dependencies
The <code>Menu</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
	<li><a href="../gameinstance">Game Instance</a>: Used to monitor for input device changes and handle saving/loading game data</li>
	<li><a href="../audio">Audio</a>: Used to play sound effects either 2D or at a specified location</li>
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
		<td>ScrollContainer</td>
		<td>Scroll container used for large menus with many items</td>
		<td>UScrollBox*</td>
	</tr>
	<tr>
		<td>Container</td>
		<td>The container used to display the menu items</td>
		<td>UPanelWidget*</td>
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
		<td>AddInputBindingOnLoad</td>
		<td>Should the input binding automatically be added as soon as the widget is loaded?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>PauseGameWhileVisible</td>
		<td>Should the game automatically be paused/resumed based on the visibility of the menu?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>DisableWhilePaused</td>
		<td>Should the menu be disabled while the game is paused?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>SelectedSFX</td>
		<td>The sound effect played when a menu item is selected</td>
		<td>USoundBase*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>BackSFX</td>
		<td>The sound effect played when trying to go back to a previous menu or closing the menu through the back button</td>
		<td>USoundBase*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>InputMappingContext</td>
		<td>The input mapping context used to navigate the menu</td>
		<td>UInputMappingContext*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>MenuUpInputAction</td>
		<td>The input action used to navigate up</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>MenuDownInputAction</td>
		<td>The input action used to navigate down</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>MenuLeftInputAction</td>
		<td>The input action used to navigate left</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>MenuRightInputAction</td>
		<td>The input action used to navigate right</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>MenuSelectInputAction</td>
		<td>The input action used to select a menu item</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>MenuBackInputAction</td>
		<td>The input action used to go back to a previous menu or close the menu</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
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
		<td>OnBackEvent</td>
		<td>Event used to handle the back/close action of the menu</td>
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
		<td>OnMenuUp</td>
		<td>Navigate up or increase the value</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>OnMenuUpHold</td>
		<td>Increase the value while holding the menu up key</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>OnMenuDown</td>
		<td>Navigate down or decrease the value</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>OnMenuDownHold</td>
		<td>Decrease the value while holding the menu down key</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>OnMenuLeft</td>
		<td>Navigate left or decrease the value</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>OnMenuLeftHold</td>
		<td>Decrease the value while holding the menu left key</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>OnMenuRight</td>
		<td>Navigate right or increase the value</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>OnMenuRightHold</td>
		<td>Increase the value while holding the menu right key</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>OnMenuSelected</td>
		<td>Select the current menu item</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>OnMenuBack</td>
		<td>Go back to a previous menu or close the menu</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>RequestHighlight</td>
		<td>Request to highlight a specific menu item</td>
		<td><strong>MenuItem (UMenuItem*)</strong><br/>The menu item to highlight</td>
		<td></td>
	</tr>
	<tr>
		<td>RemoveHighlight</td>
		<td>Request to remove the highlighted state from a specific menu item</td>
		<td><strong>MenuItem (UMenuItem*)</strong><br/>The menu item to remove the highlighted state from</td>
		<td></td>
	</tr>
	<tr>
		<td>AddMenuItem</td>
		<td>Add a menu item to the container</td>
		<td><strong>MenuItem (UMenuItem*)</strong><br/>The menu item to add</td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>Menu</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > UI > On Menu Up</li>
	<li>Ultimate Starter Kit > UI > On Menu Up Hold</li>
	<li>Ultimate Starter Kit > UI > On Menu Down</li>
	<li>Ultimate Starter Kit > UI > On Menu Down Hold</li>
	<li>Ultimate Starter Kit > UI > On Menu Left</li>
	<li>Ultimate Starter Kit > UI > On Menu Left Hold</li>
	<li>Ultimate Starter Kit > UI > On Menu Right</li>
	<li>Ultimate Starter Kit > UI > On Menu Right Hold</li>
	<li>Ultimate Starter Kit > UI > On Menu Selected</li>
	<li>Ultimate Starter Kit > UI > On Menu Back</li>
	<li>Ultimate Starter Kit > UI > Request Highlight</li>
	<li>Ultimate Starter Kit > UI > Remove Highlight</li>
	<li>Ultimate Starter Kit > UI > Add Menu Item</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>Menu</code> can now be used in any of your C++ files:
```c++
#include "USK/Widgets/Menu.h"

void ATestActor::Test()
{
	// Menu is a pointer to the UMenu
	Menu->OnMenuUp();
	Menu->OnMenuUpHold();
	Menu->OnMenuDown();
	Menu->OnMenuDownHold();
	Menu->OnMenuLeft();
	Menu->OnMenuLeftHold();
	Menu->OnMenuRight();
	Menu->OnMenuRightHold();
	Menu->OnMenuSelected();
	Menu->OnMenuBack();
	Menu->RequestHighlight(MenuItem);
	Menu->RemoveHighlight(MenuItem);
	Menu->AddMenuItem(MenuItem);
}
```
