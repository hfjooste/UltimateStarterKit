## Introduction
A widget used to display the current framerate

## Dependencies
The <code>FpsCounter</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
	<li><a href="../gameinstance">Game Instance</a>: Used to monitor for input device changes and handle saving/loading game data</li>
</ul>

## Required Widgets
There is already a <code>FpsCounter_Implementation</code> that you can use in your projects. But if you create your own instance of this widget, you need to add the following before you can compile:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>SimpleViewContainer</td>
		<td>Container for the simple view</td>
		<td>UCanvasPanel*</td>
	</tr>
	<tr>
		<td>DetailedViewContainer</td>
		<td>Container for the detailed view</td>
		<td>UCanvasPanel*</td>
	</tr>
	<tr>
		<td>FramerateSimpleText</td>
		<td>The text block used to display the framerate in the simple view</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>FramerateText</td>
		<td>The text block used to display the framerate</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>MinText</td>
		<td>The text block used to display the min framerate</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>MaxText</td>
		<td>The text block used to display the max framerate</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>AverageText</td>
		<td>The text block used to display the average framerate</td>
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
		<td>MeasureTime</td>
		<td>The amount of seconds to measure the FPS before removing old measurements</td>
		<td>int</td>
		<td>120</td>
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

### Functions
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Params</th>
		<th>Return</th>
	</tr>
	<tr>
		<td>UpdateVisibility</td>
		<td>Update the visibility of the widget</td>
		<td><strong>IsVisible (bool)</strong><br/>Is the widget visible?</td>
		<td></td>
	</tr>
	<tr>
		<td>LoadSettings</td>
		<td>Load and apply the FPS counter settings</td>
		<td></td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>FpsCounter</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > UI > Update Visibility</li>
	<li>Ultimate Starter Kit > UI > Load Settings</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>FpsCounter</code> can now be used in any of your C++ files:
```c++
#include "USK/Widgets/FpsCounter.h"

void ATestActor::Test()
{
	// FpsCounter is a pointer to the UFpsCounter
	FpsCounter->UpdateVisibility(IsVisible);
	FpsCounter->LoadSettings();
}
```
