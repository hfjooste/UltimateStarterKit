## Introduction
Behaviour tree task node used to make the enemy character attack

## Dependencies
The <code>BTTask_UskAttack</code> relies on other components of this plugin to work:
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
		<td>OwnerKey</td>
		<td>The blackboard key used to store the owner</td>
		<td>FBlackboardKeySelector</td>
		<td></td>
	</tr>
	<tr>
		<td>AttackType</td>
		<td>The type of attack that should be performed</td>
		<td>EEnemyAttackType</td>
		<td>EEnemyAttackType::Melee</td>
	</tr>
</table>
