## Introduction
The dynamic crosshair widget

## Dependencies
The <code>DynamicCrosshair</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Required Widgets
There is already a <code>DynamicCrosshair_Implementation</code> that you can use in your projects. But if you create your own instance of this widget, you need to add the following before you can compile:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>CenterImage</td>
		<td>The center image of the crosshair</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>CenterShadowImage</td>
		<td>The center shadow image of the crosshair</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>SidesContainer</td>
		<td>The container used by all the sides</td>
		<td>UCanvasPanel*</td>
	</tr>
	<tr>
		<td>TopContainer</td>
		<td>The top container of the crosshair</td>
		<td>UCanvasPanel*</td>
	</tr>
	<tr>
		<td>TopImage</td>
		<td>The top image of the crosshair</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>TopShadowImage</td>
		<td>The top shadow image of the crosshair</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>BottomContainer</td>
		<td>The bottom container of the crosshair</td>
		<td>UCanvasPanel*</td>
	</tr>
	<tr>
		<td>BottomImage</td>
		<td>The bottom image of the crosshair</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>BottomShadowImage</td>
		<td>The bottom shadow image of the crosshair</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>LeftContainer</td>
		<td>The left container of the crosshair</td>
		<td>UCanvasPanel*</td>
	</tr>
	<tr>
		<td>LeftImage</td>
		<td>The left image of the crosshair</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>LeftShadowImage</td>
		<td>The left shadow image of the crosshair</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>RightContainer</td>
		<td>The right container of the crosshair</td>
		<td>UCanvasPanel*</td>
	</tr>
	<tr>
		<td>RightImage</td>
		<td>The right image of the crosshair</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>RightShadowImage</td>
		<td>The right shadow image of the crosshair</td>
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
</table>
