## Introduction
A trigger that can be used to interact with an object

## Dependencies
The <code>InteractTrigger</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

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
		<td>bRequireCurrency</td>
		<td>Is this a paid item that should be bought using currency?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>CurrencyRequirements</td>
		<td>The currency requirements before the object can be interacted with</td>
		<td>TMap&lt;FName, int&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>InteractWidgetClass</td>
		<td>The class of the interact widget</td>
		<td>TSubclassOf&lt;UInteractWidget&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>BeforeText</td>
		<td>The text displayed before the input indicator</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>AfterText</td>
		<td>The text displayed after the input indicator</td>
		<td>FText</td>
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
		<td>CanInteract</td>
		<td>Check if the actor can interact with the object</td>
		<td><strong>Actor (AActor*)</strong><br/>The actor trying to interact with the object</td>
		<td><strong>bool</strong><br/>A boolean value indicating if the actor can interact with the object</td>
	</tr>
	<tr>
		<td>OnInteracted</td>
		<td>Called when the actor interacts with the object</td>
		<td><strong>Actor (AActor*)</strong><br/>The actor that interacted with the object</td>
		<td></td>
	</tr>
	<tr>
		<td>ReceiveOnInteracted</td>
		<td>Called when the actor interacts with the object</td>
		<td><strong>Actor (AActor*)</strong><br/>The actor that interacted with the object</td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>InteractTrigger</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Interact Trigger > Can Interact</li>
	<li>Ultimate Starter Kit > Interact Trigger > On Interacted</li>
	<li>Ultimate Starter Kit > Interact Trigger > OnInteracted</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>InteractTrigger</code> can now be used in any of your C++ files:
```c++
#include "USK/Components/InteractTrigger.h"

void ATestActor::Test()
{
	// InteractTrigger is a pointer to the UInteractTrigger
	bool CanInteractValue = InteractTrigger->CanInteract(Actor);
	InteractTrigger->OnInteracted(Actor);
	InteractTrigger->ReceiveOnInteracted(Actor);
}
```
