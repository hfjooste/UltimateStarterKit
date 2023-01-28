## Introduction
The music player can be used to play, pause and stop music. It also allows you to easily adjust the volume of the music

## API Reference
### Components
<table>
    <tr>
        <th>Name</th>
        <th>Type</th>
        <th>Description</th>
    </tr>
    <tr>
        <td>AudioPlayer</td>
        <td>UAudioComponent*</td>
        <td>The audio player component is responsible for the music playback</td>
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
        <td>Adjust the playback volume of the music </td>
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
You can play sounds using Blueprints by adding one of the following nodes (requires a reference to a <code>Music Player</code> actor):
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

The currency system can now be used in any of your C++ files:
```c++
#include "USK/Audio/MusicPlayer.h"

void ATestActor::Test()
{
    // MusicPlayer is a pointer to a Music Player actor
    MusicPlayer->SetVolume(2.0f);
    MusicPlayer->Pause();
    MusicPlayer->Play();
    MusicPlayer->Stop();
}
```