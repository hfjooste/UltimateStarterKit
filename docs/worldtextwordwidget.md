## Introduction
The widget used to display a word in the world

## Required Widgets
There is already a <code>WorldTextWordWidget_Implementation</code> that you can use in your projects. But if you create your own instance of this widget, you need to add the following before you can compile:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>Container</td>
		<td>The container for all the letters</td>
		<td>UHorizontalBox*</td>
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
		<td>InitializeWord</td>
		<td>Initialize the word</td>
		<td><strong>Text (UWorldTextWidget*)</strong><br/>The parent world text widget<br/><br/><strong>Word (FString)</strong><br/>The word to display</td>
		<td></td>
	</tr>
	<tr>
		<td>UpdateNextWord</td>
		<td>Update the reference to the next word in the text</td>
		<td><strong>Word (UWorldTextWordWidget*)</strong><br/>The next word in the text</td>
		<td></td>
	</tr>
	<tr>
		<td>Show</td>
		<td>Show the word</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>ShowNextWord</td>
		<td>Show the next word</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>Destroy</td>
		<td>Destroy the word widget</td>
		<td></td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>WorldTextWordWidget</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Narrative > Initialize Word</li>
	<li>Ultimate Starter Kit > Narrative > Update Next Word</li>
	<li>Ultimate Starter Kit > Narrative > Show</li>
	<li>Ultimate Starter Kit > Narrative > Show Next Word</li>
	<li>Ultimate Starter Kit > Narrative > Destroy</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>WorldTextWordWidget</code> can now be used in any of your C++ files:
```c++
#include "USK/Narrative/WorldTextWordWidget.h"

void ATestActor::Test()
{
	// WorldTextWordWidget is a pointer to the UWorldTextWordWidget
	WorldTextWordWidget->InitializeWord(Text, Word);
	WorldTextWordWidget->UpdateNextWord(Word);
	WorldTextWordWidget->Show();
	WorldTextWordWidget->ShowNextWord();
	WorldTextWordWidget->Destroy();
}
```
