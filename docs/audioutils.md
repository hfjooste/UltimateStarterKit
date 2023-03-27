## Introduction
The audio utils class is used to easily play sound effects

## Dependencies
The <code>AudioUtils</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## API Reference
### Functions
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Params</th>
		<th>Return</th>
	</tr>
	<tr>
		<td>PlaySound2D</td>
		<td>Play a 2D sound</td>
		<td><strong>WorldContext (const UObject*)</strong><br/>The top level object representing a map<br/><br/><strong>SoundFX (USoundBase*)</strong><br/>The USoundBase to play</td>
		<td></td>
	</tr>
	<tr>
		<td>PlayRandomSound2D</td>
		<td>Play a random 2D sound</td>
		<td><strong>WorldContext (const UObject*)</strong><br/>The top level object representing a map<br/><br/><strong>SoundFX (TArray<USoundBase*>)</strong><br/>The array of USoundBase to select the random sound from</td>
		<td></td>
	</tr>
	<tr>
		<td>PlaySound</td>
		<td>Play a sound at the specified actor's location</td>
		<td><strong>Actor (AActor*)</strong><br/>The actor where the sound will be played<br/><br/><strong>SoundFX (USoundBase*)</strong><br/>The USoundBase to play</td>
		<td></td>
	</tr>
	<tr>
		<td>PlayRandomSound</td>
		<td>Play a random sound at the specified actor's location</td>
		<td><strong>Actor (AActor*)</strong><br/>The actor where the sound will be played<br/><br/><strong>SoundFX (TArray<USoundBase*>)</strong><br/>The array of USoundBase to select the random sound from</td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>AudioUtils</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Audio > Play Sound2D</li>
	<li>Ultimate Starter Kit > Audio > Play Random Sound2D</li>
	<li>Ultimate Starter Kit > Audio > Play Sound</li>
	<li>Ultimate Starter Kit > Audio > Play Random Sound</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>AudioUtils</code> can now be used in any of your C++ files:
```c++
#include "USK/Audio/AudioUtils.h"

void ATestActor::Test()
{
	UAudioUtils::PlaySound2D(WorldContext, SoundFX);
	UAudioUtils::PlayRandomSound2D(WorldContext, SoundFX);
	UAudioUtils::PlaySound(Actor, SoundFX);
	UAudioUtils::PlayRandomSound(Actor, SoundFX);
}
```
