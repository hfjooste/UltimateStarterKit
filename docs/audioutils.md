## Introduction
The audio utils class is used to easily play sound effects

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
        <td><strong>SoundFX (USoundBase*)</strong><br/>The USoundBase to play</td>
        <td></td>
    </tr>
    <tr>
        <td>PlayRandomSound2D</td>
        <td>Play a random 2D sound</td>
        <td><strong>SoundFX (TArray&lt;USoundBase*&gt;)</strong><br/>The array of USoundBase to select the random sound from</td>
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
        <td><strong>Actor (AActor*)</strong><br/>The actor where the sound will be played<br/><br/><strong>SoundFX (TArray&lt;USoundBase*&gt;)</strong><br/>The array of USoundBase to select the random sound from</td>
        <td></td>
    </tr>
</table>

## Blueprint Usage
You can play sounds using Blueprints by adding one of the following nodes:
<ul>
    <li>Ultimate Starter Kit > Audio > Play Sound 2D</li>
    <li>Ultimate Starter Kit > Audio > Play Random Sound 2D</li>
    <li>Ultimate Starter Kit > Audio > Play Sound</li>
    <li>Ultimate Starter Kit > Audio > Play Random Sound</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The currency system can now be used in any of your C++ files:
```c++
#include "USK/Audio/AudioUtils.h"

void ATestActor::Test(const UObject* WorldContext)
{
    // SoundFx is a pointer to a USoundBase
    UAudioUtils::PlaySound2D(WorldContext, SoundFx);

    // SoundFxArray is an array of pointers to a USoundBase
    UAudioUtils::PlayRandomSound2D(WorldContext, SoundFxArray);

    // Player is a pointer to an Actor
    // SoundFx is a pointer to a USoundBase
    UAudioUtils::PlaySound(Player, SoundFx);

    // Player is a pointer to an Actor
    // SoundFxArray is an array of pointers to a USoundBase
    UAudioUtils::PlayRandomSound(Player, SoundFx);
}
```