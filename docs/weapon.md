## Introduction
The weapon attached to characters

## Dependencies
The <code>Weapon</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
	<li><a href="../audio">Audio</a>: Used to play sound effects either 2D or at a specified location</li>
</ul>

## Components
The <code>Weapon</code> uses the following components:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>MuzzleFlash</td>
		<td>The muzzle flash of the weapon</td>
		<td>USceneComponent*</td>
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
		<td>WeaponType</td>
		<td>The type of weapon</td>
		<td>EWeaponType</td>
		<td></td>
	</tr>
	<tr>
		<td>WeaponFireMode</td>
		<td>The fire mode of weapon</td>
		<td>EWeaponFireMode</td>
		<td></td>
	</tr>
	<tr>
		<td>FireRate</td>
		<td>The fire rate of the weapon (amount of seconds between each shot)</td>
		<td>float</td>
		<td>0.2f</td>
	</tr>
	<tr>
		<td>MaxShotsPerFireEvent</td>
		<td>The amount of shots fired per fire event</td>
		<td>int</td>
		<td>3</td>
	</tr>
	<tr>
		<td>bInfiniteAmmo</td>
		<td>Does the weapon have an infinite amount of ammo?</td>
		<td>bool</td>
		<td></td>
	</tr>
	<tr>
		<td>Ammo</td>
		<td>The amount of ammo for the weapon</td>
		<td>int</td>
		<td>50</td>
	</tr>
	<tr>
		<td>WeaponAttachPoint</td>
		<td>The attach point used by all weapons</td>
		<td>FName</td>
		<td></td>
	</tr>
	<tr>
		<td>WeaponTransform</td>
		<td>The relative transform of the weapon after it is attached to a character</td>
		<td>FTransform</td>
		<td></td>
	</tr>
	<tr>
		<td>Projectiles</td>
		<td>The projectiles spawned by the weapon</td>
		<td>TArray&lt;FWeaponProjectileData&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>MuzzleFlashParticleFx</td>
		<td>The muzzle flash particle effects</td>
		<td>UNiagaraSystem*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>FireSound</td>
		<td>The sound played each time the weapon is fired</td>
		<td>USoundBase*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>EmptyClipFireSound</td>
		<td>The sound played each time the weapon is fired with an empty clip</td>
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
		<td>EmptyClipFireAnimation</td>
		<td>The animation played when the weapon is fired with an empty clip</td>
		<td>UAnimMontage*</td>
		<td><code>nullptr</code></td>
	</tr>
</table>

### Events
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Params</th>
	</tr>
	<tr>
		<td>OnWeaponEquipped</td>
		<td>Event used to notify other classes when the weapon is equipped</td>
		<td></td>
	</tr>
	<tr>
		<td>OnWeaponUnequipped</td>
		<td>Event used to notify other classes when the weapon is unequipped</td>
		<td></td>
	</tr>
	<tr>
		<td>OnWeaponFired</td>
		<td>Event used to notify other classes when the weapon is fired</td>
		<td></td>
	</tr>
	<tr>
		<td>OnWeaponAmmoEmpty</td>
		<td>Event used to notify other classes when the ammo is empty</td>
		<td></td>
	</tr>
	<tr>
		<td>OnWeaponFiredEmptyClip</td>
		<td>Event used to notify other classes when the weapon is fired with an empty clip</td>
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
		<td>Equip</td>
		<td>Equip the weapon</td>
		<td><strong>TargetCharacter (AUSKCharacter*)</strong><br/>The character that will use the weapon</td>
		<td></td>
	</tr>
	<tr>
		<td>Unequip</td>
		<td>Unequip the weapon</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>StartFiring</td>
		<td>Start firing the weapon</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>StopFiring</td>
		<td>Stop firing the weapon</td>
		<td></td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>Weapon</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Weapon > Equip</li>
	<li>Ultimate Starter Kit > Weapon > Unequip</li>
	<li>Ultimate Starter Kit > Weapon > Start Firing</li>
	<li>Ultimate Starter Kit > Weapon > Stop Firing</li>
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
	Weapon->Equip(TargetCharacter);
	Weapon->Unequip();
	Weapon->StartFiring();
	Weapon->StopFiring();
}
```
