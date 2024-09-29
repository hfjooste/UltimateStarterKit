## Introduction
A widget used to display a title, text and value in the form of a menu item

## Dependencies
The <code>MenuItem</code> relies on other components of this plugin to work:
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
		<td>Title</td>
		<td>The TextBlock used to display the title of the menu item while not highlighted</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>HighlightedTitle</td>
		<td>The TextBlock used to display the title of the menu item while highlighted</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>NormalText</td>
		<td>The TextBlock used to display the text of the menu item while not highlighted</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>HighlightedText</td>
		<td>The TextBlock used to display the text of the menu item while highlighted</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>ValueText</td>
		<td>The TextBlock used to display the current value of the menu item</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>HighlightedValueText</td>
		<td>The TextBlock used to display the current value of the menu item while highlighted</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>SelectButton</td>
		<td>The button used to select the menu item</td>
		<td>UButton*</td>
	</tr>
	<tr>
		<td>ValueSlider</td>
		<td>The slider used to display and update the current value of the menu item</td>
		<td>USlider*</td>
	</tr>
	<tr>
		<td>IncreaseValueButton</td>
		<td>The button used to increase the value of the menu item</td>
		<td>UButton*</td>
	</tr>
	<tr>
		<td>IncreaseValueButtonNormalImage</td>
		<td>The image displayed in the increase value button while not highlighted</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>IncreaseValueButtonHighlightedImage</td>
		<td>The image displayed in the increase value button while highlighted</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>DecreaseValueButton</td>
		<td>The button used to decrease the value of the menu item</td>
		<td>UButton*</td>
	</tr>
	<tr>
		<td>DecreaseValueButtonNormalImage</td>
		<td>The image displayed in the decrease value button while not highlighted</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>DecreaseValueButtonHighlightedImage</td>
		<td>The image displayed in the decrease value button while highlighted</td>
		<td>UImage*</td>
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
	<tr>
		<td>InputIndicator</td>
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
		<td>false</td>
	</tr>
	<tr>
		<td>HideOnConsoles</td>
		<td>Should the menu item be hidden on consoles?</td>
		<td>bool</td>
		<td>false</td>
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
		<td>SliderBarNormalColor</td>
		<td>The color of the slider bar when not highlighted</td>
		<td>FLinearColor</td>
		<td></td>
	</tr>
	<tr>
		<td>SliderBarHighlightedColor</td>
		<td>The color of the slider bar when highlighted</td>
		<td>FLinearColor</td>
		<td></td>
	</tr>
	<tr>
		<td>SliderThumbNormalColor</td>
		<td>The color of the slider thumb when not highlighted</td>
		<td>FLinearColor</td>
		<td></td>
	</tr>
	<tr>
		<td>SliderThumbHighlightedColor</td>
		<td>The color of the slider thumb when highlighted</td>
		<td>FLinearColor</td>
		<td></td>
	</tr>
	<tr>
		<td>ValueUpdateMethod</td>
		<td>The method used to update the value of the menu item</td>
		<td>EMenuItemValueUpdateMethod</td>
		<td>EMenuItemValueUpdateMethod::SinglePress</td>
	</tr>
	<tr>
		<td>IncrementSinglePress</td>
		<td>The increment used when updating the value when the key is pressed</td>
		<td>float</td>
		<td>1.0f</td>
	</tr>
	<tr>
		<td>IncrementHold</td>
		<td>The increment used when updating the value when the key is held down</td>
		<td>float</td>
		<td>0.15f</td>
	</tr>
	<tr>
		<td>SettingsItemType</td>
		<td>The type of setting item managed by this menu item (changing this will overwrite other settings)</td>
		<td>ESettingsItemType</td>
		<td>ESettingsItemType::None</td>
	</tr>
	<tr>
		<td>AutoSaveSettingsOnValueChanged</td>
		<td>Should the settings managed by this menu item automatically be saved when the value is changed?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>AutoSaveSettingsOnHighlightRemoved</td>
		<td>Should the settings managed by this menu item automatically be saved when the highlight state is removed?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>AutoSaveSettingsOnSelected</td>
		<td>Should the settings managed by this menu item automatically be saved when the menu item is selected?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>InputDevice</td>
		<td>The input device associated with the action to rebind</td>
		<td>EInputDevice</td>
		<td>EInputDevice::Unknown</td>
	</tr>
	<tr>
		<td>InputMappingContext</td>
		<td>The input mapping context containing the action to rebind</td>
		<td>UInputMappingContext*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>InputAction</td>
		<td>The input action to rebind</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>MappableName</td>
		<td>The player mappable name for the action to rebind</td>
		<td>FName</td>
		<td></td>
	</tr>
	<tr>
		<td>ShowValueSlider</td>
		<td>Should the value slider be shown for this menu item?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>ShowValueButtons</td>
		<td>Should the increase/decrease value buttons be shown for this menu item?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>ValueMapping</td>
		<td>A mapping of possible values to text</td>
		<td>TMap&lt;int, FText&gt;</td>
		<td></td>
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
		<td>AllowSelection</td>
		<td>Can the menu item be selected?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>KeepHighlightStyleWhenSelected</td>
		<td>Should the highlighted style be kept when the menu item is selected?</td>
		<td>bool</td>
		<td>false</td>
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
	<tr>
		<td>Menu</td>
		<td>A reference to the menu that contains this menu item</td>
		<td>UMenu*</td>
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
		<td>OnSelected</td>
		<td>Event used to notify other classes that the menu item was selected</td>
		<td></td>
	</tr>
	<tr>
		<td>OnSelectedInContainer</td>
		<td>Event used to notify other classes that a specific menu item in the container was selected</td>
		<td><strong>Index (int)</strong><br/>The index of the menu item that was selected</td>
	</tr>
	<tr>
		<td>OnHighlighted</td>
		<td>Event used to notify other classes that the menu item was highlighted</td>
		<td></td>
	</tr>
	<tr>
		<td>OnHighlightRemoved</td>
		<td>Event used to notify other classes that the menu item's highlighted state was removed</td>
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
		<td>Set the text displayed in the menu item</td>
		<td><strong>Text (FText&)</strong><br/>The new text displayed in the menu item</td>
		<td></td>
	</tr>
	<tr>
		<td>SetTitle</td>
		<td>Set the title displayed in the menu item</td>
		<td><strong>Text (FText&)</strong><br/>The new title displayed in the menu item</td>
		<td></td>
	</tr>
	<tr>
		<td>SetHighlightedState</td>
		<td>Set the highlighted state of the menu item</td>
		<td><strong>IsHighlighted (bool)</strong><br/>Is the menu item highlighted?<br/><br/><strong>PlayHighlightedAnimation (bool)</strong><br/>Should the highlighted animation be played?<br/><br/><strong>PlayHighlightedSound (bool)</strong><br/>Should the highlighted sound effect be played?</td>
		<td></td>
	</tr>
	<tr>
		<td>IsHighlighted</td>
		<td>Check if the menu item is highlighted</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the menu item is highlighted</td>
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
		<td><strong>Increment (float)</strong><br/>The amount added to the current value of the menu item</td>
		<td></td>
	</tr>
	<tr>
		<td>SelectItem</td>
		<td>Select the menu item</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>UnselectItem</td>
		<td>Unselect the menu item</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>SaveSettings</td>
		<td>Save the settings managed by this menu item</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>ApplySettings</td>
		<td>Apply the settings managed by this menu item</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>GetInputActionKey</td>
		<td>Get the key used by the specified input action</td>
		<td></td>
		<td><strong>FKey</strong><br/>The key used by the specified input action</td>
	</tr>
	<tr>
		<td>OnMenuBack</td>
		<td>Called when trying to go back in the menu</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the back event was handled</td>
	</tr>
	<tr>
		<td>AnyKeyPressed</td>
		<td>Called after any key is pressed by the player (used to remap controls)</td>
		<td><strong>Key (FKey)</strong><br/>The key pressed by the player</td>
		<td></td>
	</tr>
	<tr>
		<td>ApplyKeyBinding</td>
		<td>Apply the key binding for the input action</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>IsWaitingForKeyPress</td>
		<td>Is the menu item waiting for a key press?</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the menu item is waiting for a key press</td>
	</tr>
	<tr>
		<td>ShouldKeepHighlightedStyle</td>
		<td>Check if the menu item should keep the highlighted style</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the menu item should keep the highlighted state</td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>MenuItem</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > UI > Set Text</li>
	<li>Ultimate Starter Kit > UI > Set Title</li>
	<li>Ultimate Starter Kit > UI > Set Highlighted State</li>
	<li>Ultimate Starter Kit > UI > Is Highlighted</li>
	<li>Ultimate Starter Kit > UI > Get Value</li>
	<li>Ultimate Starter Kit > UI > Update Value</li>
	<li>Ultimate Starter Kit > UI > Select Item</li>
	<li>Ultimate Starter Kit > UI > Unselect Item</li>
	<li>Ultimate Starter Kit > UI > Save Settings</li>
	<li>Ultimate Starter Kit > UI > Apply Settings</li>
	<li>Ultimate Starter Kit > UI > Get Input Action Key</li>
	<li>Ultimate Starter Kit > UI > On Menu Back</li>
	<li>Ultimate Starter Kit > UI > Any Key Pressed</li>
	<li>Ultimate Starter Kit > UI > Apply Key Binding</li>
	<li>Ultimate Starter Kit > UI > Is Waiting For Key Press</li>
	<li>Ultimate Starter Kit > UI > Should Keep Highlighted Style</li>
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
	MenuItem->SetTitle(Text);
	MenuItem->SetHighlightedState(IsHighlighted, PlayHighlightedAnimation, PlayHighlightedSound);
	bool IsHighlightedValue = MenuItem->IsHighlighted();
	int Value = MenuItem->GetValue();
	MenuItem->UpdateValue(Increment);
	MenuItem->SelectItem();
	MenuItem->UnselectItem();
	MenuItem->SaveSettings();
	MenuItem->ApplySettings();
	FKey InputActionKey = MenuItem->GetInputActionKey();
	bool OnMenuBackValue = MenuItem->OnMenuBack();
	MenuItem->AnyKeyPressed(Key);
	MenuItem->ApplyKeyBinding();
	bool IsWaitingForKeyPressValue = MenuItem->IsWaitingForKeyPress();
	bool ShouldKeepHighlightedStyleValue = MenuItem->ShouldKeepHighlightedStyle();
}
```
