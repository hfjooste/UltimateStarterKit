## Introduction
A letter displayed in the world text

## Required Widgets
There is already a <code>WorldTextLetterWidget_Implementation</code> that you can use in your projects. But if you create your own instance of this widget, you need to add the following before you can compile:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>TextBlock</td>
		<td>The text block used to display the letter</td>
		<td>UTextBlock*</td>
	</tr>
</table>

## Optional Animations
You can add the following widgets to enable extra functionality:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
	</tr>
	<tr>
		<td>ShowAnimation</td>
		<td>The animation played when showing the letter</td>
	</tr>
	<tr>
		<td>DestroyAnimation</td>
		<td>The animation played when destroying the letter</td>
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
		<td>ShowAnimation</td>
		<td>The animation played when showing the letter</td>
		<td>UWidgetAnimation*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>DestroyAnimation</td>
		<td>The animation played when destroying the letter</td>
		<td>UWidgetAnimation*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>TypeDuration</td>
		<td>The time it takes to type the letter</td>
		<td>float</td>
		<td>0.055f</td>
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
		<td>InitializeLetter</td>
		<td>Initialize the letter</td>
		<td><strong>Word (UWorldTextWordWidget*)</strong><br/>The parent world text word widget<br/><br/><strong>Letter (FString&)</strong><br/>The letter to display</td>
		<td></td>
	</tr>
	<tr>
		<td>UpdateNextLetter</td>
		<td>Update the reference to the next letter in the word</td>
		<td><strong>Letter (UWorldTextLetterWidget*)</strong><br/>The next letter in the word</td>
		<td></td>
	</tr>
	<tr>
		<td>Show</td>
		<td>Show the letter</td>
		<td><strong>Index (int)</strong><br/>The index of the letter in the word</td>
		<td></td>
	</tr>
	<tr>
		<td>Destroy</td>
		<td>Destroy the letter</td>
		<td></td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>WorldTextLetterWidget</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Narrative > Initialize Letter</li>
	<li>Ultimate Starter Kit > Narrative > Update Next Letter</li>
	<li>Ultimate Starter Kit > Narrative > Show</li>
	<li>Ultimate Starter Kit > Narrative > Destroy</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>WorldTextLetterWidget</code> can now be used in any of your C++ files:
```c++
#include "USK/Narrative/WorldTextLetterWidget.h"

void ATestActor::Test()
{
	// WorldTextLetterWidget is a pointer to the UWorldTextLetterWidget
	WorldTextLetterWidget->InitializeLetter(Word, Letter);
	WorldTextLetterWidget->UpdateNextLetter(Letter);
	WorldTextLetterWidget->Show(Index);
	WorldTextLetterWidget->Destroy();
}
```
