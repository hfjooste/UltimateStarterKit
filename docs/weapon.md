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
		<td>WeaponMesh</td>
		<td>The skeletal mesh of the weapon</td>
		<td>USkeletalMeshComponent*</td>
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
		<td>AimFov</td>
		<td>The FOV of the camera while aiming</td>
		<td>float</td>
		<td>70</td>
	</tr>
	<tr>
		<td>Crosshair</td>
		<td>The crosshair used by the weapon</td>
		<td>UCrosshairConfig*</td>
		<td><code>nullptr</code></td>
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
		<td>Projectiles</td>
		<td>The projectiles spawned by the weapon</td>
		<td>TArray&lt;FWeaponProjectileData&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>bInfiniteAmmo</td>
		<td>Does the weapon have an infinite amount of ammo?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>bRequireReloading</td>
		<td>Does the weapon require reloading?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>bAutoReloadWhenFiringWhileEmpty</td>
		<td>Should the weapon automatically be reloaded when firing while empty?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>ReloadDuration</td>
		<td>The delay after reloading and before ammo is added to the weapon</td>
		<td>float</td>
		<td>0.65f</td>
	</tr>
	<tr>
		<td>Ammo</td>
		<td>The amount of ammo for the weapon</td>
		<td>int</td>
		<td>50</td>
	</tr>
	<tr>
		<td>AmmoPerClip</td>
		<td>The amount of ammo per clip</td>
		<td>int</td>
		<td>20</td>
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
		<td>WeaponAimTransform</td>
		<td>The relative transform of the weapon while aiming</td>
		<td>FTransform</td>
		<td></td>
	</tr>
	<tr>
		<td>RecoilCurve</td>
		<td>The curve used to add recoil to the weapon</td>
		<td>UCurveVector*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>RecoveryTime</td>
		<td>The recovery time after recoil was applied</td>
		<td>float</td>
		<td>1.0f</td>
	</tr>
	<tr>
		<td>RecoilRecoveryDelay</td>
		<td>The delay before we start recovering from recoil</td>
		<td>float</td>
		<td>0.15f</td>
	</tr>
	<tr>
		<td>bWeaponSway</td>
		<td>Should weapon sway be enabled?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>WeaponSwayMultiplier</td>
		<td>The multiplier applied to the weapon sway rotation</td>
		<td>float</td>
		<td>1.0f</td>
	</tr>
	<tr>
		<td>WeaponSwayInterpSpeed</td>
		<td>The speed used to interpolate the weapon sway rotation</td>
		<td>float</td>
		<td>10.0f</td>
	</tr>
	<tr>
		<td>FireCameraShake</td>
		<td>The camera shake applied when firing the weapon</td>
		<td>TSubclassOf&lt;UCameraShakeBase&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>MuzzleFlashParticleFx</td>
		<td>The muzzle flash particle effects</td>
		<td>UNiagaraSystem*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>MuzzleFlashParticleFxTransform</td>
		<td>The transform of the muzzle flash particle effects</td>
		<td>FTransform</td>
		<td></td>
	</tr>
	<tr>
		<td>FireSound</td>
		<td>The sound played each time the weapon is fired</td>
		<td>TArray&lt;USoundBase*&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>EmptyClipFireSound</td>
		<td>The sound played each time the weapon is fired with an empty clip</td>
		<td>TArray&lt;USoundBase*&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>ReloadSound</td>
		<td>The sound played when the weapon is reloaded</td>
		<td>TArray&lt;USoundBase*&gt;</td>
		<td></td>
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
	<tr>
		<td>EquipAnimation</td>
		<td>The animation played when the weapon is equipped</td>
		<td>UAnimMontage*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ReloadAnimation</td>
		<td>The animation played when the weapon is reloaded</td>
		<td>UAnimMontage*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ReloadAimAnimation</td>
		<td>The animation played when the weapon is reloaded while aiming</td>
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
		<td>OnWeaponFiredEmptyClip</td>
		<td>Event used to notify other classes when the weapon is fired with an empty clip</td>
		<td></td>
	</tr>
	<tr>
		<td>OnWeaponAmmoUpdated</td>
		<td>Event used to notify other classes when the weapon ammo is updated</td>
		<td><strong>Weapon (AWeapon*)</strong><br/>The current weapon used by the character<br/><br/><strong>Ammo (AWeapon*)</strong><br/>The amount of ammo remaining<br/><br/><strong>ReloadAmmo (AWeapon*)</strong><br/>The amount of ammo that can be used to reload the weapon</td>
	</tr>
	<tr>
		<td>OnWeaponAmmoEmpty</td>
		<td>Event used to notify other classes when the ammo is empty</td>
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
		<td><strong>TargetCharacter (AUSKCharacter*)</strong><br/>The character that will use the weapon<br/><br/><strong>IsNewWeapon (bool)</strong><br/>Is this a new weapon?</td>
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
	<tr>
		<td>AddAmmo</td>
		<td>Add more ammo to the weapon</td>
		<td><strong>Amount (int)</strong><br/>The amount of ammo to add</td>
		<td></td>
	</tr>
	<tr>
		<td>RemoveAmmo</td>
		<td>Remove ammo from the weapon</td>
		<td><strong>Amount (int)</strong><br/>The amount of ammo to remove</td>
		<td></td>
	</tr>
	<tr>
		<td>GetAmmoRemaining</td>
		<td>Get the amount of ammo remaining</td>
		<td></td>
		<td><strong>int</strong><br/>The amount of ammo remaining</td>
	</tr>
	<tr>
		<td>GetReloadAmmoRemaining</td>
		<td>Get the amount of ammo that can be used when reloading</td>
		<td></td>
		<td><strong>int</strong><br/>The amount of ammo that can be used when reloading</td>
	</tr>
	<tr>
		<td>Reload</td>
		<td>Reload the weapon</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>StartRecoil</td>
		<td>Start applying recoil to the weapon</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>StopRecoil</td>
		<td>Stop applying recoil to the weapon</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>ApplyRecoil</td>
		<td>Apply recoil to the weapon</td>
		<td><strong>DeltaSeconds (float)</strong><br/>Game time elapsed during last frame modified by the time dilation</td>
		<td></td>
	</tr>
	<tr>
		<td>StartRecoilRecovery</td>
		<td>Start recovering from recoil</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>StopRecoilRecovery</td>
		<td>Stop recovering from recoil</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>ApplyRecoilRecovery</td>
		<td>Recover from recoil</td>
		<td><strong>DeltaSeconds (float)</strong><br/>Game time elapsed during last frame modified by the time dilation</td>
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
	<li>Ultimate Starter Kit > Weapon > Add Ammo</li>
	<li>Ultimate Starter Kit > Weapon > Remove Ammo</li>
	<li>Ultimate Starter Kit > Weapon > Get Ammo Remaining</li>
	<li>Ultimate Starter Kit > Weapon > Get Reload Ammo Remaining</li>
	<li>Ultimate Starter Kit > Weapon > Reload</li>
	<li>Ultimate Starter Kit > Weapon > Start Recoil</li>
	<li>Ultimate Starter Kit > Weapon > Stop Recoil</li>
	<li>Ultimate Starter Kit > Weapon > Apply Recoil</li>
	<li>Ultimate Starter Kit > Weapon > Start Recoil Recovery</li>
	<li>Ultimate Starter Kit > Weapon > Stop Recoil Recovery</li>
	<li>Ultimate Starter Kit > Weapon > Apply Recoil Recovery</li>
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
	Weapon->Equip(TargetCharacter, IsNewWeapon);
	Weapon->Unequip();
	Weapon->StartFiring();
	Weapon->StopFiring();
	Weapon->AddAmmo(Amount);
	Weapon->RemoveAmmo(Amount);
	int AmmoRemaining = Weapon->GetAmmoRemaining();
	int ReloadAmmoRemaining = Weapon->GetReloadAmmoRemaining();
	Weapon->Reload();
	Weapon->StartRecoil();
	Weapon->StopRecoil();
	Weapon->ApplyRecoil(DeltaSeconds);
	Weapon->StartRecoilRecovery();
	Weapon->StopRecoilRecovery();
	Weapon->ApplyRecoilRecovery(DeltaSeconds);
}
```
