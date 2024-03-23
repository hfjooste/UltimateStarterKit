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
		<td>BlendBoneName</td>
		<td>The name of the bone used to blend the character's animations</td>
		<td>FName</td>
		<td></td>
	</tr>
	<tr>
		<td>bMeshSpaceRotationBlend</td>
		<td>Whether to blend bone rotations in mesh space or in local space</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>bMeshSpaceScaleBlend</td>
		<td>Whether to blend bone scales in mesh space or in local space</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>bBlendRootMotionBasedOnRootBone</td>
		<td>Should we incorporate the per-bone blend weight of the root bone when lending root motion?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>bEnableDirectionalMovementAnimations</td>
		<td>Should directional movement animations be used?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>IdleBaseAnimation</td>
		<td>The base animation used when the character is in the idle state</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>WalkBaseAnimation</td>
		<td>The base animation used when the character is walking</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>WalkForwardBaseAnimation</td>
		<td>The base animation used when the character is walking forward</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>WalkBackwardsBaseAnimation</td>
		<td>The base animation used when the character is walking backwards</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>WalkLeftBaseAnimation</td>
		<td>The base animation used when the character is walking left</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>WalkRightBaseAnimation</td>
		<td>The base animation used when the character is walking right</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>RunBaseAnimation</td>
		<td>The base animation used when the character is running</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>RunForwardBaseAnimation</td>
		<td>The base animation used when the character is running forward</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>RunBackwardsBaseAnimation</td>
		<td>The base animation used when the character is running backwards</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>RunLeftBaseAnimation</td>
		<td>The base animation used when the character is running left</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>RunRightBaseAnimation</td>
		<td>The base animation used when the character is running right</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SprintBaseAnimation</td>
		<td>The base animation used when the character is sprinting</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SprintForwardBaseAnimation</td>
		<td>The base animation used when the character is sprinting forward</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SprintBackwardsBaseAnimation</td>
		<td>The base animation used when the character is sprinting backwards</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SprintLeftBaseAnimation</td>
		<td>The base animation used when the character is sprinting left</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SprintRightBaseAnimation</td>
		<td>The base animation used when the character is sprinting right</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>JumpBaseAnimation</td>
		<td>The base animation used when the character is jumping</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>DoubleJumpBaseAnimation</td>
		<td>The base animation used when the character is double jumping</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>FallBaseAnimation</td>
		<td>The base animation used when the character is falling</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>LandBaseAnimation</td>
		<td>The base animation used when the character is landing</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchStartBaseAnimation</td>
		<td>The base animation used when the character starts crouching</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchEndBaseAnimation</td>
		<td>The base animation used when the character stops crouching</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchIdleBaseAnimation</td>
		<td>The base animation used when the character is crouching and idle</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchWalkBaseAnimation</td>
		<td>The base animation used when the character is crouching and walking</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchWalkForwardBaseAnimation</td>
		<td>The base animation used when the character is crouching and walking forward</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchWalkBackwardsBaseAnimation</td>
		<td>The base animation used when the character is crouching and walking backwards</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchWalkLeftBaseAnimation</td>
		<td>The base animation used when the character is crouching and walking left</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchWalkRightBaseAnimation</td>
		<td>The base animation used when the character is crouching and walking right</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneStartBaseAnimation</td>
		<td>The base animation used when the character starts proning</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneEndBaseAnimation</td>
		<td>The base animation used when the character stops proning</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneIdleBaseAnimation</td>
		<td>The base animation used when the character is proning and idle</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneMoveBaseAnimation</td>
		<td>The base animation used when the character is proning and moving</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>StompStartBaseAnimation</td>
		<td>The base animation used when the character is starting to stomp</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>StompFallBaseAnimation</td>
		<td>The base animation used when the character is falling after a stomp</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>StompLandBaseAnimation</td>
		<td>The base animation used when the character is landing after a stomp</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SlideStartBaseAnimation</td>
		<td>The base animation used when the character starts sliding</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SlideEndBaseAnimation</td>
		<td>The base animation used when the character stops sliding</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SlideLoopBaseAnimation</td>
		<td>The base animation used when the character is sliding</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
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
		<td>SprintAnimation</td>
		<td>The animation used when the character is sprinting while unarmed</td>
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
		<td>CrouchStartAnimation</td>
		<td>The animation used when the character starts crouching while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchEndAnimation</td>
		<td>The animation used when the character stops crouching while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchIdleAnimation</td>
		<td>The animation used when the character is crouching and idle while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchWalkAnimation</td>
		<td>The animation used when the character is crouching and walking while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneStartAnimation</td>
		<td>The animation used when the character starts proning while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneEndAnimation</td>
		<td>The animation used when the character stops proning while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneIdleAnimation</td>
		<td>The animation used when the character is proning and idle while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneMoveAnimation</td>
		<td>The animation used when the character is proning and moving while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>StompStartAnimation</td>
		<td>The animation used when the character is starting to stomp while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>StompFallAnimation</td>
		<td>The animation used when the character is falling after a stomp while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>StompLandAnimation</td>
		<td>The animation used when the character is landing after a stomp while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SlideStartAnimation</td>
		<td>The animation used when the character starts sliding while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SlideEndAnimation</td>
		<td>The animation used when the character stops sliding while unarmed</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SlideLoopAnimation</td>
		<td>The animation used when the character is sliding while unarmed</td>
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
		<td>SprintWeaponOneHandedAnimation</td>
		<td>The animation used when the character is sprinting with a one handed weapon</td>
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
		<td>LandWeaponOneHandedAnimation</td>
		<td>The animation used when the character is landing with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchStartWeaponOneHandedAnimation</td>
		<td>The animation used when the character starts crouching with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchEndWeaponOneHandedAnimation</td>
		<td>The animation used when the character stops crouching with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchIdleWeaponOneHandedAnimation</td>
		<td>The animation used when the character is crouching and idle with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchWalkWeaponOneHandedAnimation</td>
		<td>The animation used when the character is crouching and walking with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneStartWeaponOneHandedAnimation</td>
		<td>The animation used when the character starts proning with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneEndWeaponOneHandedAnimation</td>
		<td>The animation used when the character stops proning with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneIdleWeaponOneHandedAnimation</td>
		<td>The animation used when the character is proning and idle with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneMoveWeaponOneHandedAnimation</td>
		<td>The animation used when the character is proning and moving with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>StompStartWeaponOneHandedAnimation</td>
		<td>The animation used when the character is starting to stomp with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>StompFallWeaponOneHandedAnimation</td>
		<td>The animation used when the character is falling after a stomp with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>StompLandWeaponOneHandedAnimation</td>
		<td>The animation used when the character is landing after a stomp with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SlideStartWeaponOneHandedAnimation</td>
		<td>The animation used when the character starts sliding with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SlideEndWeaponOneHandedAnimation</td>
		<td>The animation used when the character stops sliding with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SlideLoopWeaponOneHandedAnimation</td>
		<td>The animation used when the character is sliding with a one handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>IdleWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character is in the idle state with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>WalkWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character is walking with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>RunWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character is running with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SprintWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character is sprinting with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>JumpWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character is jumping with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>DoubleJumpWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character is double jumping with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>FallWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character is falling with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>LandWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character is landing with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchStartWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character starts crouching with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchEndWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character stops crouching with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchIdleWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character is crouching and idle with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchWalkWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character is crouching and walking with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneStartWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character starts proning with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneEndWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character stops proning with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneIdleWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character is proning and idle with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneMoveWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character is proning and moving with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>StompStartWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character is starting to stomp with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>StompFallWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character is falling after a stomp with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>StompLandWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character is landing after a stomp with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SlideStartWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character starts sliding with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SlideEndWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character stops sliding with a one handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SlideLoopWeaponAimOneHandedAnimation</td>
		<td>The animation used when the character is sliding with a one handed weapon while aiming</td>
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
		<td>SprintWeaponTwoHandedAnimation</td>
		<td>The animation used when the character is sprinting with a two handed weapon</td>
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
		<td>CrouchStartWeaponTwoHandedAnimation</td>
		<td>The animation used when the character starts crouching with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchEndWeaponTwoHandedAnimation</td>
		<td>The animation used when the character stops crouching with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchIdleWeaponTwoHandedAnimation</td>
		<td>The animation used when the character is crouching and idle with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchWalkWeaponTwoHandedAnimation</td>
		<td>The animation used when the character is crouching and walking with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneStartWeaponTwoHandedAnimation</td>
		<td>The animation used when the character starts proning with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneEndWeaponTwoHandedAnimation</td>
		<td>The animation used when the character stops proning with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneIdleWeaponTwoHandedAnimation</td>
		<td>The animation used when the character is proning and idle with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneMoveWeaponTwoHandedAnimation</td>
		<td>The animation used when the character is proning and moving with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>StompStartWeaponTwoHandedAnimation</td>
		<td>The animation used when the character is starting to stomp with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>StompFallWeaponTwoHandedAnimation</td>
		<td>The animation used when the character is falling after a stomp with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>StompLandWeaponTwoHandedAnimation</td>
		<td>The animation used when the character is landing after a stomp with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SlideStartWeaponTwoHandedAnimation</td>
		<td>The animation used when the character starts sliding with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SlideEndWeaponTwoHandedAnimation</td>
		<td>The animation used when the character stops sliding with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SlideLoopWeaponTwoHandedAnimation</td>
		<td>The animation used when the character is sliding with a two handed weapon</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>IdleWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character is in the idle state with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>WalkWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character is walking with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>RunWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character is running with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SprintWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character is sprinting with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>JumpWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character is jumping with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>DoubleJumpWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character is double jumping with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>FallWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character is falling with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>LandWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character is landing with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchStartWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character starts crouching with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchEndWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character stops crouching with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchIdleWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character is crouching and idle with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CrouchWalkWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character is crouching and walking with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneStartWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character starts proning with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneEndWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character stops proning with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneIdleWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character is proning and idle with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ProneMoveWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character is proning and moving with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>StompStartWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character is starting to stomp with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>StompFallWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character is falling after a stomp with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>StompLandWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character is landing after a stomp with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SlideStartWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character starts sliding with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SlideEndWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character stops sliding with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SlideLoopWeaponAimTwoHandedAnimation</td>
		<td>The animation used when the character is sliding with a two handed weapon while aiming</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>MovementBlendSpeed</td>
		<td>The blend speed used when updating the movement speed</td>
		<td>float</td>
		<td>10.0f</td>
	</tr>
	<tr>
		<td>MovementSpeed</td>
		<td>The movement speed of the character</td>
		<td>float</td>
		<td></td>
	</tr>
	<tr>
		<td>MovementDirection</td>
		<td>The movement direction of the character multiplied by the movement speed</td>
		<td>FVector2D</td>
		<td></td>
	</tr>
	<tr>
		<td>bIsCrouching</td>
		<td>Is the character currently crouching?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>bIsProning</td>
		<td>Is the character currently proning?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>bIsStomping</td>
		<td>Is the character currently stomping?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>StompBlendValue</td>
		<td>The value used to blend stomp animations</td>
		<td>float</td>
		<td></td>
	</tr>
	<tr>
		<td>bIsStompStarting</td>
		<td>Is the character starting the stomp?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>bIsEndingCrouch</td>
		<td>Is the character busy ending the crouch?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>bIsEndingProne</td>
		<td>Is the character busy ending the prone?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>IsInAir</td>
		<td>Is the character currently in the air?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>IsDoubleJumping</td>
		<td>Is the character double jumping?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>LeanCameraRotationModifier</td>
		<td>The modifier applied to the lean camera rotation</td>
		<td>float</td>
		<td>1.0f</td>
	</tr>
	<tr>
		<td>LeanCameraRoll</td>
		<td>The lean camera roll</td>
		<td>float</td>
		<td></td>
	</tr>
	<tr>
		<td>LeanBoneName</td>
		<td>The bone to rotate while the character is leaning</td>
		<td>FName</td>
		<td></td>
	</tr>
	<tr>
		<td>bIsSliding</td>
		<td>Is the character currently sliding?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>bIsEndingSlide</td>
		<td>Is the character busy ending the slide?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>bIsAiming</td>
		<td>Is the character aiming?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>AimRotation</td>
		<td>The rotation applied to the character while aiming</td>
		<td>float</td>
		<td></td>
	</tr>
	<tr>
		<td>LookAtCenterRotation</td>
		<td>The rotation applied to the character to look at the center of the screen</td>
		<td>float</td>
		<td></td>
	</tr>
	<tr>
		<td>AimBoneName</td>
		<td>The bone to rotate while the player is aiming up or down using the first person camera perspective</td>
		<td>FName</td>
		<td></td>
	</tr>
	<tr>
		<td>WeaponSwayBoneName</td>
		<td>The bone to rotate to simulate weapon sway</td>
		<td>FName</td>
		<td></td>
	</tr>
	<tr>
		<td>WeaponSway</td>
		<td>The weapon sway rotation applied to the character</td>
		<td>FRotator</td>
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
		<td>GetIdleBaseAnimation</td>
		<td>Get the base idle animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The idle animation to play</td>
	</tr>
	<tr>
		<td>GetWalkBaseAnimation</td>
		<td>Get the base walk animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The walk animation to play</td>
	</tr>
	<tr>
		<td>GetWalkForwardBaseAnimation</td>
		<td>Get the base walk forward animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The walk forward animation to play</td>
	</tr>
	<tr>
		<td>GetWalkBackwardsBaseAnimation</td>
		<td>Get the base walk backwards animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The walk backwards animation to play</td>
	</tr>
	<tr>
		<td>GetWalkLeftBaseAnimation</td>
		<td>Get the base walk left animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The walk left animation to play</td>
	</tr>
	<tr>
		<td>GetWalkRightBaseAnimation</td>
		<td>Get the base walk right animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The walk right animation to play</td>
	</tr>
	<tr>
		<td>GetRunBaseAnimation</td>
		<td>Get the base run animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The run animation to play</td>
	</tr>
	<tr>
		<td>GetRunForwardBaseAnimation</td>
		<td>Get the base run forward animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The run forward animation to play</td>
	</tr>
	<tr>
		<td>GetRunBackwardsBaseAnimation</td>
		<td>Get the base run backwards animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The run backwards animation to play</td>
	</tr>
	<tr>
		<td>GetRunLeftBaseAnimation</td>
		<td>Get the base run left animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The run left animation to play</td>
	</tr>
	<tr>
		<td>GetRunRightBaseAnimation</td>
		<td>Get the base run right animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The run right animation to play</td>
	</tr>
	<tr>
		<td>GetSprintBaseAnimation</td>
		<td>Get the base sprint animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The sprint animation to play</td>
	</tr>
	<tr>
		<td>GetSprintForwardBaseAnimation</td>
		<td>Get the base sprint forward animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The sprint forward animation to play</td>
	</tr>
	<tr>
		<td>GetSprintBackwardsBaseAnimation</td>
		<td>Get the base sprint backwards animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The sprint backwards animation to play</td>
	</tr>
	<tr>
		<td>GetSprintLeftBaseAnimation</td>
		<td>Get the base sprint left animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The sprint left animation to play</td>
	</tr>
	<tr>
		<td>GetSprintRightBaseAnimation</td>
		<td>Get the base sprint right animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The sprint right animation to play</td>
	</tr>
	<tr>
		<td>GetJumpBaseAnimation</td>
		<td>Get the base jump animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The jump animation to play</td>
	</tr>
	<tr>
		<td>GetDoubleJumpBaseAnimation</td>
		<td>Get the base double jump animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The double jump animation to play</td>
	</tr>
	<tr>
		<td>GetFallBaseAnimation</td>
		<td>Get the base fall animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The fall animation to play</td>
	</tr>
	<tr>
		<td>GetLandBaseAnimation</td>
		<td>Get the base land animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The land animation to play</td>
	</tr>
	<tr>
		<td>GetCrouchStartBaseAnimation</td>
		<td>Get the base crouch start animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The crouch start animation to play</td>
	</tr>
	<tr>
		<td>GetCrouchEndBaseAnimation</td>
		<td>Get the base crouch end animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The crouch end animation to play</td>
	</tr>
	<tr>
		<td>GetCrouchIdleBaseAnimation</td>
		<td>Get the base crouch idle animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The crouch idle animation to play</td>
	</tr>
	<tr>
		<td>GetCrouchWalkBaseAnimation</td>
		<td>Get the base crouch walk animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The crouch walk animation to play</td>
	</tr>
	<tr>
		<td>GetCrouchWalkForwardBaseAnimation</td>
		<td>Get the base crouch walk forward animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The crouch walk forward animation to play</td>
	</tr>
	<tr>
		<td>GetCrouchWalkBackwardsBaseAnimation</td>
		<td>Get the base crouch walk backwards animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The crouch walk backwards animation to play</td>
	</tr>
	<tr>
		<td>GetCrouchWalkLeftBaseAnimation</td>
		<td>Get the base crouch walk left animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The crouch walk left animation to play</td>
	</tr>
	<tr>
		<td>GetCrouchWalkRightBaseAnimation</td>
		<td>Get the base crouch walk right animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The crouch walk right animation to play</td>
	</tr>
	<tr>
		<td>GetProneStartBaseAnimation</td>
		<td>Get the base prone start animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The prone start animation to play</td>
	</tr>
	<tr>
		<td>GetProneEndBaseAnimation</td>
		<td>Get the base prone end animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The prone end animation to play</td>
	</tr>
	<tr>
		<td>GetProneIdleBaseAnimation</td>
		<td>Get the base prone idle animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The prone idle animation to play</td>
	</tr>
	<tr>
		<td>GetProneMoveBaseAnimation</td>
		<td>Get the base prone walk animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The prone walk animation to play</td>
	</tr>
	<tr>
		<td>GetStompStartBaseAnimation</td>
		<td>Get the base stomp start animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The stomp start animation to play</td>
	</tr>
	<tr>
		<td>GetStompFallBaseAnimation</td>
		<td>Get the base stomp fall animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The stomp fall animation to play</td>
	</tr>
	<tr>
		<td>GetStompLandBaseAnimation</td>
		<td>Get the base stomp land animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The stomp land animation to play</td>
	</tr>
	<tr>
		<td>GetSlideStartBaseAnimation</td>
		<td>Get the base slide start animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The slide start animation to play</td>
	</tr>
	<tr>
		<td>GetSlideEndBaseAnimation</td>
		<td>Get the base slide end animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The slide end animation to play</td>
	</tr>
	<tr>
		<td>GetSlideLoopBaseAnimation</td>
		<td>Get the base slide loop animation</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The slide loop animation to play</td>
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
		<td>GetSprintAnimation</td>
		<td>Get the sprint animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The sprint animation to play</td>
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
	<tr>
		<td>GetCrouchStartAnimation</td>
		<td>Get the crouch start animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The crouch start animation to play</td>
	</tr>
	<tr>
		<td>GetCrouchEndAnimation</td>
		<td>Get the crouch end animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The crouch end animation to play</td>
	</tr>
	<tr>
		<td>GetCrouchIdleAnimation</td>
		<td>Get the crouch idle animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The crouch idle animation to play</td>
	</tr>
	<tr>
		<td>GetCrouchWalkAnimation</td>
		<td>Get the crouch walk animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The crouch walk animation to play</td>
	</tr>
	<tr>
		<td>GetProneStartAnimation</td>
		<td>Get the prone start animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The prone start animation to play</td>
	</tr>
	<tr>
		<td>GetProneEndAnimation</td>
		<td>Get the prone end animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The prone end animation to play</td>
	</tr>
	<tr>
		<td>GetProneIdleAnimation</td>
		<td>Get the prone idle animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The prone idle animation to play</td>
	</tr>
	<tr>
		<td>GetProneMoveAnimation</td>
		<td>Get the prone walk animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The prone walk animation to play</td>
	</tr>
	<tr>
		<td>GetStompStartAnimation</td>
		<td>Get the stomp start animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The stomp start animation to play</td>
	</tr>
	<tr>
		<td>GetStompFallAnimation</td>
		<td>Get the stomp fall animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The stomp fall animation to play</td>
	</tr>
	<tr>
		<td>GetStompLandAnimation</td>
		<td>Get the stomp fall animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The stomp fall animation to play</td>
	</tr>
	<tr>
		<td>GetSlideStartAnimation</td>
		<td>Get the slide start animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The slide start animation to play</td>
	</tr>
	<tr>
		<td>GetSlideEndAnimation</td>
		<td>Get the slide end animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The slide end animation to play</td>
	</tr>
	<tr>
		<td>GetSlideLoopAnimation</td>
		<td>Get the slide loop animation based on the current armed state</td>
		<td></td>
		<td><strong>UAnimSequence*</strong><br/>The slide loop animation to play</td>
	</tr>
</table>

## Blueprint Usage
You can use this template by creating your own animation blueprint and selecting <code>UPlatformerAnimationInstance</code> as the parent class. Set your animations and use this for your characters