## Introduction
The main actor responsible for tracking the different types of currency

## Supported Currencies
The currency system supports the following types of currency:
<ol>
    <li><strong>Coins:</strong> Used to track the amount of coins collected by the player</li>
    <li><strong>Gems:</strong> Used to track the amount of gems collected by the player</li>
    <li><strong>Custom:</strong> A custom currency that can be set up to track any type of currency</li>
</ol>

## Setting up the level
Before you can manage currencies, you need to add the <code>Currency Manager</code> actor to your level. This actor is responsible for managing all the types of currency and should be placed in every level where you use the currency system

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
        <td>A reference to the Save Manager actor in the current level. This is required if you want the currency system to automatically save/load the currency values</td>
        <td>*ASaveManager</td>
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
        <td>GetCoinManager</td>
        <td>Get a reference to the currency manager component responsible for managing the coins</td>
        <td></td>
        <td><strong>UCurrencyManagerComponent*</strong><br/>A reference to the currency manager responsible for managing the coins</td>
    </tr>
    <tr>
        <td>GetGemManager</td>
        <td>Get a reference to the currency manager component responsible for managing the gems</td>
        <td></td>
        <td><strong>UCurrencyManagerComponent*</strong><br/>A reference to the currency manager responsible for managing the gems</td>
    </tr>
    <tr>
        <td>AddManager</td>
        <td>Add a custom currency manager component</td>
        <td><strong>ID (FString)</strong><br/>The unique ID associated with the currency manager component</td>
        <td><strong>UCurrencyManagerComponent*</strong><br/>A reference to the custom currency manager component</td>
    </tr>
    <tr>
        <td>GetManager</td>
        <td>Get a reference to a custom currency manager component</td>
        <td><strong>ID (FString)</strong><br/>The unique ID associated with the currency manager component</td>
        <td><strong>UCurrencyManagerComponent*</strong><br/>A reference to the custom currency manager component</td>
    </tr>
</table>

## Blueprint Usage
You can save/load data using Blueprints by adding one of the following nodes (requires a reference to the <code>Currency Manager</code> actor):
<ul>
    <li>Ultimate Starter Kit > Currency Manager > Get Coin Manager</li>
    <li>Ultimate Starter Kit > Currency Manager > Get Gem Manager</li>
    <li>Ultimate Starter Kit > Currency Manager > Add Manager</li>
    <li>Ultimate Starter Kit > Currency Manager > Get Manager</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The currency system can now be used in any of your C++ files:
```c++
#include "USK/Currency/CurrencyManager.h"

void ATestActor::Test()
{
    // CurrencyManager is a pointer to the ACurrencyManager actor in the map

    UCurrencyManagerComponent* CoinManager = CurrencyManager->GetCoinManager();
    UCurrencyManagerComponent* GemManager = CurrencyManager->GetGemManager();
    UCurrencyManagerComponent* NewGoldManager = CurrencyManager->AddManager("GOLD_BARS");
    UCurrencyManagerComponent* GoldManager = CurrencyManager->GetManager("GOLD_BARS");
}
```