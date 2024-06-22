## Introduction
The animation instance for the enemy character

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
		<td>IdleAnimation</td>
		<td>The animation played when the character is idle</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>WalkAnimation</td>
		<td>The animation played when the character is walking</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>RunAnimation</td>
		<td>The animation played when the character is running</td>
		<td>UAnimSequence*</td>
		<td><code>nullptr</code></td>
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
		<td>GetMovementSpeed</td>
		<td>Get the movement speed of the player</td>
		<td></td>
		<td><strong>float</strong><br/>The movement speed of the player</td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>USKEnemyAnimationInstance</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Animations > Get Movement Speed</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>USKEnemyAnimationInstance</code> can now be used in any of your C++ files:
```c++
#include "USK/Character/USKEnemyAnimationInstance.h"

void ATestActor::Test()
{
	// USKEnemyAnimationInstance is a pointer to the UUSKEnemyAnimationInstance
	float MovementSpeed = USKEnemyAnimationInstance->GetMovementSpeed();
}
```
