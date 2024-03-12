## Introduction
Widget used to display a dialogue

## Dependencies
The <code>DialogueTransitionType</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Required Widgets
You need to add the following before you can compile the <code>DialogueTransitionType</code> widget:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>DialogueTitle</td>
		<td>The text block used to display the dialogue title</td>
		<td>UTextBlock*</td>
	</tr>
	<tr>
		<td>DialogueText</td>
		<td>The text block used to display the dialogue text</td>
		<td>URichTextBlock*</td>
	</tr>
	<tr>
		<td>ChoiceMenu</td>
		<td>The menu used to display the dialogue choices</td>
		<td>UMenu*</td>
	</tr>
</table>

## Optional Widgets
You can add the following widgets to enable extra functionality:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>ParticipantPortrait</td>
		<td>The image used to display the portrait image of the participant</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>ParticipantPortraitBorder</td>
		<td>The border image displayed around the portrait image of the participant</td>
		<td>UImage*</td>
	</tr>
	<tr>
		<td>SkipEntryImage</td>
		<td>The image displayed when the dialogue entry is completed</td>
		<td>UImage*</td>
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
		<td>ChoiceMenuItemClass</td>
		<td>The class for all choice menu items</td>
		<td>TSubclassOf&lt;UMenuItem&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>RichTextStyle</td>
		<td>The rich text style applied to the dialogue text</td>
		<td>UDataTable*</td>
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
		<td>OnChoiceSelected</td>
		<td>Event used to notify other classes when a choice is selected</td>
		<td><strong>Index (int)</strong><br/>The index of the choice that was selected</td>
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
		<td>UpdateEntry</td>
		<td>Update the current entry and refresh the UI</td>
		<td><strong>Entry (UDialogueEntry*)</strong><br/>The new dialogue entry</td>
		<td></td>
	</tr>
	<tr>
		<td>SkipEntry</td>
		<td>Skip the current entry</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the entry was skipped</td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>DialogueTransitionType</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > UI > Update Entry</li>
	<li>Ultimate Starter Kit > UI > Skip Entry</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>DialogueTransitionType</code> can now be used in any of your C++ files:
```c++
#include "USK/Dialogue/DialogueWidget.h"

void ATestActor::Test()
{
	// DialogueTransitionType is a pointer to the EDialogueTransitionType
	DialogueTransitionType->UpdateEntry(Entry);
	bool SkipEntryValue = DialogueTransitionType->SkipEntry();
}
```
