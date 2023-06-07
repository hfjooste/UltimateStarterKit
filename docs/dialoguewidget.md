## Introduction
Widget used to display a dialogue

## Dependencies
The <code>DialogueTransitionType</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Required Widgets
You need to add the following before you can compile the <code>DialogueTransitionType</code> widget:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>DialogueTitle</td>
		<td>The text block used to display the dialogue title</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>DialogueText</td>
		<td>The text block used to display the dialogue text</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>ChoiceMenu</td>
		<td>The menu used to display the dialogue choices</td>
		<td>UMenu*</td>
	</tr>
</table>

## Optional Widgets
You can add the following widgets to enable extra functionality:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>SkipEntryImage</td>
		<td>The image displayed when the dialogue entry is completed</td>
		<td>UImage*</td>
	</tr>
</table>

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
		<td>ChoiceMenuItemClass</td>
		<td>The class for all choice menu items</td>
		<td>TSubclassOf&lt;UMenuItem&gt;</td>
		<td></td>
	</tr>
</table>

### Events
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Params</th>
	</tr>
	<tr>
		<td>OnChoiceSelected</td>
		<td>Event used to notify other classes when a choice is selected</td>
		<td><strong>Index (int)</strong><br/>The index of the choice that was selected</td>
	</tr>
</table>
