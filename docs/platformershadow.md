## Introduction
Decal used to draw a shadow beneath a character when the character is in the air

## Dependencies
The <code>ShadowDecal</code> relies on other components of this plugin to work:
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
		<td>Initialize</td>
		<td>Initialize the shadow decal</td>
		<td><strong>OwnerCharacter (ACharacter*)</strong><br/>The character owning this shadow decal</td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>ShadowDecal</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Shadow Decal > Initialize</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>ShadowDecal</code> can now be used in any of your C++ files:
```c++
#include "USK/Character/ShadowDecal.h"

void ATestActor::Test()
{
	// ShadowDecal is a pointer to the AShadowDecal
	ShadowDecal->Initialize(OwnerCharacter);
}
```
