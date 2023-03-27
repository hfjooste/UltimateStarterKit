## Introduction
All trackable data use the FTrackableData struct to specify the default values and behaviours

## Properties
<table>
	<tr>
		<th>Property</th>
		<th>Description</th>
		<th>Type</th>
		<th>Default Value</th>
	</tr>
	<tr>
		<td>InitialValue</td>
		<td>The initial value of the data</td>
		<td>float</td>
		<td></td>
	</tr>
	<tr>
		<td>EnforceMaxValue</td>
		<td>Should we enforce a maximum value?</td>
		<td>bool</td>
		<td></td>
	</tr>
	<tr>
		<td>MaxValue</td>
		<td>The maximum value of the data</td>
		<td>float</td>
		<td>100.0f</td>
	</tr>
	<tr>
		<td>AutoSave</td>
		<td>Should all value updates automatically be saved using the game instance?</td>
		<td>bool</td>
		<td></td>
	</tr>
	<tr>
		<td>AutoGenerate</td>
		<td>Should we automatically generate value every second?</td>
		<td>bool</td>
		<td></td>
	</tr>
	<tr>
		<td>GenerateAmount</td>
		<td>The amount of value to generate every second</td>
		<td>float</td>
		<td></td>
	</tr>
	<tr>
		<td>GenerateDelay</td>
		<td>The delay before the value starts generating after losing value</td>
		<td>float</td>
		<td></td>
	</tr>
</table>
