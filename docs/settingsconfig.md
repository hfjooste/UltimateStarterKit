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
		<td>GameplayDifficultyImplementation</td>
		<td>The implementation for the gameplay difficulty setting</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemGameplayDifficulty::StaticClas</td>
	</tr>
	<tr>
		<td>GameplayDifficultyText</td>
		<td>The text displayed in the gameplay difficulty settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GameplayDifficultyOptions</td>
		<td>The array of gameplay difficulty options</td>
		<td>TArray&lt;FText&gt;</td>
		<td></td>
	</tr>
	<tr>
		<td>GameplayDifficultyDefault</td>
		<td>The default gameplay difficulty value</td>
		<td>int</td>
		<td>0</td>
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
	<tr>
		<td>GraphicsResolutionImplementation</td>
		<td>The implementation for the graphics resolution settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemGraphicsResolution::StaticClas</td>
	</tr>
	<tr>
		<td>GraphicsResolutionText</td>
		<td>The text displayed in the graphics resolution settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsFullscreenImplementation</td>
		<td>The implementation for the graphics fullscreen settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemGraphicsFullscreen::StaticClas</td>
	</tr>
	<tr>
		<td>GraphicsFullscreenText</td>
		<td>The text displayed in the graphics fullscreen settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsFullscreenEnabledText</td>
		<td>The text displayed when fullscreen is enabled</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsFullscreenDisabledText</td>
		<td>The text displayed when fullscreen is disabled</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsFullscreenDefault</td>
		<td>The default value of the fullscreen setting</td>
		<td>bool</td>
		<td>true</td>
	</tr>
	<tr>
		<td>GraphicsViewDistanceImplementation</td>
		<td>The implementation for the graphics view distance settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemGraphicsViewDistance::StaticClas</td>
	</tr>
	<tr>
		<td>GraphicsViewDistanceText</td>
		<td>The text displayed in the graphics view distance settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsViewDistanceNearValueText</td>
		<td>The text displayed when the near value is used for the view distance setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsViewDistanceMediumValueText</td>
		<td>The text displayed when the medium value is used for the view distance setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsViewDistanceFarValueText</td>
		<td>The text displayed when the far value is used for the view distance setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsViewDistanceEpicValueText</td>
		<td>The text displayed when the epic value is used for the view distance setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsViewDistanceCinematicValueText</td>
		<td>The text displayed when the cinematic value is used for the view distance setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsViewDistanceDefault</td>
		<td>The default value of the view distance setting</td>
		<td>int</td>
		<td>2</td>
	</tr>
	<tr>
		<td>GraphicsAntiAliasingImplementation</td>
		<td>The implementation for the graphics anti-aliasing settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemGraphicsAntiAliasing::StaticClas</td>
	</tr>
	<tr>
		<td>GraphicsAntiAliasingText</td>
		<td>The text displayed in the graphics anti-aliasing settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsAntiAliasingLowValueText</td>
		<td>The text displayed when the low value is used for the anti-aliasing setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsAntiAliasingMediumValueText</td>
		<td>The text displayed when the medium value is used for the anti-aliasing setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsAntiAliasingHighValueText</td>
		<td>The text displayed when the high value is used for the anti-aliasing setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsAntiAliasingEpicValueText</td>
		<td>The text displayed when the epic value is used for the anti-aliasing setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsAntiAliasingCinematicValueText</td>
		<td>The text displayed when the cinematic value is used for the anti-aliasing setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsAntiAliasingDefault</td>
		<td>The default value of the anti-aliasing setting</td>
		<td>int</td>
		<td>2</td>
	</tr>
	<tr>
		<td>GraphicsPostProcessingImplementation</td>
		<td>The implementation for the graphics post processing settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemGraphicsPostProcessing::StaticClas</td>
	</tr>
	<tr>
		<td>GraphicsPostProcessingText</td>
		<td>The text displayed in the graphics post processing settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsPostProcessingLowValueText</td>
		<td>The text displayed when the low value is used for the post processing setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsPostProcessingMediumValueText</td>
		<td>The text displayed when the medium value is used for the post processing setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsPostProcessingHighValueText</td>
		<td>The text displayed when the high value is used for the post processing setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsPostProcessingEpicValueText</td>
		<td>The text displayed when the epic value is used for the post processing setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsPostProcessingCinematicValueText</td>
		<td>The text displayed when the cinematic value is used for the post processing setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsPostProcessingDefault</td>
		<td>The default value of the post processing setting</td>
		<td>int</td>
		<td>2</td>
	</tr>
	<tr>
		<td>GraphicsShadowQualityImplementation</td>
		<td>The implementation for the graphics shadow quality settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemGraphicsShadowQuality::StaticClas</td>
	</tr>
	<tr>
		<td>GraphicsShadowQualityText</td>
		<td>The text displayed in the graphics shadow quality settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsShadowQualityLowValueText</td>
		<td>The text displayed when the low value is used for the shadow quality setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsShadowQualityMediumValueText</td>
		<td>The text displayed when the medium value is used for the shadow quality setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsShadowQualityHighValueText</td>
		<td>The text displayed when the high value is used for the shadow quality setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsShadowQualityEpicValueText</td>
		<td>The text displayed when the epic value is used for the shadow quality setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsShadowQualityCinematicValueText</td>
		<td>The text displayed when the cinematic value is used for the shadow quality setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsShadowQualityDefault</td>
		<td>The default value of the shadow quality setting</td>
		<td>int</td>
		<td>2</td>
	</tr>
	<tr>
		<td>GraphicsTextureQualityImplementation</td>
		<td>The implementation for the graphics texture quality settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemGraphicsTextureQuality::StaticClas</td>
	</tr>
	<tr>
		<td>GraphicsTextureQualityText</td>
		<td>The text displayed in the graphics texture quality settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsTextureQualityLowValueText</td>
		<td>The text displayed when the low value is used for the texture quality setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsTextureQualityMediumValueText</td>
		<td>The text displayed when the medium value is used for the texture quality setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsTextureQualityHighValueText</td>
		<td>The text displayed when the high value is used for the texture quality setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsTextureQualityEpicValueText</td>
		<td>The text displayed when the epic value is used for the texture quality setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsTextureQualityCinematicValueText</td>
		<td>The text displayed when the cinematic value is used for the texture quality setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsTextureQualityDefault</td>
		<td>The default value of the texture quality setting</td>
		<td>int</td>
		<td>2</td>
	</tr>
	<tr>
		<td>GraphicsVisualEffectsImplementation</td>
		<td>The implementation for the graphics visual effects settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemGraphicsVisualEffects::StaticClas</td>
	</tr>
	<tr>
		<td>GraphicsVisualEffectsText</td>
		<td>The text displayed in the graphics visual effects settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsVisualEffectsLowValueText</td>
		<td>The text displayed when the low value is used for the visual effects setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsVisualEffectsMediumValueText</td>
		<td>The text displayed when the medium value is used for the visual effects setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsVisualEffectsHighValueText</td>
		<td>The text displayed when the high value is used for the visual effects setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsVisualEffectsEpicValueText</td>
		<td>The text displayed when the epic value is used for the visual effects setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsVisualEffectsCinematicValueText</td>
		<td>The text displayed when the cinematic value is used for the visual effects setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsVisualEffectsDefault</td>
		<td>The default value of the visual effects setting</td>
		<td>int</td>
		<td>2</td>
	</tr>
	<tr>
		<td>GraphicsShadingQualityImplementation</td>
		<td>The implementation for the graphics shading quality settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemGraphicsShadingQuality::StaticClas</td>
	</tr>
	<tr>
		<td>GraphicsShadingQualityText</td>
		<td>The text displayed in the graphics shading quality settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsShadingQualityLowValueText</td>
		<td>The text displayed when the low value is used for the shading quality setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsShadingQualityMediumValueText</td>
		<td>The text displayed when the medium value is used for the shading quality setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsShadingQualityHighValueText</td>
		<td>The text displayed when the high value is used for the shading quality setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsShadingQualityEpicValueText</td>
		<td>The text displayed when the epic value is used for the shading quality setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsShadingQualityCinematicValueText</td>
		<td>The text displayed when the cinematic value is used for the shading quality setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsShadingQualityDefault</td>
		<td>The default value of the shading quality setting</td>
		<td>int</td>
		<td>2</td>
	</tr>
	<tr>
		<td>GraphicsVsyncImplementation</td>
		<td>The implementation for the graphics vsync settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemGraphicsVsync::StaticClas</td>
	</tr>
	<tr>
		<td>GraphicsVsyncText</td>
		<td>The text displayed in the graphics vsync settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsVsyncEnabledText</td>
		<td>The text displayed when the vsync setting is enabled</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsVsyncDisabledText</td>
		<td>The text displayed when the vsync setting is disabled</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsVsyncDefault</td>
		<td>The default value of the vsync setting</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>GraphicsFpsIndicatorImplementation</td>
		<td>The implementation for the graphics FPS indicator settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemGraphicsFpsIndicator::StaticClas</td>
	</tr>
	<tr>
		<td>GraphicsFpsIndicatorText</td>
		<td>The text displayed in the graphics FPS indicator settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsFpsIndicatorEnabledText</td>
		<td>The text displayed when the FPS indicator setting is enabled</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsFpsIndicatorDisabledText</td>
		<td>The text displayed when the FPS indicator setting is disabled</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>GraphicsFpsIndicatorDefault</td>
		<td>The default value of the FPS indicator setting</td>
		<td>bool</td>
		<td>false</td>
	</tr>
	<tr>
		<td>AccessibilityColorBlindModeImplementation</td>
		<td>The implementation for the accessibility color blind mode settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemAccessibilityColorBlindMode::StaticClas</td>
	</tr>
	<tr>
		<td>AccessibilityColorBlindModeText</td>
		<td>The text displayed in the accessibility color blind mode settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>AccessibilityColorBlindModeNormalVisionText</td>
		<td>The text displayed when the normal vision value is used for the accessibility color blind mode setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>AccessibilityColorBlindModeDeuteranopiaText</td>
		<td>The text displayed when the deuteranopia value is used for the accessibility color blind mode setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>AccessibilityColorBlindModeDeuteranomalyText</td>
		<td>The text displayed when the deuteranomaly value is used for the accessibility color blind mode setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>AccessibilityColorBlindModeProtanopiaText</td>
		<td>The text displayed when the protanopia value is used for the accessibility color blind mode setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>AccessibilityColorBlindModeProtanomalyText</td>
		<td>The text displayed when the protanomaly value is used for the accessibility color blind mode setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>AccessibilityColorBlindModeTritanopiaText</td>
		<td>The text displayed when the tritanopia value is used for the accessibility color blind mode setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>AccessibilityColorBlindModeTritanomalyText</td>
		<td>The text displayed when the tritanomaly value is used for the accessibility color blind mode setting</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>AccessibilityColorBlindModeSeverityImplementation</td>
		<td>The implementation for the accessibility color blind mode severity settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemAccessibilityColorBlindModeSeverity::StaticClas</td>
	</tr>
	<tr>
		<td>AccessibilityColorBlindModeSeverityText</td>
		<td>The text displayed in the accessibility color blind mode severity settings item</td>
		<td>FText</td>
		<td></td>
	</tr>
	<tr>
		<td>ControlsRemapImplementation</td>
		<td>The implementation for the controls remap settings item</td>
		<td>TSubclassOf&lt;USettingsItem&gt;</td>
		<td>USettingsItemControlsRemap::StaticClas</td>
	</tr>
	<tr>
		<td>ControlsWaitingForKeyPressText</td>
		<td>The text displayed in the menu item while waiting for the user to press a new key</td>
		<td>FText</td>
		<td></td>
	</tr>
</table>
