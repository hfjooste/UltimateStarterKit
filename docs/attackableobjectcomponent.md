## Introduction
Component used to allow objects to be attacked

## API Reference
### Events
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Params</th>
	</tr>
	<tr>
		<td>OnAttacked</td>
		<td>Event used to notify other classes when the object is attacked</td>
		<td><strong>Attacker (AActor*)</strong><br/>A reference to the attacker</td>
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
		<td>NotifyAttack</td>
		<td>Notify subscribers that the object was attacked</td>
		<td><strong>Attacker (AActor*)</strong><br/>A reference to the attacker</td>
		<td></td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>AttackableObjectComponent</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > Components > Notify Attack</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>AttackableObjectComponent</code> can now be used in any of your C++ files:
```c++
#include "USK/Components/AttackableObjectComponent.h"

void ATestActor::Test()
{
	// AttackableObjectComponent is a pointer to the UAttackableObjectComponent
	AttackableObjectComponent->NotifyAttack(Attacker);
}
```
