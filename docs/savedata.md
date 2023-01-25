## Introduction
A system used to easily save/load game data with support for multiple save slots

## Dependencies
The save system relies on other components of this plugin to work:
<ul>
    <li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Save Data
You need to create a <code>USK Save Game</code> object before you can save/load data. This object contains all the data that you want to save. Just add the data you want to save as variables to the blueprint. The <code>Save Manager</code> will handle the rest

## Setting up the level
Before you can save/load data, you need to add the <code>Save Manager</code> actor to your level. This actor is responsible for managing all the save data and should be placed in every level where you use the save system

## Save Manager
The <code>Save Manager</code> is used to save and load the data specified in the <code>USK Save Game</code> object. You need to set the following properties before you can use the Save Manager:
<ul>
    <li><strong>Save Game Class:</strong> A reference to the <code>USK Save Game</code> class that contains the data you want to save</li>
</ul>

<i><strong>NB:</strong> You are required to set the save slot before using the save manager. If not, you will get a <code>nullptr</code> and might cause your game to crash</i>

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
        <td>AddOnDataLoadedEventBinding</td>
        <td>Add a binding to the OnDataLoaded event</td>
        <td><strong>OnDataLoadedFunction (Delegate)</strong><br/>The function called after the data is loaded</td>
        <td></td>
    </tr>
</table>

## Blueprint Usage
You can save/load data using Blueprints by adding one of the following nodes (requires a reference to the <code>Save Manager</code> actor):
<ul>
    <li>Ultimate Starter Kit > Save Manager > Set Current Save Slot</li>
    <li>Ultimate Starter Kit > Save Manager > Get Save Data</li>
    <li>Ultimate Starter Kit > Save Manager > Save Data</li>
    <li>Ultimate Starter Kit > Save Manager > Is Save Slot Used</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The save data plugin can now be used in any of your C++ files:
```c++
#include "USK/Data/SaveManager.h"

void ATestActor::Test()
{
    // SaveManager is a pointer to the ASaveManager actor in the map

    bool IsSlotInUse = SaveManager->IsSaveSlotUsed(0);
    if (IsSlotInUse)
    {
        SaveManager->SetCurrentSaveSlot(0);
        USaveGame* SaveGame = SaveManager->GetSaveData();
        UMySaveGame* MySaveGame = dynamic_cast&lt;UMySaveGame*&gt;(SaveGame);
        MySaveGame->CurrentLevel++;
        SaveManager->SaveData();
    }
}
```