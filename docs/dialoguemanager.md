## Introduction
The pawn responsible for managing the dialogue

## Dependencies
The <code>DialogueManager</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Components
The <code>DialogueManager</code> uses the following components:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>AudioComponent</td>
		<td>The audio component responsible for playing the audio files of the dialogue entries</td>
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
		<td>Dialogue</td>
		<td>The dialogue that should be played by the dialogue manager</td>
		<td>UDialogue*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>DialogueWidgetClass</td>
		<td>The class of the widget used to display the dialogue</td>
		<td>TSubclassOf&lt;UDialogueWidget&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>PlayOnStart</td>
		<td>A boolean value indicating if the dialogue should automatically play when the level is started</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>InputMappingContext</td>
		<td>The input mapping context used to interact with the dialogue</td>
		<td>UInputMappingContext*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>SkipAction</td>
		<td>The input action used to skip the current dialogue entry</td>
		<td>UInputAction*</td>
		<td><code>nullptr</code></td>
	</tr>
</table>

### Events
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Params</th>
	</tr>
	<tr>
		<td>OnDialogueEnded</td>
		<td>Event used to notify other classes when the dialogue has ended</td>
		<td><strong>LastEntryId (FName)</strong><br/>The ID of the last entry in the dialogue</td>
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
		<td>PlayDialogue</td>
		<td>Play the dialogue</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>SkipEntry</td>
		<td>Skip the current entry in the dialogue</td>
		<td></td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>DialogueManager</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Dialogue > Play Dialogue</li>
	<li>Ultimate Starter Kit > Dialogue > Skip Entry</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>DialogueManager</code> can now be used in any of your C++ files:
```c++
#include "USK/Dialogue/DialogueManager.h"

void ATestActor::Test()
{
	// DialogueManager is a pointer to the ADialogueManager
	DialogueManager->PlayDialogue();
	DialogueManager->SkipEntry();
}
```
