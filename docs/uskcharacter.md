## Introduction
Base character class

## Dependencies
The <code>USKCharacter</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
	<li><a href="../audio">Audio</a>: Used to play sound effects either 2D or at a specified location</li>
</ul>

## Camera Clipping
Sometimes parts of the character mesh or weapon might clip when close to the camera (especially while aiming). This can be fixed by changing <code>Set Near Clip Plane</code> to <code>0.1</code> in your project settings

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
		<td>The camera used by the character</td>
		<td>UCameraComponent*</td>
	</tr>
	<tr>
		<td>SpringArmComponent</td>
		<td>The spring arm component responsible for controlling the distance of the camera</td>
		<td>USpringArmComponent*</td>
	</tr>
	<tr>
		<td>CrouchTimeline</td>
		<td>The timeline component used for smooth crouching</td>
		<td>UTimelineComponent*</td>
	</tr>
	<tr>
		<td>ProneTimeline</td>
		<td>The timeline component used for smooth proning</td>
		<td>UTimelineComponent*</td>
	</tr>
	<tr>
		<td>AimTimeline</td>
		<td>The timeline component used for aiming</td>
		<td>UTimelineComponent*</td>
	</tr>
	<tr>
		<td>LookAtCenterTimeline</td>
		<td>The timeline component used to look at the center of the screen</td>
		<td>UTimelineComponent*</td>
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
		<td>The input mapping context used by the character</td>
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
		<td>SprintAction</td>
		<td>The sprint input action</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>FireWeaponAction</td>
		<td>The fire weapon input action</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>AimAction</td>
		<td>The aim down sights input action</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>EquipNextWeaponAction</td>
		<td>The equip next weapon input action</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>EquipPreviousWeaponAction</td>
		<td>The equip previous weapon input action</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ReloadWeaponAction</td>
		<td>The reload weapon input action</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchAction</td>
		<td>The crouch input action</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneAction</td>
		<td>The prone input action</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>LeanAction</td>
		<td>The lean input action</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>InteractAction</td>
		<td>The interact input action</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SwitchCameraPerspectiveAction</td>
		<td>The switch camera perspective input action</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CameraPerspective</td>
		<td>The camera perspective used by the character</td>
		<td>ECameraPerspective</td>
		<td></td>
	</tr>
	<tr>
		<td>bCanSwitchCameraPerspectives</td>
		<td>Can the character switch perspectives?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>bSmoothCameraRotation</td>
		<td>Should the camera rotation be smooth or instant?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>SmoothCameraRotationSpeed</td>
		<td>The speed used to smooth the camera rotations</td>
		<td>float</td>
		<td>5.0f</td>
	</tr>
	<tr>
		<td>HeadSocketName</td>
		<td>The name of the head socket used to attach the camera in the first person perspective</td>
		<td>FName</td>
		<td></td>
	</tr>
	<tr>
		<td>CameraAttachOffset</td>
		<td>The offset of the camera after attaching to the head</td>
		<td>FVector</td>
		<td></td>
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
		<td>bCanStompJump</td>
		<td>Can the character perform a high jump directly after landing from a stomp?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>StompJumpDuration</td>
		<td>The duration after the stomp that the character can perform the stomp jump</td>
		<td>float</td>
		<td>0.35f</td>
	</tr>
	<tr>
		<td>StompJumpVelocity</td>
		<td>The velocity applied to the character when performing a stomp jump</td>
		<td>float</td>
		<td>1250.0f</td>
	</tr>
	<tr>
		<td>bCanCrouchJump</td>
		<td>Can the character perform a high jump while crouching?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>CrouchJumpVelocity</td>
		<td>The velocity applied to the character when performing a crouch jump</td>
		<td>float</td>
		<td>1250.0f</td>
	</tr>
	<tr>
		<td>IsDoubleJumping</td>
		<td>Is the character double jumping?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>bCanLongJump</td>
		<td>Is the character allowed to perform a long jump?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>LongJumpVelocity</td>
		<td>The velocity applied to the character during a long jump</td>
		<td>FVector</td>
		<td>FVecto</td>
	</tr>
	<tr>
		<td>MovementSpeed</td>
		<td>The default movement speed</td>
		<td>float</td>
		<td>600.0f</td>
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
		<td>bSmoothMovement</td>
		<td>Should the movement be smooth or instant?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>SmoothMovementSpeed</td>
		<td>The speed used to smooth the movement</td>
		<td>float</td>
		<td>5.0f</td>
	</tr>
	<tr>
		<td>bCanSprint</td>
		<td>Can the character sprint?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>SprintSpeed</td>
		<td>The movement speed while the character is sprinting</td>
		<td>float</td>
		<td>950.0f</td>
	</tr>
	<tr>
		<td>bSprintRequiresStamina</td>
		<td>Does sprinting require stamina?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>SprintStaminaStatName</td>
		<td>The name of the stamina stat used for sprinting</td>
		<td>FName</td>
		<td></td>
	</tr>
	<tr>
		<td>SprintStaminaUseRate</td>
		<td>The amount of stamina used per second while sprinting</td>
		<td>float</td>
		<td>20.0f</td>
	</tr>
	<tr>
		<td>bCanCrouch</td>
		<td>Can the character crouch?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>bHoldToCrouch</td>
		<td>Should the crouch/prone action be held down to crouch?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>CrouchSpeed</td>
		<td>The movement speed while the character is crouching</td>
		<td>float</td>
		<td>300.0f</td>
	</tr>
	<tr>
		<td>CrouchCurve</td>
		<td>The float curve used for smooth crouching</td>
		<td>UCurveFloat*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>bCanProne</td>
		<td>Can the character prone?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>bHoldToProne</td>
		<td>Should the crouch/prone action be held down to prone?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>ProneTraceHeight</td>
		<td>The height of the trace used to check if the character can prone</td>
		<td>float</td>
		<td>5.0f</td>
	</tr>
	<tr>
		<td>ProneTraceOffsetZ</td>
		<td>The Z-offset of the trace used to check if the character can prone</td>
		<td>float</td>
		<td>-20.0f</td>
	</tr>
	<tr>
		<td>ProneMoveTraceSizeMultiplier</td>
		<td>The multiplier applied to the trace size when the character is moving while proning</td>
		<td>float</td>
		<td>0.5f</td>
	</tr>
	<tr>
		<td>ProneSpeed</td>
		<td>The movement speed while the character is proning</td>
		<td>float</td>
		<td>100.0f</td>
	</tr>
	<tr>
		<td>ProneCurve</td>
		<td>The float curve used for smooth proning</td>
		<td>UCurveFloat*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>bCanStomp</td>
		<td>Can the character perform a stomp?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>MinAirTimeBeforeStomping</td>
		<td>The minimum air time before the character can perform a stomp</td>
		<td>float</td>
		<td>0.3f</td>
	</tr>
	<tr>
		<td>StompVelocity</td>
		<td>The velocity applied to the character after performing a stomp</td>
		<td>float</td>
		<td>-5000.0f</td>
	</tr>
	<tr>
		<td>StompZeroGravityDuration</td>
		<td>The amount of time the character will be in zero gravity after performing a stomp</td>
		<td>float</td>
		<td>0.5f</td>
	</tr>
	<tr>
		<td>StompLandVelocity</td>
		<td>The velocity applied to the character when landing after performing a stomp</td>
		<td>float</td>
		<td>750.0f</td>
	</tr>
	<tr>
		<td>StompRecoveryTime</td>
		<td>The time it takes (in seconds) before the character recovers from a stomp and can move again</td>
		<td>float</td>
		<td>0.25f</td>
	</tr>
	<tr>
		<td>StompCameraShake</td>
		<td>The camera shake applied when performing a stomp</td>
		<td>TSubclassOf&lt;UCameraShakeBase&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>bCanLean</td>
		<td>Can the character lean?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>LeanSpeed</td>
		<td>The speed used when leaning</td>
		<td>float</td>
		<td>5.0f</td>
	</tr>
	<tr>
		<td>LeanOffset</td>
		<td>The offset applied to the camera when leaning</td>
		<td>float</td>
		<td>50.0f</td>
	</tr>
	<tr>
		<td>LeanRotation</td>
		<td>The rotation applied to the camera when leaning</td>
		<td>float</td>
		<td>25.0f</td>
	</tr>
	<tr>
		<td>bLookAtCenterWhileIdle</td>
		<td>Should the character automatically rotate to look at the center of the screen while idle?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>MaxLookAtCenterRotationWhileIdle</td>
		<td>The maximum rotation that can be applied while looking at the center of the screen while idle</td>
		<td>float</td>
		<td>90.0f</td>
	</tr>
	<tr>
		<td>bLookAtCenterWhileRunning</td>
		<td>Should the character automatically rotate to look at the center of the screen while running?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>MaxLookAtCenterRotationWhileRunning</td>
		<td>The maximum rotation that can be applied while looking at the center of the screen while running</td>
		<td>float</td>
		<td>90.0f</td>
	</tr>
	<tr>
		<td>bLookAtCenterWhileSprinting</td>
		<td>Should the character automatically rotate to look at the center of the screen while sprinting?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>MaxLookAtCenterRotationWhileSprinting</td>
		<td>The maximum rotation that can be applied while looking at the center of the screen while sprinting</td>
		<td>float</td>
		<td>90.0f</td>
	</tr>
	<tr>
		<td>bLookAtCenterWhileCrouching</td>
		<td>Should the character automatically rotate to look at the center of the screen while crouching?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>MaxLookAtCenterRotationWhileCrouching</td>
		<td>The maximum rotation that can be applied while looking at the center of the screen while crouching</td>
		<td>float</td>
		<td>60.0f</td>
	</tr>
	<tr>
		<td>bLookAtCenterWhileProning</td>
		<td>Should the character automatically rotate to look at the center of the screen while proning?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>MaxLookAtCenterRotationWhileProning</td>
		<td>The maximum rotation that can be applied while looking at the center of the screen while proning</td>
		<td>float</td>
		<td>45.0f</td>
	</tr>
	<tr>
		<td>LookAtCenterCurve</td>
		<td>The float curve used to look at the center of the screen</td>
		<td>UCurveFloat*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>bCanSlide</td>
		<td>Can the character perform a slide?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>SlideSpeed</td>
		<td>The movement speed while the character is sliding</td>
		<td>float</td>
		<td>2500.0f</td>
	</tr>
	<tr>
		<td>bSlideRequiresSprinting</td>
		<td>Does sliding require the character to sprint?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>SlideMinSpeed</td>
		<td>The minimum movement speed before a slide is allowed</td>
		<td>float</td>
		<td>400.0f</td>
	</tr>
	<tr>
		<td>SlidingTime</td>
		<td>The time the character is allowed to slide</td>
		<td>float</td>
		<td>0.5f</td>
	</tr>
	<tr>
		<td>SlidingCooldown</td>
		<td>The cooldown after a slide before another slide can be performed</td>
		<td>float</td>
		<td>0.5f</td>
	</tr>
	<tr>
		<td>SlideSoundEffects</td>
		<td>The sound effect played when the character is sliding</td>
		<td>TArray&lt;USoundBase*&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>MaxWeapons</td>
		<td>The maximum amount of weapons that the character can carry</td>
		<td>int</td>
		<td>2</td>
	</tr>
	<tr>
		<td>DefaultWeaponClass</td>
		<td>The default weapon the character will equip on spawn</td>
		<td>TSubclassOf&lt;AWeapon&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>AimCurve</td>
		<td>The float curve used for aiming</td>
		<td>UCurveFloat*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>DefaultCrosshair</td>
		<td>The default crosshair to use if no weapon is equipped</td>
		<td>UCrosshairConfig*</td>
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
		<td>OnCurrentWeaponUpdated</td>
		<td>Event used to notify other classes when the weapon is updated</td>
		<td><strong>Weapon (AWeapon*)</strong><br/>The current weapon used by the character<br/><br/><strong>Ammo (AWeapon*)</strong><br/>The amount of ammo remaining<br/><br/><strong>ReloadAmmo (AWeapon*)</strong><br/>The amount of ammo that can be used to reload the weapon</td>
	</tr>
	<tr>
		<td>OnCrosshairUpdated</td>
		<td>Event used to notify other classes that the crosshair is updated</td>
		<td><strong>Crosshair (UCrosshairConfig*)</strong><br/>The current crosshair config</td>
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
		<td>GetCameraComponent</td>
		<td>Get the camera used by the character</td>
		<td></td>
		<td><strong>UCameraComponent*</strong><br/>The camera used by the character</td>
	</tr>
	<tr>
		<td>GetSpringArmComponent</td>
		<td>Get the spring arm component of the character</td>
		<td></td>
		<td><strong>USpringArmComponent*</strong><br/>The spring arm component responsible for controlling the distance of the camera</td>
	</tr>
	<tr>
		<td>GetCameraPerspective</td>
		<td>Get the current camera perspective</td>
		<td></td>
		<td><strong>ECameraPerspective</strong><br/>The current camera perspective</td>
	</tr>
	<tr>
		<td>UpdateCameraPerspective</td>
		<td>Update the current camera perspective</td>
		<td><strong>NewCameraPerspective (ECameraPerspective)</strong><br/>The new camera perspective</td>
		<td></td>
	</tr>
	<tr>
		<td>SwitchCameraPerspective</td>
		<td>Switch the current camera perspective</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>SetWeapon</td>
		<td>Set the current weapon used by the character</td>
		<td><strong>NewWeapon (AWeapon*)</strong><br/>The new weapon</td>
		<td></td>
	</tr>
	<tr>
		<td>GetWeapon</td>
		<td>Get the current weapon used by the character</td>
		<td></td>
		<td><strong>AWeapon*</strong><br/>The current weapon used by the character</td>
	</tr>
	<tr>
		<td>HasWeapon</td>
		<td>Check if the character has a weapon</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the character has a weapon</td>
	</tr>
	<tr>
		<td>IsCrouching</td>
		<td>Check if the character is crouching</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the character is crouching</td>
	</tr>
	<tr>
		<td>IsProning</td>
		<td>Check if the character is proning</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the character is proning</td>
	</tr>
	<tr>
		<td>IsEndingCrouch</td>
		<td>Check if the character is busy ending the crouch</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the character is busy ending the crouch</td>
	</tr>
	<tr>
		<td>IsEndingProne</td>
		<td>Check if the character is busy ending the prone</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the character is busy ending the prone</td>
	</tr>
	<tr>
		<td>IsStomping</td>
		<td>Check if the character is stomping</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the character is stomping</td>
	</tr>
	<tr>
		<td>IsStompStarting</td>
		<td>Check if the character is starting to stomp</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the character is starting to stomp</td>
	</tr>
	<tr>
		<td>GetLeanCameraRoll</td>
		<td>Get the current lean camera roll</td>
		<td></td>
		<td><strong>float</strong><br/>The current lean camera roll</td>
	</tr>
	<tr>
		<td>GetLookAtCenterRotation</td>
		<td>Get the look at center rotation</td>
		<td></td>
		<td><strong>float</strong><br/>The look at center rotation</td>
	</tr>
	<tr>
		<td>IsSliding</td>
		<td>Check if the character is sliding</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the character is sliding</td>
	</tr>
	<tr>
		<td>IsEndingSlide</td>
		<td>Check if the character is busy ending the slide</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the character is busy ending the slide</td>
	</tr>
	<tr>
		<td>GetInteractTrigger</td>
		<td>Get the current interact trigger</td>
		<td></td>
		<td><strong>UInteractTrigger*</strong><br/>The current interact trigger</td>
	</tr>
	<tr>
		<td>UpdateInteractTrigger</td>
		<td>Update the current interact trigger</td>
		<td><strong>NewInteractTrigger (UInteractTrigger*)</strong><br/>The new interact trigger</td>
		<td></td>
	</tr>
	<tr>
		<td>OnWeaponUpdated</td>
		<td>Called when the current weapon is updated</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>OnNewWeaponEquipped</td>
		<td>Called when a new weapon is equipped for the first time</td>
		<td><strong>Weapon (AWeapon*)</strong><br/>The new weapon that was equipped</td>
		<td></td>
	</tr>
	<tr>
		<td>IsAiming</td>
		<td>Check if the character is aiming</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the character is aiming</td>
	</tr>
	<tr>
		<td>GetCrosshair</td>
		<td>Get the crosshair configuration</td>
		<td></td>
		<td><strong>UCrosshairConfig*</strong><br/>The crosshair configuration</td>
	</tr>
	<tr>
		<td>GetWeaponSway</td>
		<td>Get the current weapon sway rotation</td>
		<td></td>
		<td><strong>FRotator</strong><br/>The current weapon sway rotation</td>
	</tr>
	<tr>
		<td>StartFiringWeapon</td>
		<td>Start firing the current weapon</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>StopFiringWeapon</td>
		<td>Stop firing the current weapon</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>EquipNextWeapon</td>
		<td>Equip the next weapon in the list of available weapons</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>EquipPreviousWeapon</td>
		<td>Equip the previous weapon in the list of available weapons</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>StartCrouching</td>
		<td>Start crouching</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>StopCrouching</td>
		<td>Stop crouching</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>StartProning</td>
		<td>Start proning</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>StopProning</td>
		<td>Stop proning</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>UpdateCharacterMeshLocationWhileCrouching</td>
		<td>Update the character mesh location while crouching</td>
		<td><strong>SizeDifference (float)</strong><br/>The difference between the original capsule size and the crouched capsule size</td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
There is no additional functions exposed to Blueprints. Just create the character and add it to your level