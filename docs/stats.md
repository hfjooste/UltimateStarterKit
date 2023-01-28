## Introduction
A system used to easily manage character stats. It supports regenerating the value (including an optional delay) and automatically saving the stat values

## Dependencies
The currency system relies on other components of this plugin to work:
<ul>
    <li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
    <li><a href="../savedata">Save Data</a>: Used to automatically save/load stat values (optional)</li>
</ul>

## Stat Component
Before you can manage stats, you need to add a <code>Stat Component</code> to the actor/character containing the stat. The stat can be configured by changing the properties on the <code>Stat Component</code>

<i><strong>NB:</strong> Adding the <code>Save Manager</code> to the level is required if you want the currency system to automatically save/load the currency values</i>

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
        <td>SaveManager</td>
        <td>A reference to the save manager used to automatically save the value</td>
        <td>ASaveManager*</td>
        <td><code>nullptr</code></td>
    </tr>
    <tr>
        <td>ID</td>
        <td>The unique ID associated with the stat being managed</td>
        <td>FString</td>
        <td></td>
    </tr>
    <tr>
        <td>InitialValue</td>
        <td>The initial value of the stat</td>
        <td>float</td>
        <td>100.0f</td>
    </tr>
    <tr>
        <td>MaxValue</td>
        <td>The maximum value of the stat</td>
        <td>float</td>
        <td>100.0f</td>
    </tr>
    <tr>
        <td>Regenerate</td>
        <td>The amount of value that is regenerated every second</td>
        <td>float</td>
        <td>0.0f</td>
    </tr>
    <tr>
        <td>RegenerateDelay</td>
        <td>The delay before the value is regenerated</td>
        <td>float</td>
        <td>0.0f</td>
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
        <td>OnValueUpdated</td>
        <td>Event that is broadcasted every time the stat value is updated</td>
        <td><strong>Value (float)</strong><br/>The new value of the stat<br/><br/><strong>ValuePercentage (float)</strong><br/>The new stat value as a percentage of the max value</td>
    </tr>
    <tr>
        <td>OnValueZero</td>
        <td>Event that is broadcasted every time the stat value reaches 0</td>
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
        <td>GetValue</td>
        <td>Get the current stat value</td>
        <td></td>
        <td><strong>float</strong><br/>The current stat value</td>
    </tr>
    <tr>
        <td>GetValuePercentage</td>
        <td>Get the current stat value as a percentage of the max value</td>
        <td></td>
        <td><strong>float</strong><br/>The current stat value as a percentage of the max value</td>
    </tr>
    <tr>
        <td>UpdateValue</td>
        <td>Update the current stat value</td>
        <td><strong>Amount (float)</strong><br/>The amount to add to the stat value</td>
        <td><strong>float</strong><br/>The new stat value</td>
    </tr>
    <tr>
        <td>LoadValue</td>
        <td>Load the saved value for the stat using the save manager</td>
        <td></td>
        <td></td>
    </tr>
</table>

## Blueprint Usage
You can save/load data using Blueprints by adding one of the following nodes (requires a reference to <code>Stat Component</code>):
<ul>
    <li>Ultimate Starter Kit > Stats > Get Value</li>
    <li>Ultimate Starter Kit > Stats > Get Value Percentage</li>
    <li>Ultimate Starter Kit > Stats > Update Value</li>
    <li>Ultimate Starter Kit > Stats > Load Value</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The save data plugin can now be used in any of your C++ files:
```c++
#include "USK/Stats/StatsComponent.h"

void ATestActor::Test()
{
    // Health is a pointer to the Stat Component

    int HealthValue = Health->GetValue();
    int HealthPercentage = Health->GetValuePercentage();
    int NewHealthValue = Health->UpdateValue(-50.0f);
    Health->LoadValue();
}
```