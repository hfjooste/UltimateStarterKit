## Introduction
Base character that can be used for 3D platformer games

## Dependencies
The <code>PlatformerCharacter</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Features
The following features are included in the 3D platformer character class:
<ol>
    <li><strong>Double Jumping</strong>: Additional jump with a different jump animation</li>
    <li><strong>Variable Jump Height</strong>: Adjust jump height based on how long the jump button is pressed</li>
    <li><strong>Coyote Time</strong>: Allow the character to jump for a short time after falling off the platform</li>
    <li><strong>Shadow Decal</strong>: A decal used as a shadow to indicate where the character will land</li>
    <li><strong>Adjustable Camera Distance</strong>: The camera automatically zooms in on the character while idle and zooms out as soon as the character starts moving</li>
    <li><strong>Jump & Land effects</strong>: Sound effects and particles when jumping and landing</li>
</ol>

All these features can be configured to meet your needs and can also be disabled

## Components
The <code>PlatformerCharacter</code> uses the following components:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>SpringArmComponent</td>
		<td>Base character that can be used for 3D platformer games</td>
		<td>USpringArmComponent*</td>
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
		<td>TargetArmLength</td>
		<td>Length of the spring arm component</td>
		<td>float</td>
		<td>350.0f</td>
	</tr>
	<tr>
		<td>ArmLengthMultiplier</td>
		<td>The multiplier applied to the spring arm component when the character is moving</td>
		<td>float</td>
		<td>0.4f</td>
	</tr>
	<tr>
		<td>CameraAdjustmentSpeed</td>
		<td>The speed used when adjusting the camera distance</td>
		<td>float</td>
		<td>3.0f</td>
	</tr>
</table>

## Blueprint Usage
There is no additional functions exposed to Blueprints. Just create the character and add it to your level