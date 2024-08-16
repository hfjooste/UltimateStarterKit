## Introduction
Behaviour tree task node used to make the enemy character chase the target actor while flying

## Dependencies
The <code>BTTask_UskFlyChaseTarget</code> relies on other components of this plugin to work:
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
		<td>OwnerKey</td>
		<td>The blackboard key used to store the owner</td>
		<td>FBlackboardKeySelector</td>
		<td></td>
	</tr>
	<tr>
		<td>TargetLocationKey</td>
		<td>The blackboard key used to store the target location</td>
		<td>FBlackboardKeySelector</td>
		<td></td>
	</tr>
	<tr>
		<td>GridIndexMin</td>
		<td>The minimum index of the grid used to find possible locations</td>
		<td>int</td>
		<td>-1</td>
	</tr>
	<tr>
		<td>GridIndexMax</td>
		<td>The maximum index of the grid used to find possible locations</td>
		<td>int</td>
		<td>1</td>
	</tr>
	<tr>
		<td>GridBlockSize</td>
		<td>The size of each block in the grid used to find possible locations</td>
		<td>float</td>
		<td>50.0f</td>
	</tr>
	<tr>
		<td>MinDistanceFromGround</td>
		<td>The minimum distance from the ground that the enemy character should maintain</td>
		<td>float</td>
		<td>500.0f</td>
	</tr>
	<tr>
		<td>bResetVelocityWhenTargetLost</td>
		<td>Should the velocity of the enemy character be reset when the target is lost?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>VelocityUpdateInterpSpeed</td>
		<td>The speed at which the velocity of the enemy character should be updated</td>
		<td>float</td>
		<td>10.0f</td>
	</tr>
	<tr>
		<td>ObstacleObjectTypes</td>
		<td>The object types that are considered obstacles</td>
		<td>TArray&lt;TEnumAsByte&lt;EObjectTypeQuery&gt;&gt;</td>
		<td></td>
	</tr>
</table>
