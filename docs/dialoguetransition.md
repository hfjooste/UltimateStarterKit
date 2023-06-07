## Introduction
A transition from one dialogue entry to the next

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
		<td>Text</td>
		<td>The text displayed for this transition (choice)</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>StartEntry</td>
		<td>The dialogue entry where the transition starts</td>
		<td>UDialogueEntry*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>EndEntry</td>
		<td>The dialogue entry where the transition ends</td>
		<td>UDialogueEntry*</td>
		<td><code>nullptr</code></td>
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
		<td>OnMarkedForDeletion</td>
		<td>Event used to notify other classes that the transition is marked for deletion</td>
		<td></td>
	</tr>
</table>
