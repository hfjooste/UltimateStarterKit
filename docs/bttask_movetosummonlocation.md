## Introduction
Behaviour tree task node used to make the enemy character move towards the summon location

## Dependencies
The <code>BTTask_UskMoveToSummonLocation</code> relies on other components of this plugin to work:
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
		<td>SummonLocationKey</td>
		<td>The blackboard key used to store the summon location</td>
		<td>FBlackboardKeySelector</td>
		<td></td>
	</tr>
	<tr>
		<td>AcceptanceRadius</td>
		<td>The radius around the point that the character must reach to consider the point reached</td>
		<td>float</td>
		<td>500.0f</td>
	</tr>
	<tr>
		<td>FocusLocationRadius</td>
		<td>The radius around the point where the character will start focusing the location</td>
		<td>float</td>
		<td>700.0f</td>
	</tr>
</table>
