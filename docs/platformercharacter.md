## Introduction
Base character that can be used for 3D platformer games

## Dependencies
The <code>PlatformerCharacter</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

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

### Functions
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Params</th>
		<th>Return</th>
	</tr>
	<tr>
		<td>GetSpringArmComponent</td>
		<td>Get the spring arm component of the character</td>
		<td></td>
		<td><strong>USpringArmComponent*</strong><br/>The spring arm component responsible for controlling the distance of the camera</td>
	</tr>
</table>

## Blueprint Usage
There is no additional functions exposed to Blueprints. Just create the character and add it to your level