## Introduction
A weapon ammo item that can be picked up by a character

## Dependencies
The <code>WeaponAmmoItem</code> relies on other components of this plugin to work:
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
		<td>Ammo</td>
		<td>The amount of ammo to add to the weapon</td>
		<td>int</td>
		<td>10</td>
	</tr>
	<tr>
		<td>bAddToAnyWeapon</td>
		<td>Should the ammo be added to any weapon?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>AllowedWeapons</td>
		<td>The weapons that can use this ammo</td>
		<td>TArray&lt;TSubclassOf&lt;AWeapon&gt;&gt;</td>
		<td></td>
	</tr>
</table>
