## Introduction
Decorator used to check if the AI is near the target

## Dependencies
The <code>BTDecorator_UskIsNearTarget</code> relies on other components of this plugin to work:
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
		<td>bCheckZDifference</td>
		<td>A boolean value indicating if the Z difference should be checked</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>MaxDistance</td>
		<td>The maximum distance the AI can be from the target</td>
		<td>float</td>
		<td>500.0f</td>
	</tr>
</table>
