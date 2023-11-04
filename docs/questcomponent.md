## Introduction
Component used to update the actor based on the current quest and point

## Dependencies
The <code>QuestComponent</code> relies on other components of this plugin to work:
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
		<td>Quest</td>
		<td>The quest associated with the component</td>
		<td>UQuest*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>RequiredPoint</td>
		<td>The point of the quest associated with the component</td>
		<td>int</td>
		<td></td>
	</tr>
	<tr>
		<td>bHideIfQuestNotActive</td>
		<td>Should the actor be hidden if the quest is not active?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>bHideAfterPointCompleted</td>
		<td>Should the actor be hidden if the quest point has been completed?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
</table>
