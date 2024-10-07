## Introduction
Behaviour tree task node used to make the enemy start dodging

## Dependencies
The <code>BTTask_UskDodge</code> relies on other components of this plugin to work:
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
		<td>QueuedDodgeKey</td>
		<td>The blackboard key used to store the queued dodge state</td>
		<td>FBlackboardKeySelector</td>
		<td></td>
	</tr>
	<tr>
		<td>QueuedDodgeConfigNameKey</td>
		<td>The blackboard key used to store the queued dodge config name</td>
		<td>FBlackboardKeySelector</td>
		<td></td>
	</tr>
	<tr>
		<td>DodgeConfig</td>
		<td>The dodge configurations used by the enemy</td>
		<td>TMap&lt;FName, FDodgeConfig&gt;</td>
		<td></td>
	</tr>
</table>
