## Introduction
The crosshair configuration data asset

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
		<td>bDisplayCenterImage</td>
		<td>Should the center image be displayed?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>CenterImage</td>
		<td>The image to display in the center of the crosshair</td>
		<td>UTexture2D*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CenterColor</td>
		<td>The color of the center image</td>
		<td>FLinearColor</td>
		<td>FLinearColor::White</td>
	</tr>
	<tr>
		<td>bDisplayCenterShadow</td>
		<td>Should a shadow be displayed behind the center image?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>CenterShadowColor</td>
		<td>The color of the shadow behind the center image</td>
		<td>FLinearColor</td>
		<td>FLinearColor::Black</td>
	</tr>
	<tr>
		<td>CenterShadowScale</td>
		<td>The scale of the shadow behind the center image</td>
		<td>float</td>
		<td>1.15f</td>
	</tr>
	<tr>
		<td>Rotation</td>
		<td>The rotation applied to the sides of the crosshair</td>
		<td>float</td>
		<td></td>
	</tr>
	<tr>
		<td>SpreadBlendSpeed</td>
		<td>The blend speed used when updating the spread of the crosshair</td>
		<td>float</td>
		<td>10.0f</td>
	</tr>
	<tr>
		<td>bUseGlobalColor</td>
		<td>Should a global color be used for the sides of the crosshair?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>GlobalColor</td>
		<td>The global color used for the sides of the crosshair</td>
		<td>FLinearColor</td>
		<td>FLinearColor::White</td>
	</tr>
	<tr>
		<td>bDisplayTop</td>
		<td>Should the top side of the crosshair be displayed?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>TopColor</td>
		<td>The color of the top side of the crosshair</td>
		<td>FLinearColor</td>
		<td>FLinearColor::White</td>
	</tr>
	<tr>
		<td>TopLength</td>
		<td>The length of the top side of the crosshair</td>
		<td>float</td>
		<td>20.0f</td>
	</tr>
	<tr>
		<td>TopThickness</td>
		<td>The thickness of the top side of the crosshair</td>
		<td>float</td>
		<td>4.0f</td>
	</tr>
	<tr>
		<td>TopSpread</td>
		<td>The spread of the top side of the crosshair</td>
		<td>float</td>
		<td>50.0f</td>
	</tr>
	<tr>
		<td>TopOffset</td>
		<td>The offset of the top side of the crosshair</td>
		<td>float</td>
		<td>10.0f</td>
	</tr>
	<tr>
		<td>bDisplayTopShadow</td>
		<td>Should a shadow be displayed behind the top side of the crosshair?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>TopShadowColor</td>
		<td>The color of the shadow behind the top side of the crosshair</td>
		<td>FLinearColor</td>
		<td>FLinearColor::Black</td>
	</tr>
	<tr>
		<td>TopShadowScale</td>
		<td>The scale of the shadow behind the top side of the crosshair</td>
		<td>float</td>
		<td>1.15f</td>
	</tr>
	<tr>
		<td>bDisplayBottom</td>
		<td>Should the bottom side of the crosshair be displayed?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>BottomColor</td>
		<td>The color of the bottom side of the crosshair</td>
		<td>FLinearColor</td>
		<td>FLinearColor::White</td>
	</tr>
	<tr>
		<td>BottomLength</td>
		<td>The length of the bottom side of the crosshair</td>
		<td>float</td>
		<td>20.0f</td>
	</tr>
	<tr>
		<td>BottomThickness</td>
		<td>The thickness of the bottom side of the crosshair</td>
		<td>float</td>
		<td>4.0f</td>
	</tr>
	<tr>
		<td>BottomSpread</td>
		<td>The spread of the bottom side of the crosshair</td>
		<td>float</td>
		<td>50.0f</td>
	</tr>
	<tr>
		<td>BottomOffset</td>
		<td>The offset of the bottom side of the crosshair</td>
		<td>float</td>
		<td>10.0f</td>
	</tr>
	<tr>
		<td>bDisplayBottomShadow</td>
		<td>Should a shadow be displayed behind the bottom side of the crosshair?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>BottomShadowColor</td>
		<td>The color of the shadow behind the bottom side of the crosshair</td>
		<td>FLinearColor</td>
		<td>FLinearColor::Black</td>
	</tr>
	<tr>
		<td>BottomShadowScale</td>
		<td>The scale of the shadow behind the bottom side of the crosshair</td>
		<td>float</td>
		<td>1.15f</td>
	</tr>
	<tr>
		<td>bDisplayLeft</td>
		<td>Should the left side of the crosshair be displayed?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>LeftColor</td>
		<td>The color of the left side of the crosshair</td>
		<td>FLinearColor</td>
		<td>FLinearColor::White</td>
	</tr>
	<tr>
		<td>LeftLength</td>
		<td>The length of the left side of the crosshair</td>
		<td>float</td>
		<td>20.0f</td>
	</tr>
	<tr>
		<td>LeftThickness</td>
		<td>The thickness of the left side of the crosshair</td>
		<td>float</td>
		<td>4.0f</td>
	</tr>
	<tr>
		<td>LeftSpread</td>
		<td>The spread of the left side of the crosshair</td>
		<td>float</td>
		<td>50.0f</td>
	</tr>
	<tr>
		<td>LeftOffset</td>
		<td>The offset of the left side of the crosshair</td>
		<td>float</td>
		<td>10.0f</td>
	</tr>
	<tr>
		<td>bDisplayLeftShadow</td>
		<td>Should a shadow be displayed behind the left side of the crosshair?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>LeftShadowColor</td>
		<td>The color of the shadow behind the left side of the crosshair</td>
		<td>FLinearColor</td>
		<td>FLinearColor::Black</td>
	</tr>
	<tr>
		<td>LeftShadowScale</td>
		<td>The scale of the shadow behind the left side of the crosshair</td>
		<td>float</td>
		<td>1.15f</td>
	</tr>
	<tr>
		<td>bDisplayRight</td>
		<td>Should the right side of the crosshair be displayed?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>RightColor</td>
		<td>The color of the right side of the crosshair</td>
		<td>FLinearColor</td>
		<td></td>
	</tr>
	<tr>
		<td>RightLength</td>
		<td>The length of the right side of the crosshair</td>
		<td>float</td>
		<td>20.0f</td>
	</tr>
	<tr>
		<td>RightThickness</td>
		<td>The thickness of the right side of the crosshair</td>
		<td>float</td>
		<td>4.0f</td>
	</tr>
	<tr>
		<td>RightSpread</td>
		<td>The spread of the right side of the crosshair</td>
		<td>float</td>
		<td>50.0f</td>
	</tr>
	<tr>
		<td>RightOffset</td>
		<td>The offset of the right side of the crosshair</td>
		<td>float</td>
		<td>10.0f</td>
	</tr>
	<tr>
		<td>bDisplayRightShadow</td>
		<td>Should a shadow be displayed behind the right side of the crosshair?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>RightShadowColor</td>
		<td>The color of the shadow behind the right side of the crosshair</td>
		<td>FLinearColor</td>
		<td>FLinearColor::Black</td>
	</tr>
	<tr>
		<td>RightShadowScale</td>
		<td>The scale of the shadow behind the right side of the crosshair</td>
		<td>float</td>
		<td>1.15f</td>
	</tr>
</table>
