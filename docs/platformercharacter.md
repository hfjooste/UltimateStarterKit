## Introduction
The 3D platformer character extends the base character class and adds some features used by popular 3D platformers

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
The 3D platformer character adds the following components compared to the base character class:
<ul>
    <li>SpringArmComponent: The spring arm component responsible for controlling the distance of the camera</li>
    <li>CameraComponent: The camera used by the character</li>
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
        <td>TArray&lt;USoundBase&gt;</td>
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
        <td>(0.0f, 0.0f, 0.0f)</td>
    </tr>
    <tr>
        <td>LandedSoundEffects</td>
        <td>An array of sound effects played when landing</td>
        <td>TArray&lt;USoundBase&gt;</td>
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
        <td>(0.0f, 0.0f, 0.0f)</td>
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
        <td>IsDoubleJumping</td>
        <td>Is the character double jumping?</td>
        <td>bool</td>
        <td>false</td>
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