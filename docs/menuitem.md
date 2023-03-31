## Introduction
A widget used to display a title, text and value in the form of a menu item

## Dependencies
The <code>MenuItem</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
	<li><a href="../audio">Audio</a>: Used to play sound effects either 2D or at a specified location</li>
</ul>

## Required Widgets
You need to add the following before you can compile the <code>MenuItem</code> widget:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>NormalText</td>
		<td>The TextBlock used to display the text of the menu item while not highlighted</td>
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
		<td>The TextBlock used to display the title of the menu item</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>HighlightedText</td>
		<td>The TextBlock used to display the text of the menu item while highlighted</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>BorderLeft</td>
		<td>The border displayed on the left of the menu item</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>BorderRight</td>
		<td>The border displayed on the right of the menu item</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>BorderBackground</td>
		<td>The background border display in the menu item</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>ButtonLeft</td>
		<td>The button displayed on the left of the menu item</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>ButtonRight</td>
		<td>The button displayed on the right of the menu item</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>ButtonBackground</td>
		<td>The background button display in the menu item</td>
		<td>UImage*</td>
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
		<td>HighlightedAnimation</td>
		<td>The animation played when the menu item is highlighted</td>
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
		<td>HighlightedAnimation</td>
		<td>The animation played when the menu item is highlighted</td>
		<td>UWidgetAnimation*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>FocusByDefault</td>
		<td>Should the menu item be focused by default?</td>
		<td>bool</td>
		<td></td>
	</tr>
	<tr>
		<td>HideOnConsoles</td>
		<td>Should the menu item be hidden on consoles?</td>
		<td>bool</td>
		<td></td>
	</tr>
	<tr>
		<td>TitleText</td>
		<td>The title text displayed in the menu item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>MenuItemText</td>
		<td>The text displayed in the menu item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>HighlightedSFX</td>
		<td>The sound effect played when the menu item is highlighted</td>
		<td>USoundBase*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>BorderNormalColor</td>
		<td>The color of the border when not highlighted</td>
		<td>FLinearColor</td>
		<td></td>
	</tr>
	<tr>
		<td>BorderHighlightedColor</td>
		<td>The color of the border when highlighted</td>
		<td>FLinearColor</td>
		<td></td>
	</tr>
	<tr>
		<td>BorderNormalImage</td>
		<td>The image of the border when not highlighted</td>
		<td>UTexture2D*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>BorderHighlightedImage</td>
		<td>The image of the border when highlighted</td>
		<td>UTexture2D*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>BorderLeftNormalImage</td>
		<td>The image of the left border when not highlighted</td>
		<td>UTexture2D*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>BorderLeftHighlightedImage</td>
		<td>The image of the left border when highlighted</td>
		<td>UTexture2D*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>BorderRightNormalImage</td>
		<td>The image of the right border when not highlighted</td>
		<td>UTexture2D*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>BorderRightHighlightedImage</td>
		<td>The image of the right border when highlighted</td>
		<td>UTexture2D*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>BackgroundNormalColor</td>
		<td>The color of the button when not highlighted</td>
		<td>FLinearColor</td>
		<td></td>
	</tr>
	<tr>
		<td>BackgroundHighlightedColor</td>
		<td>The color of the button when highlighted</td>
		<td>FLinearColor</td>
		<td></td>
	</tr>
	<tr>
		<td>BackgroundNormalImage</td>
		<td>The image of the button when not highlighted</td>
		<td>UTexture2D*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>BackgroundHighlightedImage</td>
		<td>The image of the button when highlighted</td>
		<td>UTexture2D*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>BackgroundLeftNormalImage</td>
		<td>The image of the left button when not highlighted</td>
		<td>UTexture2D*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>BackgroundLeftHighlightedImage</td>
		<td>The image of the left button when highlighted</td>
		<td>UTexture2D*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>BackgroundRightNormalImage</td>
		<td>The image of the right button when not highlighted</td>
		<td>UTexture2D*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>BackgroundRightHighlightedImage</td>
		<td>The image of the right button when highlighted</td>
		<td>UTexture2D*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>DefaultValue</td>
		<td>The default value of the menu item</td>
		<td>int</td>
		<td>100</td>
	</tr>
	<tr>
		<td>MinValue</td>
		<td>The minimum value of the menu item</td>
		<td>int</td>
		<td>0</td>
	</tr>
	<tr>
		<td>MaxValue</td>
		<td>The maximum value of the menu item</td>
		<td>int</td>
		<td>100</td>
	</tr>
	<tr>
		<td>VerticalNavigation</td>
		<td>The type of navigation used by the menu item when pressing the up or down key</td>
		<td>EMenuNavigation</td>
		<td>EMenuNavigation::HighlightItem</td>
	</tr>
	<tr>
		<td>MenuItemUp</td>
		<td>The menu item highlighted when the up key is pressed</td>
		<td>UMenuItem*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>MenuItemDown</td>
		<td>The menu item highlighted when the down key is pressed</td>
		<td>UMenuItem*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>HorizontalNavigation</td>
		<td>The type of navigation used by the menu item when pressing the left or right key</td>
		<td>EMenuNavigation</td>
		<td>EMenuNavigation::HighlightItem</td>
	</tr>
	<tr>
		<td>MenuItemLeft</td>
		<td>The menu item highlighted when the left key is pressed</td>
		<td>UMenuItem*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>MenuItemRight</td>
		<td>The menu item highlighted when the right key is pressed</td>
		<td>UMenuItem*</td>
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
		<td>OnSelectedEvent</td>
		<td>Event used to notify other classes that the menu item was selected</td>
		<td></td>
	</tr>
	<tr>
		<td>OnValueChanged</td>
		<td>Event used to notify other classes that the menu item's value was updated</td>
		<td><strong>Value (int)</strong><br/>The new value of the menu item</td>
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
		<td>SetText</td>
		<td>Set the text display in the menu item</td>
		<td><strong>Text (FText)</strong><br/>The new text displayed in the menu item</td>
		<td></td>
	</tr>
	<tr>
		<td>SetHighlightedState</td>
		<td>Set the highlighted state of the menu item</td>
		<td><strong>IsHighlighted (bool)</strong><br/>Is the menu item highlighted?<br/><br/><strong>PlayHighlightedSound (bool)</strong><br/>Should the highlighted sound effect be played?</td>
		<td></td>
	</tr>
	<tr>
		<td>GetValue</td>
		<td>Get the current value of the menu item</td>
		<td></td>
		<td><strong>int</strong><br/>The current value of the menu item</td>
	</tr>
	<tr>
		<td>UpdateValue</td>
		<td>Update the value of the menu item</td>
		<td><strong>IncreaseValue (bool)</strong><br/>Should the value be increased?</td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>MenuItem</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > UI > Set Text</li>
	<li>Ultimate Starter Kit > UI > Set Highlighted State</li>
	<li>Ultimate Starter Kit > UI > Get Value</li>
	<li>Ultimate Starter Kit > UI > Update Value</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>MenuItem</code> can now be used in any of your C++ files:
```c++
#include "USK/Widgets/MenuItem.h"

void ATestActor::Test()
{
	// MenuItem is a pointer to the UMenuItem
	MenuItem->SetText(Text);
	MenuItem->SetHighlightedState(IsHighlighted, PlayHighlightedSound);
	int Value = MenuItem->GetValue();
	MenuItem->UpdateValue(IncreaseValue);
}
```
