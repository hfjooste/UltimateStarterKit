## Introduction
Behaviour tree task node used to make the enemy summon other enemies

## Dependencies
The <code>BTTask_UskSummonEnemy</code> relies on other components of this plugin to work:
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
		<td>SummonDelayKey</td>
		<td>The blackboard key used to store the summon delay</td>
		<td>FBlackboardKeySelector</td>
		<td></td>
	</tr>
	<tr>
		<td>SummonLocationKey</td>
		<td>The blackboard key used to store the summon location</td>
		<td>FBlackboardKeySelector</td>
		<td></td>
	</tr>
</table>
