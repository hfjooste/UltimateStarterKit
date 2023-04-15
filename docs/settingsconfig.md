## Introduction
The configuration used for managing settings

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
		<td>AudioMasterImplementation</td>
		<td>The implementation for the audio master settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemAudioMaster::StaticClas</td>
	</tr>
	<tr>
		<td>AudioMasterSoundMix</td>
		<td>The sound mix used to manage all sound classes</td>
		<td>USoundMix*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>AudioMasterText</td>
		<td>The text displayed in the master audio settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>AudioMasterMin</td>
		<td>The minimum value for the master audio settings item</td>
		<td>float</td>
		<td>0.0f</td>
	</tr>
	<tr>
		<td>AudioMasterMax</td>
		<td>The maximum value for the master audio settings item</td>
		<td>float</td>
		<td>100.0f</td>
	</tr>
	<tr>
		<td>AudioMasterDefault</td>
		<td>The default value for the master audio settings item</td>
		<td>float</td>
		<td>100.0f</td>
	</tr>
	<tr>
		<td>AudioMusicImplementation</td>
		<td>The implementation for the audio music settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemAudioMusic::StaticClas</td>
	</tr>
	<tr>
		<td>AudioMusicSoundClass</td>
		<td>The sound class used by all music</td>
		<td>USoundClass*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>AudioMusicText</td>
		<td>The text displayed in the music audio settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>AudioMusicMin</td>
		<td>The minimum value for the music audio settings item</td>
		<td>float</td>
		<td>0.0f</td>
	</tr>
	<tr>
		<td>AudioMusicMax</td>
		<td>The maximum value for the music audio settings item</td>
		<td>float</td>
		<td>100.0f</td>
	</tr>
	<tr>
		<td>AudioMusicDefault</td>
		<td>The default value for the music audio settings item</td>
		<td>float</td>
		<td>100.0f</td>
	</tr>
	<tr>
		<td>AudioEffectsImplementation</td>
		<td>The implementation for the audio effects settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemAudioEffects::StaticClas</td>
	</tr>
	<tr>
		<td>AudioEffectsSoundClass</td>
		<td>The sound class used by all effects</td>
		<td>USoundClass*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>AudioEffectsText</td>
		<td>The text displayed in the effects audio settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>AudioEffectsMin</td>
		<td>The minimum value for the effects audio settings item</td>
		<td>float</td>
		<td>0.0f</td>
	</tr>
	<tr>
		<td>AudioEffectsMax</td>
		<td>The maximum value for the effects audio settings item</td>
		<td>float</td>
		<td>100.0f</td>
	</tr>
	<tr>
		<td>AudioEffectsDefault</td>
		<td>The default value for the effects audio settings item</td>
		<td>float</td>
		<td>100.0f</td>
	</tr>
	<tr>
		<td>AudioUiImplementation</td>
		<td>The implementation for the audio UI settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemAudioUi::StaticClas</td>
	</tr>
	<tr>
		<td>AudioUiSoundClass</td>
		<td>The sound class used by all UI</td>
		<td>USoundClass*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>AudioUiText</td>
		<td>The text displayed in the UI audio settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>AudioUiMin</td>
		<td>The minimum value for the UI audio settings item</td>
		<td>float</td>
		<td>0.0f</td>
	</tr>
	<tr>
		<td>AudioUiMax</td>
		<td>The maximum value for the UI audio settings item</td>
		<td>float</td>
		<td>100.0f</td>
	</tr>
	<tr>
		<td>AudioUiDefault</td>
		<td>The default value for the UI audio settings item</td>
		<td>float</td>
		<td>100.0f</td>
	</tr>
	<tr>
		<td>AudioVoiceImplementation</td>
		<td>The implementation for the audio voice settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemAudioVoice::StaticClas</td>
	</tr>
	<tr>
		<td>AudioVoiceSoundClass</td>
		<td>The sound class used by all voice</td>
		<td>USoundClass*</td>
		<td><code>nullptr</code></td>
	</tr>
	<tr>
		<td>AudioVoiceText</td>
		<td>The text displayed in the voice audio settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>AudioVoiceMin</td>
		<td>The minimum value for the voice audio settings item</td>
		<td>float</td>
		<td>0.0f</td>
	</tr>
	<tr>
		<td>AudioVoiceMax</td>
		<td>The maximum value for the voice audio settings item</td>
		<td>float</td>
		<td>100.0f</td>
	</tr>
	<tr>
		<td>AudioVoiceDefault</td>
		<td>The default value for the voice audio settings item</td>
		<td>float</td>
		<td>100.0f</td>
	</tr>
</table>
