## Introduction
Base animation instance for a 3D platformer character

## Dependencies
The <code>PlatformerAnimationInstance</code> relies on other components of this plugin to work:
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
		<td>IdleAnimation</td>
		<td>The animation used when the character is in the idle state</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>WalkAnimation</td>
		<td>The animation used when the character is walking</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>RunAnimation</td>
		<td>The animation used when the character is running</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>JumpAnimation</td>
		<td>The animation used when the character is jumping</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>DoubleJumpAnimation</td>
		<td>The animation used when the character is double jumping</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>FallAnimation</td>
		<td>The animation used when the character is falling</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>LandAnimation</td>
		<td>The animation used when the character is landing</td>
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

## Blueprint Usage
You can use this template by creating your own animation blueprint and selecting <code>UPlatformerAnimationInstance</code> as the parent class. Set your animations and use this for your 3D platformer character