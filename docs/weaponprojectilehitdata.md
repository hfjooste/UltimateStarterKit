## Introduction
Structure describing the hit data of a projectile

## Properties
<table>
	<tr>
		<th>Property</th>
		<th>Description</th>
		<th>Type</th>
		<th>Default Value</th>
	</tr>
	<tr>
		<td>HitParticleFx</td>
		<td>The particle FX to spawn when the projectile hits the actor</td>
		<td>UNiagaraSystem*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>HitParticleFxTransform</td>
		<td>The transform of the particle FX</td>
		<td>FTransform</td>
		<td></td>
	</tr>
	<tr>
		<td>HitSfx</td>
		<td>The sound effect to play when the projectile hits the actor</td>
		<td>TArray&lt;USoundBase*&gt;</td>
		<td></td>
	</tr>
</table>
