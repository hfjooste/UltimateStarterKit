## Introduction
A base game instance with support for saving and loading game data using multiple save slots

## Dependencies
The game instance relies on other components of this plugin to work:
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
        <td>TSubclassOf&lt;USaveGame&gt;</td>
        <td><code>nullptr</code></td>
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
        <td> Event used to notify other classes when the current input device is updated</td>
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
        <td>Return the save data from the current save slot. You will need to cast this to your specific save game class before you can access the data</td>
        <td></td>
        <td><strong>USaveGame*</strong><br/>A reference to the current save data</td>
    </tr>
    <tr>
        <td>SaveData</td>
        <td>Save the data to the current save slot</td>
        <td></td>
        <td></td>
    </tr>
    <tr>
        <td>SetCurrentSaveSlot</td>
        <td>Set the current save slot used to save/load data. You are required to set the save slot before using the save manager. If not, you will get a <code>nullptr</code> and might cause your game to crash</td>
        <td><strong>Index (int)</strong><br/>The index of the save slot to use</td>
        <td></td>
    </tr>
    <tr>
        <td>IsSaveSlotUsed</td>
        <td>Returns a boolean value indicating if the specified save slot is in use (contains data)</td>
        <td><strong>Index (int)</strong><br/>The index of the save slot to check</td>
        <td><strong>bool</strong><br/>A boolean value indicating if the save slot is used</td>
    </tr>
    <tr>
        <td>GetInputIndicatorIcon</td>
        <td>Get the input indicator icon for a specific action</td>
        <td><strong>InputAction (UInputAction*)</strong><br/>The input action<br/><br/><strong>Amount (int)</strong><br/>The amount of icons to retrieve</td>
        <td><strong>TArray&lt;UTexture2D*&gt;</strong><br/>An array of input indicator icons for the specified action</td>
    </tr>
</table>

## Blueprint Usage
You can save/load data using Blueprints by adding one of the following nodes (requires a reference to the <code>USK Game Instance</code>):
<ul>
    <li>Ultimate Starter Kit > Save Data > Set Current Save Slot</li>
    <li>Ultimate Starter Kit > Save Data > Get Save Data</li>
    <li>Ultimate Starter Kit > Save Data > Save Data</li>
    <li>Ultimate Starter Kit > Save Data > Is Save Slot Used</li>
    <li>Ultimate Starter Kit > Input > Get Input Indicator Icon</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The game instance can now be used in any of your C++ files:
```c++
#include "USK/Core/USKGameInstance.h"

void ATestActor::Test(UInputAction* JumpAction)
{
    UGameInstance* CurrentGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UUSKGameInstance* GameInstance = dynamic_cast&lt;UUSKGameInstance*&gt;(CurrentGameInstance);

    bool IsSlotInUse = GameInstance->IsSaveSlotUsed(0);
    if (IsSlotInUse)
    {
        GameInstance->SetCurrentSaveSlot(0);
        USaveGame* SaveGame = GameInstance->GetSaveData();
        UMySaveGame* MySaveGame = dynamic_cast&lt;UMySaveGame*&gt;(SaveGame);
        MySaveGame->CurrentLevel++;
        GameInstance->SaveData();
    }

    TArray<UTexture2D*> JumpIcons = GameInstance->GetInputIndicatorIcon(JumpAction, 1);
}
```