## Introduction
Base class for all enemy characters

## Dependencies
The <code>USKEnemyCharacter</code> relies on other components of this plugin to work:
<ul>
	<li><a href="../logger">Logger</a>: Used to log useful information to help you debug any issues you might experience</li>
</ul>

## Components
The <code>USKEnemyCharacter</code> uses the following components:
<table>
	<tr>
		<th>Name</th>
		<th>Description</th>
		<th>Type</th>
	</tr>
	<tr>
		<td>AttackCollider</td>
		<td>Base class for all enemy characters</td>
		<td>USphereComponent*</td>
	</tr>
	<tr>
		<td>AttackableObjectComponent</td>
		<td>The component used to allow the actor to be attacked</td>
		<td>UAttackableObjectComponent*</td>
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
		<td>BehaviorTree</td>
		<td>The behavior tree to use for the enemy character</td>
		<td>UBehaviorTree*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>TargetActorClass</td>
		<td>The class of the actor the enemy will target</td>
		<td>TSubclassOf&lt;AUSKCharacter&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>bPauseWhenLocationReached</td>
		<td>Should the AI be paused when the target location is reached?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>PauseDelay</td>
		<td>The delay in seconds before the AI starts moving again</td>
		<td>float</td>
		<td>3.0f</td>
	</tr>
	<tr>
		<td>AcceptanceRadius</td>
		<td>The radius around the target location before it is considered reached</td>
		<td>float</td>
		<td>100.0f</td>
	</tr>
	<tr>
		<td>bUseSpawningAnimation</td>
		<td>Should the enemy use a spawning animation?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>WanderAreas</td>
		<td>An array of areas where the enemy can wander</td>
		<td>TArray&lt;AEnemyWanderArea*&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>bUseRandomWanderLocation</td>
		<td>Should the enemy wander randomly?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>bWanderRandomX</td>
		<td>Should a random X location be used for wandering?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>RandomWanderXRange</td>
		<td>The range of random X locations used when picking a new wander location</td>
		<td>FVector2D</td>
		<td>FVector2</td>
	</tr>
	<tr>
		<td>bWanderRandomY</td>
		<td>Should a random Y location be used for wandering?</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>RandomWanderYRange</td>
		<td>The range of random Y locations used when picking a new wander location</td>
		<td>FVector2D</td>
		<td>FVector2</td>
	</tr>
	<tr>
		<td>bWanderRandomZ</td>
		<td>Should a random Z location be used for wandering?</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>RandomWanderZRange</td>
		<td>The range of random Z locations used when picking a new wander location</td>
		<td>FVector2D</td>
		<td>FVector2</td>
	</tr>
	<tr>
		<td>WanderAreaIndex</td>
		<td>The index of the wander area to use when wandering</td>
		<td>int</td>
		<td>0</td>
	</tr>
	<tr>
		<td>PatrolPoints</td>
		<td>The array of patrol points the enemy will move between</td>
		<td>TArray&lt;AEnemyPatrolPoint*&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>PatrolType</td>
		<td>The type of patrol movement the enemy will use</td>
		<td>EPatrolType</td>
		<td></td>
	</tr>
	<tr>
		<td>AttackColliderAttachBoneName</td>
		<td>The name of the bone to attach the attack collider to</td>
		<td>FName</td>
		<td></td>
	</tr>
	<tr>
		<td>MeleeAttackAnimationMontages</td>
		<td>The melee attack animation montages</td>
		<td>TArray&lt;UAnimMontage*&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>RangedAttackAnimationMontages</td>
		<td>The ranged attack animation montages</td>
		<td>TArray&lt;UAnimMontage*&gt;</td>
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
		<td>GetPatrolPointLocations</td>
		<td>Get the array of patrol point locations</td>
		<td></td>
		<td><strong>TArray&lt;FVector&gt;</strong><br/>The array of patrol point locations</td>
	</tr>
	<tr>
		<td>UpdateSpawnState</td>
		<td>Update the spawning state of the enemy</td>
		<td><strong>NewValue (bool)</strong><br/>The new spawning state value</td>
		<td></td>
	</tr>
	<tr>
		<td>IsSpawning</td>
		<td>Check if the enemy is busy spawning</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the enemy is busy spawning</td>
	</tr>
	<tr>
		<td>UpdateDeadState</td>
		<td>Update the dead state of the enemy</td>
		<td><strong>NewValue (bool)</strong><br/>The new dead state value</td>
		<td></td>
	</tr>
	<tr>
		<td>IsDead</td>
		<td>Check if the enemy is dead</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the enemy is dead</td>
	</tr>
	<tr>
		<td>StartStaggeredState</td>
		<td>Start the staggered state of the enemy</td>
		<td><strong>StaggerDuration (float)</strong><br/>The duration of the staggered state</td>
		<td></td>
	</tr>
	<tr>
		<td>EndStaggeredState</td>
		<td>End the staggered state of the enemy</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>IsStaggered</td>
		<td>Check if the enemy is staggered</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the enemy is staggered</td>
	</tr>
	<tr>
		<td>StartAttacking</td>
		<td>Start attacking the target</td>
		<td><strong>AttackType (EEnemyAttackType)</strong><br/>The type of attack to start</td>
		<td></td>
	</tr>
	<tr>
		<td>StopAttacking</td>
		<td>Stop attacking the target</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>OnAttackStarted</td>
		<td>Called when the attack is started</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>OnAttackStopped</td>
		<td>Called when the attack is stopped</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>GetCurrentAttackType</td>
		<td>Get the current attack type of the enemy</td>
		<td></td>
		<td><strong>EEnemyAttackType</strong><br/>The current attack type of the enemy</td>
	</tr>
	<tr>
		<td>TeleportOut</td>
		<td>Teleport the enemy out of the level</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>TeleportIn</td>
		<td>Teleport the enemy into the level</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>GetSummonLocation</td>
		<td>Get the location to summon an enemy</td>
		<td></td>
		<td><strong>FVector</strong><br/>The location to summon an enemy</td>
	</tr>
	<tr>
		<td>SummonEnemy</td>
		<td>Summon an enemy</td>
		<td></td>
		<td><strong>float</strong><br/>The duration of the summon sequence</td>
	</tr>
	<tr>
		<td>CancelSummoningEnemy</td>
		<td>Cancel summoning of an enemy</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>StartDodging</td>
		<td>Start the dodge sequence</td>
		<td><strong>DodgeConfig (FDodgeConfig)</strong><br/>The config used to dodge</td>
		<td></td>
	</tr>
	<tr>
		<td>StopDodging</td>
		<td>Stop the dodge sequence</td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>IsDodging</td>
		<td>Check if the enemy is dodging</td>
		<td></td>
		<td><strong>bool</strong><br/>A boolean value indicating if the enemy is dodging</td>
	</tr>
