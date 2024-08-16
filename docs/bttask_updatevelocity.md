## Introduction
Behaviour tree task node used to update the velocity of an enemy character

## Dependencies
The <code>BTTask_UskUpdateVelocity</code> relies on other components of this plugin to work:
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
		<td>NewVelocity</td>
		<td>The new velocity of the enemy character</td>
		<td>FVector</td>
		<td></td>
	</tr>
</table>
