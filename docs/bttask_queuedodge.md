## Introduction
Behaviour tree task node used to queue a dodge

## Dependencies
The <code>BTTask_UskQueueDodge</code> relies on other components of this plugin to work:
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
		<td>DodgeConfigName</td>
		<td>The name of the dodge configurations to queue</td>
		<td>FName</td>
		<td></td>
	</tr>
</table>
