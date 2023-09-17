## Introduction
Base character class

## Dependencies
The <code>USKCharacter</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
	<li><a href="../audio">Audio</a>: Used to play sound effects either 2D or at a specified location</li>
</ul>

## Components
The <code>USKCharacter</code> uses the following components:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>CameraComponent</td>
		<td>Base character class</td>
		<td>UCameraComponent*</td>
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
		<td>InputMappingContext</td>
		<td>The input mapping context used by the player</td>
		<td>UInputMappingContext*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>MoveAction</td>
		<td>The move input action</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>LookAroundAction</td>
		<td>The camera rotation input action</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>JumpAction</td>
		<td>The jump input action</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ShadowDecalClass</td>
		<td>The shadow decal class used to draw a shadow below the character while in the air</td>
		<td>TSubclassOf&lt;AShadowDecal&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>JumpSoundEffects</td>
		<td>An array of sound effects played when jumping</td>
		<td>TArray&lt;USoundBase*&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>JumpParticleFx</td>
		<td>The particle effects spawned when jumping</td>
		<td>UNiagaraSystem*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>JumpParticleFxSpawnOffset</td>
		<td>The offset applied to the location of the jump particles when spawning</td>
		<td>FVector</td>
		<td></td>
	</tr>
	<tr>
		<td>LandedSoundEffects</td>
		<td>An array of sound effects played when landing</td>
		<td>TArray&lt;USoundBase*&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>LandParticleFx</td>
		<td>The particle effects spawned when landing</td>
		<td>UNiagaraSystem*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>LandParticleFxSpawnOffset</td>
		<td>The offset applied to the location of the land particles when spawning</td>
		<td>FVector</td>
		<td></td>
	</tr>
	<tr>
		<td>VariableJumpHeight</td>
		<td>Does the character support variable jump height?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>VariableJumpHeightMaxHoldTime</td>
		<td>The amount of time to hold the jump button to reach the max height</td>
		<td>float</td>
		<td>0.3f</td>
	</tr>
	<tr>
		<td>JumpVelocity</td>
		<td>The velocity applied to the character when jumping</td>
		<td>float</td>
		<td>500.0f</td>
	</tr>
	<tr>
		<td>AirControl</td>
		<td>The amount of lateral movement control available to the character while in the air</td>
		<td>float</td>
		<td>1000.0f</td>
	</tr>
	<tr>
		<td>FallingFriction</td>
		<td>The amount of friction to apply to lateral air movement when falling</td>
		<td>float</td>
		<td>3.5f</td>
	</tr>
	<tr>
		<td>Gravity</td>
		<td>The amount of gravity applied to the character</td>
		<td>float</td>
		<td>2.0f</td>
	</tr>
	<tr>
		<td>CanDoubleJump</td>
		<td>Can the character perform a double jump?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>CanCoyoteJump</td>
		<td>Does the character support coyote time when trying to jump?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>CoyoteJumpTime</td>
		<td>The amount of coyote time for the character</td>
		<td>float</td>
		<td>0.375f</td>
	</tr>
	<tr>
		<td>CoyoteJumpVelocity</td>
		<td>The velocity applied to the character when performing a coyote jump</td>
		<td>float</td>
		<td>700.0f</td>
	</tr>
	<tr>
		<td>BrakingFriction</td>
		<td>Friction coefficient applied when braking</td>
		<td>float</td>
		<td>10.0f</td>
	</tr>
	<tr>
		<td>MaxAcceleration</td>
		<td>The rate of change of velocity</td>
		<td>float</td>
		<td>2500.0f</td>
	</tr>
</table>

## Blueprint Usage
There is no additional functions exposed to Blueprints. Just create the character and add it to your level