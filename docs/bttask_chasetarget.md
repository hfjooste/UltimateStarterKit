## Introduction
Behaviour tree task node used to make the enemy character chase the target actor

## Dependencies
The <code>BTTask_UskChaseTarget</code> relies on other components of this plugin to work:
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
</table>
