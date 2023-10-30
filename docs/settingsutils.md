## Introduction
A Blueprint Function Library class used to load, save and apply all settings

## Dependencies
The <code>SettingsUtils</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
	<li><a href="../gameinstance">Game Instance</a>: Used to monitor for input device changes and handle saving/loading game data</li>
</ul>

## Requirements
It's important that you configure the settings in the <a href="/gameinstance">Game Instance</a> before you can use the settings feature

## Controls Settings
Before you can use the plugin to automatically handle the controls settings, you need to configure your Input Mapping Context. You are required to specify the `Name` for each key that can be changed through the plugin. This `Name` should match the value you specify in your `Menu Item`<br/><br/>
<i><strong>NB: This feature is only available on Unreal Engine 5 and newer (UE5.3 support coming soon)</strong></i>

## API Reference
### Functions
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Params</th>
		<th>Return</th>
	</tr>
	<tr>
		<td>Initialize</td>
		<td>Initialize the settings</td>
		<td><strong>GameInstance (UUSKGameInstance*)</strong><br/>A reference to the game instance</td>
		<td></td>
	</tr>
	<tr>
		<td>LoadSettings</td>
		<td>Load the settings</td>
		<td></td>
		<td><strong>USettingsData*</strong><br/>The loaded settings data</td>
	</tr>
	<tr>
		<td>SaveSettings</td>
		<td>Save the settings</td>
		<td><strong>Settings (USettingsData*)</strong><br/>The updated settings data</td>
		<td></td>
	</tr>
	<tr>
		<td>ApplySettingsInWorld</td>
		<td>Apply the settings</td>
		<td><strong>World (UObject*)</strong><br/>The world context<br/><br/><strong>Settings (USettingsData*)</strong><br/>The settings data to apply</td>
		<td></td>
	</tr>
	<tr>
		<td>ApplySettings</td>
		<td>Apply the settings</td>
		<td><strong>GameInstance (UUSKGameInstance*)</strong><br/>A reference to the game instance<br/><br/><strong>Settings (USettingsData*)</strong><br/>The settings data to apply</td>
		<td></td>
	</tr>
	<tr>
		<td>ConfigureMenuItem</td>
		<td>Configure the menu item to manage the specified settings item</td>
		<td><strong>MenuItem (UMenuItem*)</strong><br/>The menu item to configure</td>
		<td></td>
	</tr>
	<tr>
		<td>SaveMenuItemSettings</td>
		<td>Save the settings managed by the menu item</td>
		<td><strong>MenuItem (UMenuItem*)</strong><br/>The menu item containing the updated settings<br/><br/><strong>ApplySettings (bool)</strong><br/>Should the settings also be applied?</td>
		<td></td>
	</tr>
	<tr>
		<td>ApplyMenuItemSettings</td>
		<td>Apply the settings managed by the menu item</td>
		<td><strong>MenuItem (UMenuItem*)</strong><br/>The menu item containing the updated settings</td>
		<td></td>
	</tr>
	<tr>
		<td>GetSettingsItemForMenuItem</td>
		<td>Get the settings item for the specified menu item</td>
		<td><strong>MenuItem (UMenuItem*)</strong><br/>The menu item to get the settings item for<br/><br/><strong>Config (USettingsConfig*)</strong><br/>The settings config specified in the game instance</td>
		<td><strong>USettingsItem*</strong><br/>The settings item</td>
	</tr>
	<tr>
		<td>GetSettingsItem</td>
		<td>Get the settings item for the specified settings item type</td>
		<td><strong>SettingsItemType (ESettingsItemType)</strong><br/>The menu item to get the settings item for<br/><br/><strong>Config (USettingsConfig*)</strong><br/>The settings config specified in the game instance</td>
		<td><strong>USettingsItem*</strong><br/>The settings item</td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>SettingsUtils</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Settings > Initialize</li>
	<li>Ultimate Starter Kit > Settings > Load Settings</li>
	<li>Ultimate Starter Kit > Settings > Save Settings</li>
	<li>Ultimate Starter Kit > Settings > Apply Settings In World</li>
	<li>Ultimate Starter Kit > Settings > Apply Settings</li>
	<li>Ultimate Starter Kit > Settings > Configure Menu Item</li>
	<li>Ultimate Starter Kit > Settings > Save Menu Item Settings</li>
	<li>Ultimate Starter Kit > Settings > Apply Menu Item Settings</li>
	<li>Ultimate Starter Kit > Settings > Get Settings Item For Menu Item</li>
	<li>Ultimate Starter Kit > Settings > Get Settings Item</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>SettingsUtils</code> can now be used in any of your C++ files:
```c++
#include "USK/Settings/SettingsUtils.h"

void ATestActor::Test()
{
	USettingsUtils::Initialize(GameInstance);
	USettingsData* LoadSettingsValue = USettingsUtils::LoadSettings();
	USettingsUtils::SaveSettings(Settings);
	USettingsUtils::ApplySettingsInWorld(World, Settings);
	USettingsUtils::ApplySettings(GameInstance, Settings);
	USettingsUtils::ConfigureMenuItem(MenuItem);
	USettingsUtils::SaveMenuItemSettings(MenuItem, ApplySettings);
	USettingsUtils::ApplyMenuItemSettings(MenuItem);
	USettingsItem* SettingsItemForMenuItem = USettingsUtils::GetSettingsItemForMenuItem(MenuItem, Config);
	USettingsItem* SettingsItem = USettingsUtils::GetSettingsItem(SettingsItemType, Config);
}
```
