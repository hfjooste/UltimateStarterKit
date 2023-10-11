## Introduction
A decal spawned when a projectile hits something

## Dependencies
The <code>WeaponProjectileDecal</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

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
		<td>bAutomaticallyDestroy</td>
		<td>Should the decal automatically be destroyed?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>Lifetime</td>
		<td>The lifetime of the decal</td>
		<td>float</td>
		<td>10.0f</td>
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
		<td>DestroyDecal</td>
		<td>Destroy the decal actor</td>
		<td></td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>WeaponProjectileDecal</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Weapon Projectile Decal > Destroy Decal</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>WeaponProjectileDecal</code> can now be used in any of your C++ files:
```c++
#include "USK/Weapons/WeaponProjectileDecal.h"

void ATestActor::Test()
{
	// WeaponProjectileDecal is a pointer to the AWeaponProjectileDecal
	WeaponProjectileDecal->DestroyDecal();
}
```
