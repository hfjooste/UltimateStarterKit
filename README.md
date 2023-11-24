# Ultimate Starter Kit
<p>
    <img alt="Stars" src="https://img.shields.io/github/stars/hfjooste/UltimateStarterKit" />
    <img alt="Downloads" src="https://img.shields.io/github/downloads/hfjooste/UltimateStarterKit/total" />
    <img alt="Contributors" src="https://img.shields.io/github/contributors/hfjooste/UltimateStarterKit" />
    <img alt="Issues" src="https://img.shields.io/github/issues/hfjooste/UltimateStarterKit" />
</p>
The Ultimate Starter Kit plugin to speed up development of Unreal Engine games

## 📝 Requirements
<i><strong>This plugin was only tested on Windows. It might not work as expected on Linux/MacOS</strong></i><br/><br/>
The Ultimate Starter Kit plugin is only available for Unreal Engine 4.27 and newer. The plugin also depends on the following plugins:
<ol>
    <li>Niagara</li>
    <li>Enhanced Input</li>
</ol>

## 🛠️ Installation
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

## 🚀 Features
The Ultimate Starter Kit plugin comes with the following features:
<ul>
    <li><strong>Logger</strong>: A system used to easily log info to file and via on-screen messages</li>
    <li><strong>Save data management</strong>: A system used to easily save/load game data with support for multiple save slots</li>
    <li><strong>Settings</strong>: A full settings system including both the UI and save/load logic</li>
    <li><strong>Dialogue System</strong>: A full dialogue system with support for different participants, choices, and branches</li>
    <li><strong>Inventory Management</strong>: Manage multiple inventories with save data integration</li>
    <li><strong>Input Indicators</strong>: A system used to easily detect different input devices and update the UI to display the correct indicators</li>
    <li><strong>Currency</strong>: A system that is used to easily manage different types of currency</li>
    <li><strong>Audio</strong>: A system used to manage the basic properties of audio files</li>
    <li><strong>Stats</strong>: A system used to easily manage character stats with an optional regenerate ability</li>
    <li><strong>Characters</strong>: Character controllers with lots of features
        <ul>
            <li>First and Third person characters</li>
            <li>True FPS with a single full body mesh</li>
            <li>Switch between different camera perspectives at runtime</li>
            <li>Shadow decals to make platforming easier</li>
            <li>Sprinting with stamina support</li>
            <li>Double jumping</li>
            <li>Variable jump height</li>
            <li>Coyote time</li>
            <li>Smooth crouching with crouch jumping</li>
            <li>Stomping with stomp jumping</li>
            <li>Leaning with procedural animations</li>
            <li>Sliding with long jump</li>
        </ul>
    </li>
    <li><strong>Character Animation Blueprint</strong>: Base animation blueprint for all USK characters
        <ul>
            <li>Upper/Lower body animation blending</li>
            <li>Procedural leaning animations</li>
            <li>Supports animations for 3 different armed states with aiming animations</li>
        </ul>
    </li>
    <li><strong>Weapons System</strong>: A customizable weapon system with support for recoil, multiple fire types, aiming, fire rates, ammo, reloading, and projectile types</li>
    <li><strong>Menu system</strong>: A customizable menu system with support for controllers and complex menu layouts</li>
    <li><strong>Interact system</strong>: A customizable interaction system with interact prompts</li>
    <li><strong>Quest system</strong>: A quest system with support for multiple quest points</li>
    <li><strong>Config Utils</strong>: Extract information from different config files</li>
    <li><strong>Platform Utils</strong>: Easily detect different platform types and architectures</li>
    <li><strong>Project Utils</strong>: Extract project information like name, description, and version</li>
</ul>

## 📜 Documentation
- The full documentation is available <a href="https://hfjooste.github.io/UltimateStarterKit" target="_blank">here</a>
- The Markdown documentation is also included in the repo under the <code>docs</code> directory for offline use. Or checkout the <code>docs</code> branch for the full HTML documentation
- Each release contains the full HTML documentation and a PDF for that specific version
- Each function is fully documented in the C++ source code
- The demo project contains an example of each system in Blueprints

## ❤️ Credits
<ul>
    <li><a href="https://github.com/jinyuliao/GenericGraph" target="_blank">Generic Graph by jinyuliao</a></li>
    <li><a href="https://www.behance.net/pravdin" target="_blank">Comic Helvetic Font by Alexander Pravdin</a></li>
    <li><a href="https://freesound.org/people/broumbroum/" target="_blank">Menu Sound Effects by Broumbroum</a></li>
    <li><a href="https://freesound.org/people/felixyadomi/" target="_blank">Land & Jump Sound Effects by Felixyadomi</a></li>
    <li><a href="https://freesound.org/people/Scrampunk/" target="_blank">Item Sound Effects by Scrampunk</a></li>
    <li><a href="https://freesound.org/people/Aquafeniz/" target="_blank">Slide Sound Effects by Aquafeniz</a></li>
    <li><a href="https://inaudio.org" target="_blank">Music by InAudio</a></li>
</ul>

## 💻 Contribution Guidelines

If you would like to contribute to the Ultimate Starter Kit, please follow our [Contribution Guidelines](./Contribution.md). These guidelines provide detailed information on how to create branches, make changes, test, document, commit, and open pull requests. 
We welcome contributions from the community and look forward to your valuable input.

## ℹ️ Support
If you have any questions, feel free to contact me through <a href="https://mastodon.gamedev.place/@hfjooste" target="_blank">Mastodon</a> or <a href="https://twitter.com/hfjooste" target="_blank">Twitter</a>. You can also send me an email at <a href="mailto:henryjooste95@gmail.com">henryjooste95@gmail.com</a>. The Discussions or Issues tab on GitHub can also be used to discuss problems/features or report any issues
