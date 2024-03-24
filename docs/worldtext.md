## Introduction
Actor used to display text in the world

## Components
The <code>WorldText</code> uses the following components:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>Container</td>
		<td>Actor used to display text in the world</td>
		<td>USceneComponent*</td>
	</tr>
	<tr>
		<td>TriggerComponent</td>
		<td>The trigger used to activate the text</td>
		<td>UBoxComponent*</td>
	</tr>
	<tr>
		<td>TextWidgetComponent</td>
		<td>The text widget responsible for displaying the text</td>
		<td>UWidgetComponent*</td>
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
		<td>WordWidgetClass</td>
		<td>The class used to create the word widget</td>
		<td>TSubclassOf&lt;UWorldTextWordWidget&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>LetterWidgetClass</td>
		<td>The class used to create the letter widget</td>
		<td>TSubclassOf&lt;UWorldTextLetterWidget&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>bIsDisabled</td>
		<td>Is the trigger disabled?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>Text</td>
		<td>The text that should be displayed</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>Sound</td>
		<td>The sound to play when activating the text</td>
		<td>USoundBase*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>bPlaySoundAtActor</td>
		<td>Should the audio be played at the actor's location?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>ActivateOnDestroy</td>
		<td>An array of world text actors to activate when this text actor is destroyed</td>
		<td>TArray&lt;AWorldText*&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>EnableOnDestroy</td>
		<td>An array of world text actors to enable when this text actor is destroyed</td>
		<td>TArray&lt;AWorldText*&gt;</td>
		<td></td>
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
		<td>Activate</td>
		<td>Activate the text</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>CanActorTriggerText</td>
		<td>Can the actor trigger the text?</td>
		<td><strong>Actor (AActor*)</strong><br/>The actor to check</td>
		<td><strong>bool</strong><br/>A boolean value indicating if the actor can trigger the text</td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>WorldText</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Narrative > Activate</li>
	<li>Ultimate Starter Kit > Narrative > Can Actor Trigger Text</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>WorldText</code> can now be used in any of your C++ files:
```c++
#include "USK/Narrative/WorldText.h"

void ATestActor::Test()
{
	// WorldText is a pointer to the AWorldText
	WorldText->Activate();
	bool CanActorTriggerTextValue = WorldText->CanActorTriggerText(Actor);
}
```
