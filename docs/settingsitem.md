## Introduction
An implementation for a settings item controlling how the setting is configured, saved and applied

## Dependencies
The <code>SettingsItem</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../gameinstance">Game Instance</a>: Used to monitor for input device changes and handle saving/loading game data</li>
</ul>

## Implementations

There is already implementations for all settings items. But you can expand this if needed
<table>
    <tr>
        <th>Category</th>
        <th>Name</th>
        <th>Description</th>
    </tr>
    <tr>
        <td>Audio</td>
        <td>SettingsItemAudioMaster</td>
        <td>An implementation for the audio master settings item</td>
    </tr>
    <tr>
        <td>Audio</td>
        <td>SettingsItemAudioMusic</td>
        <td>An implementation for the audio music settings item</td>
    </tr>
    <tr>
        <td>Audio</td>
        <td>SettingsItemAudioEffects</td>
        <td>An implementation for the audio effects settings item</td>
    </tr>
    <tr>
        <td>Audio</td>
        <td>SettingsItemAudioUi</td>
        <td>An implementation for the audio UI settings item</td>
    </tr>
    <tr>
        <td>Audio</td>
        <td>SettingsItemAudioVoice</td>
        <td>An implementation for the audio voice settings item</td>
    </tr>
    <tr>
        <td>Graphics</td>
        <td>SettingsItemGraphicsResolution</td>
        <td>An implementation for the graphics resolution settings item</td>
    </tr>
    <tr>
        <td>Graphics</td>
        <td>SettingsItemGraphicsFullscreen</td>
        <td>An implementation for the graphics fullscreen settings item</td>
    </tr>
    <tr>
        <td>Graphics</td>
        <td>SettingsItemGraphicsViewDistance</td>
        <td>An implementation for the graphics view distance settings item</td>
    </tr>
    <tr>
        <td>Graphics</td>
        <td>SettingsItemGraphicsAntiAliasing</td>
        <td>An implementation for the graphics anti-aliasing settings item</td>
    </tr>
    <tr>
        <td>Graphics</td>
        <td>SettingsItemGraphicsPostProcessing</td>
        <td>An implementation for the graphics post processing settings item</td>
    </tr>
    <tr>
        <td>Graphics</td>
        <td>SettingsItemGraphicsShadowQuality</td>
        <td>An implementation for the graphics shadow quality settings item</td>
    </tr>
    <tr>
        <td>Graphics</td>
        <td>SettingsItemGraphicsTextureQuality</td>
        <td>An implementation for the graphics texture quality settings item</td>
    </tr>
    <tr>
        <td>Graphics</td>
        <td>SettingsItemGraphicsVisualEffects</td>
        <td>An implementation for the graphics visual effects settings item</td>
    </tr>
    <tr>
        <td>Graphics</td>
        <td>SettingsItemGraphicsShadingQuality</td>
        <td>An implementation for the graphics shading quality settings item</td>
    </tr>
    <tr>
        <td>Graphics</td>
        <td>SettingsItemGraphicsVsync</td>
        <td>An implementation for the graphics vsync settings item</td>
    </tr>
    <tr>
        <td>Graphics</td>
        <td>SettingsItemGraphicsFpsIndicator</td>
        <td>An implementation for the graphics FPS indicator settings item</td>
    </tr>
    <tr>
        <td>Accessibility</td>
        <td>SettingsItemAccessibilityColorBlindMode</td>
        <td>An implementation for the accessibility color blind mode settings item</td>
    </tr>
    <tr>
        <td>Accessibility</td>
        <td>SettingsItemAccessibilityColorBlindModeSeverity</td>
        <td>An implementation for the accessibility color blind mode severity settings item</td>
    </tr>
    <tr>
        <td>Controls</td>
        <td>SettingsItemControlsRemap</td>
        <td>An implementation for the controls settings item</td>
    </tr>
</table>

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
		<td>ConfigureMenuItem</td>
		<td>Configure the menu item</td>
		<td><strong>Config (void)</strong><br/>The settings config specified in the game instance<br/><br/><strong>Settings (USettingsData*)</strong><br/>The current settings data<br/><br/><strong>MenuItem (UMenuItem*)</strong><br/>The menu item to configure</td>
		<td></td>
	</tr>
	<tr>
		<td>SaveSettings</td>
		<td>Save the settings managed by a menu item</td>
		<td><strong>Settings (USettingsData*)</strong><br/>The current settings data<br/><br/><strong>MenuItem (UMenuItem*)</strong><br/>The menu item containing the updated settings</td>
		<td><strong>USettingsData*</strong><br/>The updated settings data</td>
	</tr>
	<tr>
		<td>ApplySettings</td>
		<td>Apply the settings</td>
		<td><strong>World (UObject*)</strong><br/>The world context<br/><br/><strong>Config (USettingsConfig*)</strong><br/>The settings config specified in the game instance<br/><br/><strong>Settings (USettingsData*)</strong><br/>The current settings data</td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>SettingsItem</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Settings > Configure Menu Item</li>
	<li>Ultimate Starter Kit > Settings > Save Settings</li>
	<li>Ultimate Starter Kit > Settings > Apply Settings</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>SettingsItem</code> can now be used in any of your C++ files:
```c++
#include "USK/Settings/SettingsItem.h"

void ATestActor::Test()
{
	// SettingsItem is a pointer to the USettingsItem
	SettingsItem->ConfigureMenuItem(Config, Settings, MenuItem);
	USettingsData* SaveSettingsValue = SettingsItem->SaveSettings(Settings, MenuItem);
	SettingsItem->ApplySettings(World, Config, Settings);
}
```
