# Ultimate Starter Kit
The Ultimate Starter Kit plugin to speed up development of Unreal Engine games

## Requirements
The Ultimate Starter Kit plugin is only available for Unreal Engine 4.27 and newer. The plugin also depends on the following plugins:
<ol>
    <li>Niagara</li>
    <li>Enchanced Input</li>
</ol>

## Installation
<ol>
    <li>Download the latest release from <a href="https://github.com/hfjooste/UltimateStarterKit/releases" target="_blank">GitHub</a></li>
    <li>Navigate to <code>C:\Program Files\Epic Games\UE_{VERSION}\Engine\Plugins</code></li>
    <li>Create a <code>Marketplace</code> folder if needed</li>
    <li>Extract the release and copy to the <code>Marketplace</code> folder</li>
    <li>Open Unreal Engine</li>
    <li>Click on <code>Edit > Plugins</code></li>
    <li>Enable the plugin under the <code>Built-in > Other</code> category</li>
    <li>Restart Unreal Engine</li>
</ol>

## Features
The Ultimate Starter Kit plugin comes with the following features:
<ul>
    <li><strong>Logger</strong>: A system used to easily log info to file and via on-screen messages</li>
    <li><strong>Save data management</strong>: A system used to easily save/load game data with support for multiple save slots</li>
    <li><strong>Settings</strong>: A full settings system including both the UI and save/load logic</li>
    <li><strong>Input Indicators</strong>: A system used to easily detect different input devices and update the UI to display the correct indicators</li>
    <li><strong>Currency</strong>: A system that is used to easily manage different types of currency</li>
    <li><strong>Audio</strong>: A system used to manage the basic properties of audio files</li>
    <li><strong>Stats</strong>: A system used to easily manage character stats with an optional regenerate ability</li>
    <li><strong>3D platformer character</strong>: Basic 3D platformer character and animation template</li>
    <li><strong>Menu system</strong>: A customizable menu system with support for controllers and complex menu layouts</li>
    <li><strong>Config Utils</strong>: Extract information from different config files</li>
    <li><strong>Platform Utils</strong>: Easily detect different platform types and architectures</li>
    <li><strong>Project Utils</strong>: Extract project information like name, description and version</li>
</ul>

## Documentation
- The full documentation is available <a href="https://hfjooste.github.io/UltimateStarterKit" target="_blank">here</a>
- The Markdown documentation is also included in the repo under the <code>docs</code> directory for offline use. Or checkout the <code>docs</code> branch for the full HTML documentation
- Each release contains the full HTML documentation and a PDF for that specific version
- Each function is fully documented in the C++ source code
- The demo project contains an example of each system in Blueprints

## Roadmap
I'm planning on expanding this plugin and adding a bunch of new features. This includes:
- Settings system with save data integration
- Inventory management
- Basic dialogue system

## Credits
<ul>
    <li><a href="https://www.behance.net/pravdin" target="_blank">Comic Helvetic Font by Alexander Pravdin</a></li>
    <li><a href="https://freesound.org/people/broumbroum/" target="_blank">Menu Sound Effects by Broumbroum</a></li>
    <li><a href="https://freesound.org/people/felixyadomi/" target="_blank">Land & Jump Sound Effects by Felixyadomi</a></li>
    <li><a href="https://freesound.org/people/Scrampunk/" target="_blank">Item Sound Effects by Scrampunk</a></li>
    <li><a href="https://inaudio.org" target="_blank">Music by InAudio</a></li>
</ul>

## Support
If you have any questions, feel free to contact me through <a href="https://mastodon.gamedev.place/@hfjooste" target="_blank">Mastodon</a> or <a href="https://twitter.com/hfjooste" target="_blank">Twitter</a>. You can also send me an email at <a href="mailto:henryjooste95@gmail.com">henryjooste95@gmail.com</a>. The Discussions or Issues tab on GitHub can also be used to discuss problems/features or report any issues