## Introduction
Behaviour tree task node used to pause the AI

## Dependencies
The <code>BTTask_UskPauseAi</code> relies on other components of this plugin to work:
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
		<td>PauseDelayKey</td>
		<td>The blackboard key used to store the pause delay</td>
		<td>FBlackboardKeySelector</td>
		<td></td>
	</tr>
	<tr>
		<td>Delay</td>
		<td>The new pause delay</td>
		<td>float</td>
		<td>3.0f</td>
	</tr>
</table>
