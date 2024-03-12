## Introduction
A single entry in a dialogue

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
		<td>Owner</td>
		<td>The owner participant of the dialogue entry</td>
		<td>UDialogueParticipant*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>Transition</td>
		<td>The type of transition for this dialogue entry</td>
		<td>EDialogueTransitionType</td>
		<td></td>
	</tr>
	<tr>
		<td>Id</td>
		<td>The ID of the dialogue entry</td>
		<td>FName</td>
		<td>FNam</td>
	</tr>
	<tr>
		<td>Text</td>
		<td>The text to display</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>Speed</td>
		<td>The speed of the dialogue</td>
		<td>float</td>
		<td>12.5f</td>
	</tr>
	<tr>
		<td>Audio</td>
		<td>The audio to play with this dialogue entry</td>
		<td>USoundBase*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>bOverrideRichTextStyle</td>
		<td>Should the rich text style be overridden?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>RichTextStyle</td>
		<td>The rich text style applied to the widget</td>
		<td>UDataTable*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>bOverridePortraitImage</td>
		<td>Should the participant portrait image be overridden?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>CustomPortraitImage</td>
		<td>The custom portrait image for this dialogue entry</td>
		<td>UTexture2D*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>CustomPortraitBorderColor</td>
		<td>The custom portrait border color for this dialogue entry</td>
		<td>FSlateColor</td>
		<td>FSlateColo</td>
	</tr>
	<tr>
		<td>Dialogue</td>
		<td>A reference to the dialogue containing this entry</td>
		<td>UDialogue*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>ParentNodes</td>
		<td>An array of all the parent entries for this dialogue entry</td>
		<td>TArray&lt;UDialogueEntry*&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>ChildrenNodes</td>
		<td>An array of all the child entries for this dialogue entry</td>
		<td>TArray&lt;UDialogueEntry*&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>Edges</td>
		<td>A map of all the possible edges for this dialogue entry</td>
		<td>TMap&lt;UDialogueEntry*, UDialogueTransition*&gt;</td>
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
		<td>IsLeafNode</td>
		<td>Check if this entry is a leaf node</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if this entry is a leaf node</td>
	</tr>
	<tr>
		<td>GetTitle</td>
		<td>Get the title displayed for this dialogue entry</td>
		<td></td>
		<td><strong>FText</strong><br/>The title displayed for this dialogue entry</td>
	</tr>
	<tr>
		<td>GetText</td>
		<td>Get the text displayed for this dialogue entry</td>
		<td></td>
		<td><strong>FText</strong><br/>The text displayed for this dialogue entry</td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>DialogueEntry</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Dialogue > Entry > Is Leaf Node</li>
	<li>Ultimate Starter Kit > Dialogue > Entry > Get Title</li>
	<li>Ultimate Starter Kit > Dialogue > Entry > Get Text</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>DialogueEntry</code> can now be used in any of your C++ files:
```c++
#include "USK/Dialogue/DialogueEntry.h"

void ATestActor::Test()
{
	// DialogueEntry is a pointer to the UDialogueEntry
	bool IsLeafNodeValue = DialogueEntry->IsLeafNode();
	FText Title = DialogueEntry->GetTitle();
	FText Text = DialogueEntry->GetText();
}
```
