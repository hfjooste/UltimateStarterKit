## Introduction
The weapon attached to characters

## Dependencies
The <code>Weapon</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../audio">Audio</a>: Used to play sound effects either 2D or at a specified location</li>
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
		<td>WeaponType</td>
		<td>The type of weapon</td>
		<td>EWeaponType</td>
		<td></td>
	</tr>
	<tr>
		<td>ProjectileClass</td>
		<td>The projectile spawned by the weapon</td>
		<td>TSubclassOf&lt;AWeaponProjectile&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>FireSound</td>
		<td>The sound played each time the weapon is fired</td>
		<td>USoundBase*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>FireAnimation</td>
		<td>The animation played when the weapon is fired</td>
		<td>UAnimMontage*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>MuzzleOffset</td>
		<td>The muzzle offset of the weapon</td>
		<td>FVector</td>
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
		<td>AttachWeapon</td>
		<td>Attach the weapon to a character</td>
		<td><strong>TargetCharacter (AUSKCharacter*)</strong><br/>The character that will use the weapon</td>
		<td></td>
	</tr>
	<tr>
		<td>Fire</td>
		<td>Fire the weapon</td>
		<td></td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>Weapon</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Weapon > Attach Weapon</li>
	<li>Ultimate Starter Kit > Weapon > Fire</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>Weapon</code> can now be used in any of your C++ files:
```c++
#include "USK/Weapons/Weapon.h"

void ATestActor::Test()
{
	// Weapon is a pointer to the AWeapon
	Weapon->AttachWeapon(TargetCharacter);
	Weapon->Fire();
}
```
