## Introduction
The actor component used by the currency manager to update the value of a specific currency. It's important to never manually add this component to any actor. The currency manager will handle that

## Currency ID
Each currency type requires a unique ID. This is used to identify the type of currency and automatically save/load the currency values. The build in currencies are using the following values:
<table>
    <tr>
        <th>Currency</th>
        <th>ID</th>
    <tr>
    <tr>
        <td>Coins</td>
        <td>USK_CURRENCY_COINS</td>
    </tr>
    <tr>
        <td>Gems</td>
        <td>USK_CURRENCY_GEMS</td>
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
        <td>SaveManager</td>
        <td>A reference to the Save Manager actor in the current level. This is required if you want the currency system to automatically save/load the currency values</td>
        <td>*ASaveManager</td>
        <td><code>nullptr</code></td>
    </tr>
    <tr>
        <td>ID</td>
        <td>The unique ID associated with the currency being managed</td>
        <td>FString</td>
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
        <td>GetAmount</td>
        <td>Get the current amount of currency</td>
        <td></td>
        <td><strong>int</strong><br/>The amount of currency</td>
    </tr>
    <tr>
        <td>Add</td>
        <td>Add to the currency</td>
        <td><strong>Amount (int)</strong><br/>The amount to add</td>
        <td><strong>int</strong><br/>The new amount of currency</td>
    </tr>
    <tr>
        <td>Remove</td>
        <td>Remove from the currency</td>
        <td><strong>Amount (int)</strong><br/>The amount to remove</td>
        <td><strong>int</strong><br/>The new amount of currency</td>
    </tr>
    <tr>
        <td>HaveEnough</td>
        <td>Check if there is enough currency</td>
        <td><strong>RequiredAmount (int)</strong><br/>The required amount of currency</td>
        <td><strong>bool</strong><br/>A boolean value indicating if there is enough currency</td>
    </tr>
</table>

## Blueprint Usage
You can save/load data using Blueprints by adding one of the following nodes (requires a reference to <code>Currency Manager Component</code>):
<ul>
    <li>Ultimate Starter Kit > Currency Manager > Get Amount</li>
    <li>Ultimate Starter Kit > Currency Manager > Add</li>
    <li>Ultimate Starter Kit > Currency Manager > Remove</li>
    <li>Ultimate Starter Kit > Currency Manager > Have Enough</li>
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
    int Coins = CoinManager->GetAmount();
    CoinManager->Add(10);
    CoinManager->Remove(5);
    bool CanAffordItem = CoinManager->HaveEnough(50);
}
```