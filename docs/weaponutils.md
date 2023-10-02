## Introduction
A Blueprint Function Library class used to manage weapons

## Dependencies
The <code>WeaponUtils</code> relies on other components of this plugin to work:
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
		<td>EquipWeapon</td>
		<td>Equip a weapon to a character</td>
		<td><strong>Owner (AUSKCharacter*)</strong><br/>The owner character<br/><br/><strong>WeaponClass (TSubclassOf<AWeapon>)</strong><br/>The weapon class to equip</td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>WeaponUtils</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Weapons > Equip Weapon</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>WeaponUtils</code> can now be used in any of your C++ files:
```c++
#include "USK/Weapons/WeaponUtils.h"

void ATestActor::Test()
{
	UWeaponUtils::EquipWeapon(Owner, WeaponClass);
}
```
