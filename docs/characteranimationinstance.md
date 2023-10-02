## Introduction
Base animation instance for USK characters

## Dependencies
The <code>USKCharacterAnimationInstance</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Animation Montages
The animation blueprint contains a <code>USK</code> slot that can be used to play animation montages

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
		<td>IdleAnimation</td>
		<td>The animation used when the character is in the idle state while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>WalkAnimation</td>
		<td>The animation used when the character is walking while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>RunAnimation</td>
		<td>The animation used when the character is running while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>JumpAnimation</td>
		<td>The animation used when the character is jumping while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>DoubleJumpAnimation</td>
		<td>The animation used when the character is double jumping while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>FallAnimation</td>
		<td>The animation used when the character is falling while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>LandAnimation</td>
		<td>The animation used when the character is landing while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>IdleWeaponOneHandedAnimation</td>
		<td>The animation used when the character is in the idle state with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>WalkWeaponOneHandedAnimation</td>
		<td>The animation used when the character is walking with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>RunWeaponOneHandedAnimation</td>
		<td>The animation used when the character is running with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>JumpWeaponOneHandedAnimation</td>
		<td>The animation used when the character is jumping with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>DoubleJumpWeaponOneHandedAnimation</td>
		<td>The animation used when the character is double jumping with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>FallWeaponOneHandedAnimation</td>
		<td>The animation used when the character is falling with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>LandOneHandedAnimation</td>
		<td>The animation used when the character is landing with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>IdleWeaponTwoHandedAnimation</td>
		<td>The animation used when the character is in the idle state with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>WalkWeaponTwoHandedAnimation</td>
		<td>The animation used when the character is walking with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>RunWeaponTwoHandedAnimation</td>
		<td>The animation used when the character is running with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>JumpWeaponTwoHandedAnimation</td>
		<td>The animation used when the character is jumping with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>DoubleJumpWeaponTwoHandedAnimation</td>
		<td>The animation used when the character is double jumping with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>FallWeaponTwoHandedAnimation</td>
		<td>The animation used when the character is falling with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>LandWeaponTwoHandedAnimation</td>
		<td>The animation used when the character is landing with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>MovementSpeed</td>
		<td>The movement speed fo the character</td>
		<td>float</td>
		<td></td>
	</tr>
	<tr>
		<td>IsInAir</td>
		<td>Is the character currently in the air?</td>
		<td>bool</td>
		<td></td>
	</tr>
	<tr>
		<td>IsDoubleJumping</td>
		<td>Is the character double jumping?</td>
		<td>bool</td>
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
		<td>GetIdleAnimation</td>
		<td>Get the idle animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The idle animation to play</td>
	</tr>
	<tr>
		<td>GetWalkAnimation</td>
		<td>Get the walk animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The walk animation to play</td>
	</tr>
	<tr>
		<td>GetRunAnimation</td>
		<td>Get the run animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The run animation to play</td>
	</tr>
	<tr>
		<td>GetJumpAnimation</td>
		<td>Get the jump animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The jump animation to play</td>
	</tr>
	<tr>
		<td>GetDoubleJumpAnimation</td>
		<td>Get the double jump animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The double jump animation to play</td>
	</tr>
	<tr>
		<td>GetFallAnimation</td>
		<td>Get the fall animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The fall animation to play</td>
	</tr>
	<tr>
		<td>GetLandAnimation</td>
		<td>Get the land animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The land animation to play</td>
	</tr>
</table>

## Blueprint Usage
You can use this template by creating your own animation blueprint and selecting <code>UPlatformerAnimationInstance</code> as the parent class. Set your animations and use this for your 3D platformer character