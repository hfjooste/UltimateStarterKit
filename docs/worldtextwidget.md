## Introduction
The widget used to display text in the world

## Dependencies
The <code>WorldTextWidget</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../audio">Audio</a>: Used to play sound effects either 2D or at a specified location</li>
</ul>

## Required Widgets
There is already a <code>WorldTextWidget_Implementation</code> that you can use in your projects. But if you create your own instance of this widget, you need to add the following before you can compile:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>Container</td>
		<td>The container for all the word widgets</td>
		<td>UWrapBox*</td>
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
		<td>DestroyTextDelay</td>
		<td>The delay before destroying the text widget after typing has finished</td>
		<td>float</td>
		<td>2.0f</td>
	</tr>
	<tr>
		<td>DestroyActorDelay</td>
		<td>The delay before destroying the actor after the text widget has been destroyed</td>
		<td>float</td>
		<td>1.0f</td>
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
		<td>OnDestroyed</td>
		<td>Event used to notify other classes when the text is destroyed</td>
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
		<td>InitializeWidget</td>
		<td>Initialize the widget</td>
		<td><strong>WordClass (TSubclassOf<UWorldTextWordWidget>)</strong><br/>The world word widget class<br/><br/><strong>LetterClass (TSubclassOf<UWorldTextLetterWidget>)</strong><br/>The world letter widget class</td>
		<td></td>
	</tr>
	<tr>
		<td>Show</td>
		<td>Show the text in the widget</td>
		<td><strong>Text (FText&)</strong><br/>The text to display<br/><br/><strong>Sound (USoundBase*)</strong><br/>The sound to play when displaying the text<br/><br/><strong>PlaySoundAtActor (AActor*)</strong><br/>The actor to play the sound at</td>
		<td></td>
	</tr>
	<tr>
		<td>Destroy</td>
		<td>Destroy the text widget</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>GetWordWidgetClass</td>
		<td>Get the world word widget class</td>
		<td></td>
		<td><strong>TSubclassOf&lt;UWorldTextWordWidget&gt;</strong><br/>The world word widget class</td>
	</tr>
	<tr>
		<td>GetLetterWidgetClass</td>
		<td>Get the world letter widget class</td>
		<td></td>
		<td><strong>TSubclassOf&lt;UWorldTextLetterWidget&gt;</strong><br/>The world letter widget class</td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>WorldTextWidget</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Narrative > Initialize Widget</li>
	<li>Ultimate Starter Kit > Narrative > Show</li>
	<li>Ultimate Starter Kit > Narrative > Destroy</li>
	<li>Ultimate Starter Kit > Narrative > Get Word Widget Class</li>
	<li>Ultimate Starter Kit > Narrative > Get Letter Widget Class</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>WorldTextWidget</code> can now be used in any of your C++ files:
```c++
#include "USK/Narrative/WorldTextWidget.h"

void ATestActor::Test()
{
	// WorldTextWidget is a pointer to the UWorldTextWidget
	WorldTextWidget->InitializeWidget(WordClass, LetterClass);
	WorldTextWidget->Show(Text, Sound, PlaySoundAtActor);
	WorldTextWidget->Destroy();
	TSubclassOf<UWorldTextWordWidget> WordWidgetClass = WorldTextWidget->GetWordWidgetClass();
	TSubclassOf<UWorldTextLetterWidget> LetterWidgetClass = WorldTextWidget->GetLetterWidgetClass();
}
```
