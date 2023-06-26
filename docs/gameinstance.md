## Introduction
A base game instance with support for saving and loading game data using multiple save slots

## Dependencies
The <code>USKGameInstance</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Using the Game Instance
You need to create a blueprint using the `USKGameInstance_Implementation` as a parent before using the game instance. The input indicators feature is already configured if you use this base class. If you prefer to set this up manually, you can use `USKGameInstance` instead. After creating your own game instance blueprint, set this as the default game instance:
<ol>
    <li>Open the Project Settings</li>
    <li>Go to Project > Maps & Modes</li>
    <li>Change the <code>Game Instance Class</code> value to your own blueprint</li>
</ol>

## Save Data
You need to create a <code>USK Save Game</code> object before you can save/load data. This object contains all the data that you want to save. Just add the data you want to save as variables to the blueprint. The <code>Game Instance</code> will handle the rest. You also need to set the following properties before you can save/load data:
<ul>
    <li><strong>Save Game Class:</strong> A reference to the <code>USK Save Game</code> class that contains the data you want to save</li>
</ul>

<i><strong>NB:</strong> You are required to set the save slot before you can save/load data. If not, you will get a <code>nullptr</code> and might cause your game to crash</i>

## Input Indicators
The Game Instance will automatically detect input events and update the current input device if needed. If the input device is changed, other classes will be notified through the <code>OnInputDeviceUpdated</code> event

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
		<td>SaveGameClass</td>
		<td>The class that holds the data that should be saved/loaded</td>
		<td>TSubclassOf&lt;UUSKSaveGame&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>SettingsConfig</td>
		<td>The configuration for the settings</td>
		<td>USettingsConfig*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>IsInputIndicatorsEnabled</td>
		<td>Is the input indicators feature enabled?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>InputMappingContext</td>
		<td>The input mapping context used to extract the keys based on specific input actions</td>
		<td>UInputMappingContext*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>KeyboardMouseInputMappings</td>
		<td>A map of all keyboard/mouse keys and the texture displayed in the indicator</td>
		<td>TMap&lt;FKey, UTexture2D*&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>GenericControllerInputMappings</td>
		<td>A map of all generic controller keys and the texture displayed in the indicator</td>
		<td>TMap&lt;FKey, UTexture2D*&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>XboxControllerInputMappings</td>
		<td>A map of all Xbox controller keys and the texture displayed in the indicator</td>
		<td>TMap&lt;FKey, UTexture2D*&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>PlaystationControllerInputMappings</td>
		<td>A map of all Playstation controller keys and the texture displayed in the indicator</td>
		<td>TMap&lt;FKey, UTexture2D*&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>SwitchControllerInputMappings</td>
		<td>A map of all Switch controller keys and the texture displayed in the indicator</td>
		<td>TMap&lt;FKey, UTexture2D*&gt;</td>
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
		<td>OnDataLoadedEvent</td>
		<td>Event used to notify other classes when the save data is loaded</td>
		<td></td>
	</tr>
	<tr>
		<td>OnInputDeviceUpdated</td>
		<td>Event used to notify other classes when the current input device is updated</td>
		<td></td>
	</tr>
	<tr>
		<td>OnGamePaused</td>
		<td>Event used to notify other classes when the game is paused</td>
		<td></td>
	</tr>
	<tr>
		<td>OnGameUnpaused</td>
		<td>Event used to notify other classes when the game is unpaused</td>
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
		<td>GetSaveData</td>
		<td>Get the save data that is currently loaded</td>
		<td></td>
		<td><strong>UUSKSaveGame*</strong><br/>A reference to the current save data</td>
	</tr>
	<tr>
		<td>SaveData</td>
		<td>Save the modified data currently in memory</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>SetCurrentSaveSlot</td>
		<td>Set the current save slot</td>
		<td><strong>Index (int)</strong><br/>The index of the save slot</td>
		<td></td>
	</tr>
	<tr>
		<td>IsSaveSlotUsed</td>
		<td>Check if a save slot is used</td>
		<td><strong>Index (int)</strong><br/>The index of the save slot to check</td>
		<td><strong>bool</strong><br/>A boolean value indicating if the save slot is used</td>
	</tr>
	<tr>
		<td>EnableInputIndicators</td>
		<td>Enable the input indicators feature</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>DisableInputIndicators</td>
		<td>Disable the input indicators feature</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>GetInputIndicatorIcon</td>
		<td>Get the input indicator icon for a specific action</td>
		<td><strong>InputAction (UInputAction*)</strong><br/>The input action<br/><br/><strong>Amount (int)</strong><br/>The amount of icons to retrieve</td>
		<td><strong>TArray&lt;UTexture2D*&gt;</strong><br/>An array of input indicator icons for the specified action</td>
	</tr>
	<tr>
		<td>GetInputIndicatorIconForKey</td>
		<td>Get the input indicator icon for a specific key</td>
		<td><strong>Key (FKey)</strong><br/>The key used to retrieve the input indicator icon<br/><br/><strong>InputDevice (EInputDevice)</strong><br/>The input device used to retrieve the input indicator icon</td>
		<td><strong>UTexture2D*</strong><br/>The input indicator icon for the specified key</td>
	</tr>
	<tr>
		<td>GetKeyForInputAction</td>
		<td>Get the key used by a specific input action</td>
		<td><strong>Context (UInputMappingContext*)</strong><br/>The input mapping context<br/><br/><strong>InputAction (UInputAction*)</strong><br/>The input action<br/><br/><strong>MappableName (FName)</strong><br/>The player mappable name for the action</td>
		<td><strong>FKey</strong><br/>The key used by the specified input action</td>
	</tr>
	<tr>
		<td>UpdateKeyBindings</td>
		<td>Update the key bindings that was changed by the player</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>PauseGame</td>
		<td>Pause the game</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>UnpauseGame</td>
		<td>Unpause the game</td>
		<td></td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>USKGameInstance</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Save Data > Get Save Data</li>
	<li>Ultimate Starter Kit > Save Data > Save Data</li>
	<li>Ultimate Starter Kit > Save Data > Set Current Save Slot</li>
	<li>Ultimate Starter Kit > Save Data > Is Save Slot Used</li>
	<li>Ultimate Starter Kit > Input > Enable Input Indicators</li>
	<li>Ultimate Starter Kit > Input > Disable Input Indicators</li>
	<li>Ultimate Starter Kit > Input > Get Input Indicator Icon</li>
	<li>Ultimate Starter Kit > Input > Get Input Indicator Icon For Key</li>
	<li>Ultimate Starter Kit > Input > Get Key For Input Action</li>
	<li>Ultimate Starter Kit > Input > Update Key Bindings</li>
	<li>Ultimate Starter Kit > Pause > Pause Game</li>
	<li>Ultimate Starter Kit > Pause > Unpause Game</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>USKGameInstance</code> can now be used in any of your C++ files:
```c++
#include "USK/Core/USKGameInstance.h"

void ATestActor::Test()
{
	// USKGameInstance is a pointer to the UUSKGameInstance
	UUSKSaveGame* SaveData = USKGameInstance->GetSaveData();
	USKGameInstance->SaveData();
	USKGameInstance->SetCurrentSaveSlot(Index);
	bool IsSaveSlotUsedValue = USKGameInstance->IsSaveSlotUsed(Index);
	USKGameInstance->EnableInputIndicators();
	USKGameInstance->DisableInputIndicators();
	TArray<UTexture2D*> InputIndicatorIcon = USKGameInstance->GetInputIndicatorIcon(InputAction, Amount);
	UTexture2D* InputIndicatorIconForKey = USKGameInstance->GetInputIndicatorIconForKey(Key, InputDevice);
	FKey KeyForInputAction = USKGameInstance->GetKeyForInputAction(Context, InputAction, MappableName);
	USKGameInstance->UpdateKeyBindings();
	USKGameInstance->PauseGame();
	USKGameInstance->UnpauseGame();
}
```
