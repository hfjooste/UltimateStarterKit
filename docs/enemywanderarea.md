## Introduction
An area in the world that an enemy can wander around in

## Components
The <code>EnemyWanderArea</code> uses the following components:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>WanderArea</td>
		<td>An area in the world that an enemy can wander around in</td>
		<td>UBoxComponent*</td>
	</tr>
</table>

## API Reference
### Functions
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Params</th>
		<th>Return</th>
	</tr>
	<tr>
		<td>GetRandomLocationInArea</td>
		<td>Get a random location in the wander area</td>
		<td></td>
		<td><strong>FVector</strong><br/>A random location in the wander area</td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>EnemyWanderArea</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > AI > Get Random Location In Area</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>EnemyWanderArea</code> can now be used in any of your C++ files:
```c++
#include "USK/AI/EnemyWanderArea.h"

void ATestActor::Test()
{
	// EnemyWanderArea is a pointer to the AEnemyWanderArea
	FVector RandomLocationInArea = EnemyWanderArea->GetRandomLocationInArea();
}
```
