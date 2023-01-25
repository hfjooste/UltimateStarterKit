## Introduction
A system that is used to easily manage different types of currency

## Dependencies
The currency system relies on other components of this plugin to work:
<ul>
    <li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
    <li><a href="../savedata">Save Data</a>: Used to automatically save/load currency values (optional)</li>
</ul>

## Modules
The currency system uses 2 different classes to manage your currency:
<ol>
    <li><a href="../currencymanager">Currency Manager</a>: The main actor responsible for tracking the different types of currency</li>
    <li><a href="../currencycomponent">Currency Component</a>: The actor component used by the currency manager to update the value of a specific currency</li>
</ol>