</table>

## Blueprint Usage
You can use the <code>USKEnemyCharacter</code> using Blueprints by adding one of the following nodes:
<ul>
	<li>Ultimate Starter Kit > AI > Get Patrol Point Locations</li>
	<li>Ultimate Starter Kit > AI > Update Spawn State</li>
	<li>Ultimate Starter Kit > AI > Is Spawning</li>
	<li>Ultimate Starter Kit > AI > Update Dead State</li>
	<li>Ultimate Starter Kit > AI > Is Dead</li>
	<li>Ultimate Starter Kit > AI > Start Staggered State</li>
	<li>Ultimate Starter Kit > AI > End Staggered State</li>
	<li>Ultimate Starter Kit > AI > Is Staggered</li>
	<li>Ultimate Starter Kit > AI > Start Attacking</li>
	<li>Ultimate Starter Kit > AI > Stop Attacking</li>
	<li>Ultimate Starter Kit > AI > On Attack Started</li>
	<li>Ultimate Starter Kit > AI > On Attack Stopped</li>
	<li>Ultimate Starter Kit > AI > Get Current Attack Type</li>
	<li>Ultimate Starter Kit > AI > Teleport Out</li>
	<li>Ultimate Starter Kit > AI > Teleport In</li>
	<li>Ultimate Starter Kit > AI > Get Summon Location</li>
	<li>Ultimate Starter Kit > AI > Summon Enemy</li>
	<li>Ultimate Starter Kit > AI > Cancel Summoning Enemy</li>
	<li>Ultimate Starter Kit > AI > Start Dodging</li>
	<li>Ultimate Starter Kit > AI > Stop Dodging</li>
	<li>Ultimate Starter Kit > AI > Is Dodging</li>
</ul>

## C++ Usage
Before you can use the plugin, you first need to enable the plugin in your <code>Build.cs</code> file:
```c++
PublicDependencyModuleNames.Add("USK");
```

The <code>USKEnemyCharacter</code> can now be used in any of your C++ files:
```c++
#include "USK/Character/USKEnemyCharacter.h"

void ATestActor::Test()
{
	// USKEnemyCharacter is a pointer to the AUSKEnemyCharacter
	TArray<FVector> PatrolPointLocations = USKEnemyCharacter->GetPatrolPointLocations();
	USKEnemyCharacter->UpdateSpawnState(NewValue);
	bool IsSpawningValue = USKEnemyCharacter->IsSpawning();
	USKEnemyCharacter->UpdateDeadState(NewValue);
	bool IsDeadValue = USKEnemyCharacter->IsDead();
	USKEnemyCharacter->StartStaggeredState(StaggerDuration);
	USKEnemyCharacter->EndStaggeredState();
	bool IsStaggeredValue = USKEnemyCharacter->IsStaggered();
	USKEnemyCharacter->StartAttacking(AttackType);
	USKEnemyCharacter->StopAttacking();
	USKEnemyCharacter->OnAttackStarted();
	USKEnemyCharacter->OnAttackStopped();
	EEnemyAttackType CurrentAttackType = USKEnemyCharacter->GetCurrentAttackType();
	USKEnemyCharacter->TeleportOut();
	USKEnemyCharacter->TeleportIn();
	FVector SummonLocation = USKEnemyCharacter->GetSummonLocation();
	float SummonEnemyValue = USKEnemyCharacter->SummonEnemy();
	USKEnemyCharacter->CancelSummoningEnemy();
	USKEnemyCharacter->StartDodging(DodgeConfig);
	USKEnemyCharacter->StopDodging();
	bool IsDodgingValue = USKEnemyCharacter->IsDodging();
}
```
