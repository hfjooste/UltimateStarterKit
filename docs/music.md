## Introduction
Actor responsible for playing, pausing and stopping music. It also allows you to adjust music volume

## Dependencies
The <code>inal</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Components
The <code>inal</code> uses the following components:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>AudioPlayer</td>
		<td>Actor responsible for playing, pausing and stopping music. It also allows you to adjust music volume</td>
		<td>UAudioComponent*</td>
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
		<td>PlayOnStart</td>
		<td>Should the music automatically play when the actor is spawned?</td>
		<td>bool</td>
		<td>true</td>
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
		<td>SetVolume</td>
		<td>Adjust the playback volume of the music</td>
		<td><strong>Volume (float)</strong><br/>The new volume of the music</td>
		<td></td>
	</tr>
	<tr>
		<td>Play</td>
		<td>Play the music</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>Pause</td>
		<td>Pause the music</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>Stop</td>
		<td>Stop the music</td>
		<td></td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>inal</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Audio > Set Volume</li>
	<li>Ultimate Starter Kit > Audio > Play</li>
	<li>Ultimate Starter Kit > Audio > Pause</li>
	<li>Ultimate Starter Kit > Audio > Stop</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>inal</code> can now be used in any of your C++ files:
```c++
#include "USK/Audio/MusicPlayer.h"

void ATestActor::Test()
{
	// inal is a pointer to the final
	inal->SetVolume(Volume);
	inal->Play();
	inal->Pause();
	inal->Stop();
}
```
