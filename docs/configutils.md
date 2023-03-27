## Introduction
A Blueprint Function Library class used to extract config values

## Dependencies
The <code>ConfigUtils</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

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
		<td>GetConfigValue</td>
		<td>Extract a config value from a given config file</td>
		<td><strong>Filename (FString)</strong><br/>The name of the config file<br/><br/><strong>Section (FString)</strong><br/>The section in the config file<br/><br/><strong>Key (FString)</strong><br/>The key in the config file<br/><br/><strong>DefaultValue (FString)</strong><br/>The default value to return if the config file can't be read</td>
		<td><strong>FString</strong><br/>The value extracted from the config file</td>
	</tr>
	<tr>
		<td>GetGameConfigValue</td>
		<td>Extract a config value from the default game config file</td>
		<td><strong>Section (FString)</strong><br/>The section in the config file<br/><br/><strong>Key (FString)</strong><br/>The key in the config file<br/><br/><strong>DefaultValue (FString)</strong><br/>The default value to return if the config file can't be read</td>
		<td><strong>FString</strong><br/>The value extracted from the config file</td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>ConfigUtils</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Utils > Config > Get Config Value</li>
	<li>Ultimate Starter Kit > Utils > Config > Get Game Config Value</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>ConfigUtils</code> can now be used in any of your C++ files:
```c++
#include "USK/Utils/ConfigUtils.h"

void ATestActor::Test()
{
	FString ConfigValue = UConfigUtils::GetConfigValue(Filename, Section, Key, DefaultValue);
	FString GameConfigValue = UConfigUtils::GetGameConfigValue(Section, Key, DefaultValue);
}
```
