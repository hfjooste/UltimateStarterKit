## Introduction
A system used to manage the basic properties of audio files. It includes different sound classes, a sound mix and sound attenuation settings

## Dependencies
The audio system relies on other components of this plugin to work:
<ul>
    <li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Sound Classes
The audio system includes a few basic preconfigured sound classes:
<table>
    <tr>
        <th>Class name</th>
        <th>Group</th>
        <th>Volume</th>
    </tr>
    <tr>
        <td>USK_EffectsSoundClass</td>
        <td>Effects</td>
        <td>1.0</td>
    </tr>
    <tr>
        <td>USK_MusicSoundClass</td>
        <td>Music</td>
        <td>0.5</td>
    </tr>
    <tr>
        <td>USK_UISoundClass</td>
        <td>UI</td>
        <td>1.0</td>
    </tr>
    <tr>
        <td>USK_VoiceSoundClass</td>
        <td>Voice</td>
        <td>3.0</td>
    </tr>
</table>