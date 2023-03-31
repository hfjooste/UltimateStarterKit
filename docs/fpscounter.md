## Introduction
A widget used to display the current framerate

## Required Widgets
There is already a <code>FpsCounter_Implementation</code> that you can use in your projects. But if you create your own instance of this widget, you need to add the following before you can compile:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>FramerateText</td>
		<td>The text block used to display the framerate</td>
		<td>UTextBlock*</td>
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
		<td>UpdateDelay</td>
		<td>The delay in seconds between each update</td>
		<td>float</td>
		<td>0.125f</td>
	</tr>
	<tr>
		<td>HighFramerate</td>
		<td>A framerate that is considered high and will use the high color</td>
		<td>int</td>
		<td>60</td>
	</tr>
	<tr>
		<td>MediumFramerate</td>
		<td>A framerate that is considered medium and will use the medium color</td>
		<td>int</td>
		<td>30</td>
	</tr>
	<tr>
		<td>HighColor</td>
		<td>The color used to display high framerates</td>
		<td>FLinearColor</td>
		<td>FLinearColor::Green</td>
	</tr>
	<tr>
		<td>MediumColor</td>
		<td>The color used to display medium framerates</td>
		<td>FLinearColor</td>
		<td>FLinearColor::Yellow</td>
	</tr>
	<tr>
		<td>LowColor</td>
		<td>The color used to display low framerates</td>
		<td>FLinearColor</td>
		<td>FLinearColor::Red</td>
	</tr>
</table>
