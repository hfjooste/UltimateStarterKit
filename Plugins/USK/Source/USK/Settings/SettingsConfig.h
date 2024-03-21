// Created by Henry Jooste

#pragma once

#include "SettingsItem.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundClass.h"
#include "Engine/DataAsset.h"
#include "Items/SettingsItemAccessibilityColorBlindMode.h"
#include "Items/SettingsItemAccessibilityColorBlindModeSeverity.h"
#include "Items/SettingsItemAudioMaster.h"
#include "Items/SettingsItemAudioMusic.h"
#include "Items/SettingsItemAudioEffects.h"
#include "Items/SettingsItemAudioUi.h"
#include "Items/SettingsItemAudioVoice.h"
#include "Items/SettingsItemControlsRemap.h"
#include "Items/SettingsItemGameplayDifficulty.h"
#include "Items/SettingsItemGraphicsAntiAliasing.h"
#include "Items/SettingsItemGraphicsFpsIndicator.h"
#include "Items/SettingsItemGraphicsResolution.h"
#include "Items/SettingsItemGraphicsFullscreen.h"
#include "Items/SettingsItemGraphicsPostProcessing.h"
#include "Items/SettingsItemGraphicsShadingQuality.h"
#include "Items/SettingsItemGraphicsShadowQuality.h"
#include "Items/SettingsItemGraphicsTextureQuality.h"
#include "Items/SettingsItemGraphicsViewDistance.h"
#include "Items/SettingsItemGraphicsVisualEffects.h"
#include "Items/SettingsItemGraphicsVsync.h"
#include "SettingsConfig.generated.h"

/**
 * @brief The configuration used for managing settings
 */
UCLASS(BlueprintType)
class USK_API USettingsConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	/**
	 * @brief The implementation for the gameplay difficulty setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Gameplay|Difficulty",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> GameplayDifficultyImplementation = USettingsItemGameplayDifficulty::StaticClass();

	/**
	 * @brief The text displayed in the gameplay difficulty settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Gameplay|Difficulty",
		DisplayName = "Title")
	FText GameplayDifficultyText;

	/**
	 * @brief The array of gameplay difficulty options
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Gameplay|Difficulty",
		DisplayName = "Options")
	TArray<FText> GameplayDifficultyOptions;

	/**
	 * @brief The default gameplay difficulty value
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Gameplay|Difficulty",
		DisplayName = "Default Value")
	int GameplayDifficultyDefault = 0;
	
	/**
	 * @brief The implementation for the audio master settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Master",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> AudioMasterImplementation = USettingsItemAudioMaster::StaticClass();

	/**
	 * @brief The sound mix used to manage all sound classes
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Master",
		DisplayName = "Sound Mix")
	USoundMix* AudioMasterSoundMix;

	/**
	 * @brief The text displayed in the master audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Master",
		DisplayName = "Title")
	FText AudioMasterText;

	/**
	 * @brief The minimum value for the master audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Master",
		DisplayName = "Minimum Value")
	float AudioMasterMin = 0.0f;

	/**
	 * @brief The maximum value for the master audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Master",
		DisplayName = "Maximum Value")
	float AudioMasterMax = 100.0f;

	/**
	 * @brief The default value for the master audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Master",
		DisplayName = "Default Value")
	float AudioMasterDefault = 100.0f;

	/**
	 * @brief The implementation for the audio music settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Music",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> AudioMusicImplementation = USettingsItemAudioMusic::StaticClass();

	/**
	 * @brief The sound class used by all music
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Music",
		DisplayName = "Sound Class")
	USoundClass* AudioMusicSoundClass;

	/**
	 * @brief The text displayed in the music audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Music",
		DisplayName = "Title")
	FText AudioMusicText;

	/**
	 * @brief The minimum value for the music audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Music",
		DisplayName = "Minimum Value")
	float AudioMusicMin = 0.0f;

	/**
	 * @brief The maximum value for the music audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Music",
		DisplayName = "Maximum Value")
	float AudioMusicMax = 100.0f;

	/**
	 * @brief The default value for the music audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Music",
		DisplayName = "Default Value")
	float AudioMusicDefault = 100.0f;

	/**
	 * @brief The implementation for the audio effects settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Effects",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> AudioEffectsImplementation = USettingsItemAudioEffects::StaticClass();

	/**
	 * @brief The sound class used by all effects
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Effects",
		DisplayName = "Sound Class")
	USoundClass* AudioEffectsSoundClass;

	/**
	 * @brief The text displayed in the effects audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Effects",
		DisplayName = "Title")
	FText AudioEffectsText;

	/**
	 * @brief The minimum value for the effects audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Effects",
		DisplayName = "Minimum Value")
	float AudioEffectsMin = 0.0f;

	/**
	 * @brief The maximum value for the effects audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Effects",
		DisplayName = "Maximum Value")
	float AudioEffectsMax = 100.0f;

	/**
	 * @brief The default value for the effects audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Effects",
		DisplayName = "Default Value")
	float AudioEffectsDefault = 100.0f;

	/**
	 * @brief The implementation for the audio UI settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|UI",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> AudioUiImplementation = USettingsItemAudioUi::StaticClass();

	/**
	 * @brief The sound class used by all UI
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|UI",
		DisplayName = "Sound Class")
	USoundClass* AudioUiSoundClass;

	/**
	 * @brief The text displayed in the UI audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|UI",
		DisplayName = "Title")
	FText AudioUiText;

	/**
	 * @brief The minimum value for the UI audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|UI",
		DisplayName = "Minimum Value")
	float AudioUiMin = 0.0f;

	/**
	 * @brief The maximum value for the UI audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|UI",
		DisplayName = "Maximum Value")
	float AudioUiMax = 100.0f;

	/**
	 * @brief The default value for the UI audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|UI",
		DisplayName = "Default Value")
	float AudioUiDefault = 100.0f;

	/**
	 * @brief The implementation for the audio voice settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Voice",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> AudioVoiceImplementation = USettingsItemAudioVoice::StaticClass();

	/**
	 * @brief The sound class used by all voice
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Voice",
		DisplayName = "Sound Class")
	USoundClass* AudioVoiceSoundClass;

	/**
	 * @brief The text displayed in the voice audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Voice",
		DisplayName = "Title")
	FText AudioVoiceText;

	/**
	 * @brief The minimum value for the voice audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Voice",
		DisplayName = "Minimum Value")
	float AudioVoiceMin = 0.0f;

	/**
	 * @brief The maximum value for the voice audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Voice",
		DisplayName = "Maximum Value")
	float AudioVoiceMax = 100.0f;

	/**
	 * @brief The default value for the voice audio settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Audio|Voice",
		DisplayName = "Default Value")
	float AudioVoiceDefault = 100.0f;

	/**
	 * @brief The implementation for the graphics resolution settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Resolution",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> GraphicsResolutionImplementation = USettingsItemGraphicsResolution::StaticClass();

	/**
	 * @brief The text displayed in the graphics resolution settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Resolution",
		DisplayName = "Title")
	FText GraphicsResolutionText;

	/**
	 * @brief The implementation for the graphics fullscreen settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Fullscreen",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> GraphicsFullscreenImplementation = USettingsItemGraphicsFullscreen::StaticClass();

	/**
	 * @brief The text displayed in the graphics fullscreen settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Fullscreen",
		DisplayName = "Title")
	FText GraphicsFullscreenText;

	/**
	 * @brief The text displayed when fullscreen is enabled
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Fullscreen",
		DisplayName = "Enabled Text")
	FText GraphicsFullscreenEnabledText;

	/**
	 * @brief The text displayed when fullscreen is disabled
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Fullscreen",
		DisplayName = "Disabled Text")
	FText GraphicsFullscreenDisabledText;

	/**
	 * @brief The default value of the fullscreen setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Fullscreen",
		DisplayName = "Default Value")
	bool GraphicsFullscreenDefault = true;

	/**
	 * @brief The implementation for the graphics view distance settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|View Distance",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> GraphicsViewDistanceImplementation = USettingsItemGraphicsViewDistance::StaticClass();

	/**
	 * @brief The text displayed in the graphics view distance settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|View Distance",
		DisplayName = "Title")
	FText GraphicsViewDistanceText;

	/**
	 * @brief The text displayed when the near value is used for the view distance setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|View Distance",
		DisplayName = "Near Text")
	FText GraphicsViewDistanceNearValueText;

	/**
	 * @brief The text displayed when the medium value is used for the view distance setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|View Distance",
		DisplayName = "Medium Text")
	FText GraphicsViewDistanceMediumValueText;

	/**
	 * @brief The text displayed when the far value is used for the view distance setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|View Distance",
		DisplayName = "Far Text")
	FText GraphicsViewDistanceFarValueText;

	/**
	 * @brief The text displayed when the epic value is used for the view distance setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|View Distance",
		DisplayName = "Epic Text")
	FText GraphicsViewDistanceEpicValueText;

	/**
	 * @brief The text displayed when the cinematic value is used for the view distance setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|View Distance",
		DisplayName = "Cinematic Text")
	FText GraphicsViewDistanceCinematicValueText;

	/**
	 * @brief The default value of the view distance setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|View Distance",
		DisplayName = "Default Value", meta = (ClampMin = "0", ClampMax = "4", UIMin = "0", UIMax = "4"))
	int GraphicsViewDistanceDefault = 2;

	/**
	 * @brief The implementation for the graphics anti-aliasing settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Anti-Aliasing",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> GraphicsAntiAliasingImplementation = USettingsItemGraphicsAntiAliasing::StaticClass();

	/**
	 * @brief The text displayed in the graphics anti-aliasing settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Anti-Aliasing",
		DisplayName = "Title")
	FText GraphicsAntiAliasingText;

	/**
	 * @brief The text displayed when the low value is used for the anti-aliasing setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Anti-Aliasing",
		DisplayName = "Low Text")
	FText GraphicsAntiAliasingLowValueText;

	/**
	 * @brief The text displayed when the medium value is used for the anti-aliasing setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Anti-Aliasing",
		DisplayName = "Medium Text")
	FText GraphicsAntiAliasingMediumValueText;

	/**
	 * @brief The text displayed when the high value is used for the anti-aliasing setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Anti-Aliasing",
		DisplayName = "High Text")
	FText GraphicsAntiAliasingHighValueText;

	/**
	 * @brief The text displayed when the epic value is used for the anti-aliasing setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Anti-Aliasing",
		DisplayName = "Epic Text")
	FText GraphicsAntiAliasingEpicValueText;

	/**
	 * @brief The text displayed when the cinematic value is used for the anti-aliasing setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Anti-Aliasing",
		DisplayName = "Cinematic Text")
	FText GraphicsAntiAliasingCinematicValueText;

	/**
	 * @brief The default value of the anti-aliasing setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Anti-Aliasing",
		DisplayName = "Default Value", meta = (ClampMin = "0", ClampMax = "4", UIMin = "0", UIMax = "4"))
	int GraphicsAntiAliasingDefault = 2;

	/**
	 * @brief The implementation for the graphics post processing settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Post Processing",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> GraphicsPostProcessingImplementation = USettingsItemGraphicsPostProcessing::StaticClass();

	/**
	 * @brief The text displayed in the graphics post processing settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Post Processing",
		DisplayName = "Title")
	FText GraphicsPostProcessingText;

	/**
	 * @brief The text displayed when the low value is used for the post processing setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Post Processing",
		DisplayName = "Low Text")
	FText GraphicsPostProcessingLowValueText;

	/**
	 * @brief The text displayed when the medium value is used for the post processing setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Post Processing",
		DisplayName = "Medium Text")
	FText GraphicsPostProcessingMediumValueText;

	/**
	 * @brief The text displayed when the high value is used for the post processing setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Post Processing",
		DisplayName = "High Text")
	FText GraphicsPostProcessingHighValueText;

	/**
	 * @brief The text displayed when the epic value is used for the post processing setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Post Processing",
		DisplayName = "Epic Text")
	FText GraphicsPostProcessingEpicValueText;

	/**
	 * @brief The text displayed when the cinematic value is used for the post processing setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Post Processing",
		DisplayName = "Cinematic Text")
	FText GraphicsPostProcessingCinematicValueText;

	/**
	 * @brief The default value of the post processing setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Post Processing",
		DisplayName = "Default Value", meta = (ClampMin = "0", ClampMax = "4", UIMin = "0", UIMax = "4"))
	int GraphicsPostProcessingDefault = 2;

	/**
	 * @brief The implementation for the graphics shadow quality settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Shadow Quality",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> GraphicsShadowQualityImplementation = USettingsItemGraphicsShadowQuality::StaticClass();

	/**
	 * @brief The text displayed in the graphics shadow quality settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Shadow Quality",
		DisplayName = "Title")
	FText GraphicsShadowQualityText;

	/**
	 * @brief The text displayed when the low value is used for the shadow quality setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Shadow Quality",
		DisplayName = "Low Text")
	FText GraphicsShadowQualityLowValueText;

	/**
	 * @brief The text displayed when the medium value is used for the shadow quality setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Shadow Quality",
		DisplayName = "Medium Text")
	FText GraphicsShadowQualityMediumValueText;

	/**
	 * @brief The text displayed when the high value is used for the shadow quality setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Shadow Quality",
		DisplayName = "High Text")
	FText GraphicsShadowQualityHighValueText;

	/**
	 * @brief The text displayed when the epic value is used for the shadow quality setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Shadow Quality",
		DisplayName = "Epic Text")
	FText GraphicsShadowQualityEpicValueText;

	/**
	 * @brief The text displayed when the cinematic value is used for the shadow quality setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Shadow Quality",
		DisplayName = "Cinematic Text")
	FText GraphicsShadowQualityCinematicValueText;

	/**
	 * @brief The default value of the shadow quality setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Shadow Quality",
		DisplayName = "Default Value", meta = (ClampMin = "0", ClampMax = "4", UIMin = "0", UIMax = "4"))
	int GraphicsShadowQualityDefault = 2;

	/**
	 * @brief The implementation for the graphics texture quality settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Texture Quality",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> GraphicsTextureQualityImplementation = USettingsItemGraphicsTextureQuality::StaticClass();

	/**
	 * @brief The text displayed in the graphics texture quality settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Texture Quality",
		DisplayName = "Title")
	FText GraphicsTextureQualityText;

	/**
	 * @brief The text displayed when the low value is used for the texture quality setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Texture Quality",
		DisplayName = "Low Text")
	FText GraphicsTextureQualityLowValueText;

	/**
	 * @brief The text displayed when the medium value is used for the texture quality setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Texture Quality",
		DisplayName = "Medium Text")
	FText GraphicsTextureQualityMediumValueText;

	/**
	 * @brief The text displayed when the high value is used for the texture quality setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Texture Quality",
		DisplayName = "High Text")
	FText GraphicsTextureQualityHighValueText;

	/**
	 * @brief The text displayed when the epic value is used for the texture quality setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Texture Quality",
		DisplayName = "Epic Text")
	FText GraphicsTextureQualityEpicValueText;

	/**
	 * @brief The text displayed when the cinematic value is used for the texture quality setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Texture Quality",
		DisplayName = "Cinematic Text")
	FText GraphicsTextureQualityCinematicValueText;

	/**
	 * @brief The default value of the texture quality setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Texture Quality",
		DisplayName = "Default Value", meta = (ClampMin = "0", ClampMax = "4", UIMin = "0", UIMax = "4"))
	int GraphicsTextureQualityDefault = 2;

	/**
	 * @brief The implementation for the graphics visual effects settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Visual Effects",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> GraphicsVisualEffectsImplementation = USettingsItemGraphicsVisualEffects::StaticClass();

	/**
	 * @brief The text displayed in the graphics visual effects settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Visual Effects",
		DisplayName = "Title")
	FText GraphicsVisualEffectsText;

	/**
	 * @brief The text displayed when the low value is used for the visual effects setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Visual Effects",
		DisplayName = "Low Text")
	FText GraphicsVisualEffectsLowValueText;

	/**
	 * @brief The text displayed when the medium value is used for the visual effects setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Visual Effects",
		DisplayName = "Medium Text")
	FText GraphicsVisualEffectsMediumValueText;

	/**
	 * @brief The text displayed when the high value is used for the visual effects setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Visual Effects",
		DisplayName = "High Text")
	FText GraphicsVisualEffectsHighValueText;

	/**
	 * @brief The text displayed when the epic value is used for the visual effects setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Visual Effects",
		DisplayName = "Epic Text")
	FText GraphicsVisualEffectsEpicValueText;

	/**
	 * @brief The text displayed when the cinematic value is used for the visual effects setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Visual Effects",
		DisplayName = "Cinematic Text")
	FText GraphicsVisualEffectsCinematicValueText;

	/**
	 * @brief The default value of the visual effects setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Visual Effects",
		DisplayName = "Default Value", meta = (ClampMin = "0", ClampMax = "4", UIMin = "0", UIMax = "4"))
	int GraphicsVisualEffectsDefault = 2;

	/**
	 * @brief The implementation for the graphics shading quality settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Shading Quality",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> GraphicsShadingQualityImplementation = USettingsItemGraphicsShadingQuality::StaticClass();

	/**
	 * @brief The text displayed in the graphics shading quality settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Shading Quality",
		DisplayName = "Title")
	FText GraphicsShadingQualityText;

	/**
	 * @brief The text displayed when the low value is used for the shading quality setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Shading Quality",
		DisplayName = "Low Text")
	FText GraphicsShadingQualityLowValueText;

	/**
	 * @brief The text displayed when the medium value is used for the shading quality setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Shading Quality",
		DisplayName = "Medium Text")
	FText GraphicsShadingQualityMediumValueText;

	/**
	 * @brief The text displayed when the high value is used for the shading quality setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Shading Quality",
		DisplayName = "High Text")
	FText GraphicsShadingQualityHighValueText;

	/**
	 * @brief The text displayed when the epic value is used for the shading quality setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Shading Quality",
		DisplayName = "Epic Text")
	FText GraphicsShadingQualityEpicValueText;

	/**
	 * @brief The text displayed when the cinematic value is used for the shading quality setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Shading Quality",
		DisplayName = "Cinematic Text")
	FText GraphicsShadingQualityCinematicValueText;

	/**
	 * @brief The default value of the shading quality setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|Shading Quality",
		DisplayName = "Default Value", meta = (ClampMin = "0", ClampMax = "4", UIMin = "0", UIMax = "4"))
	int GraphicsShadingQualityDefault = 2;

	/**
	 * @brief The implementation for the graphics vsync settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|VSync",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> GraphicsVsyncImplementation = USettingsItemGraphicsVsync::StaticClass();

	/**
	 * @brief The text displayed in the graphics vsync settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|VSync",
		DisplayName = "Title")
	FText GraphicsVsyncText;

	/**
	 * @brief The text displayed when the vsync setting is enabled
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|VSync",
		DisplayName = "Enabled Text")
	FText GraphicsVsyncEnabledText;

	/**
	 * @brief The text displayed when the vsync setting is disabled
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|VSync",
		DisplayName = "Disabled Text")
	FText GraphicsVsyncDisabledText;

	/**
	 * @brief The default value of the vsync setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|VSync",
		DisplayName = "Default Value")
	bool GraphicsVsyncDefault;

	/**
	 * @brief The implementation for the graphics FPS indicator settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|FPS Indicator",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> GraphicsFpsIndicatorImplementation = USettingsItemGraphicsFpsIndicator::StaticClass();

	/**
	 * @brief The text displayed in the graphics FPS indicator settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|FPS Indicator",
		DisplayName = "Title")
	FText GraphicsFpsIndicatorText;

	/**
	 * @brief The text displayed when the FPS indicator setting is enabled
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|FPS Indicator",
		DisplayName = "Enabled Text")
	FText GraphicsFpsIndicatorEnabledText;

	/**
	 * @brief The text displayed when the FPS indicator setting is disabled
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|FPS Indicator",
		DisplayName = "Disabled Text")
	FText GraphicsFpsIndicatorDisabledText;

	/**
	 * @brief The default value of the FPS indicator setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Graphics|FPS Indicator",
		DisplayName = "Default Value")
	bool GraphicsFpsIndicatorDefault;

	/**
	 * @brief The implementation for the accessibility color blind mode settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Accessibility|Color Blind Mode",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> AccessibilityColorBlindModeImplementation = USettingsItemAccessibilityColorBlindMode::StaticClass();

	/**
	 * @brief The text displayed in the accessibility color blind mode settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Accessibility|Color Blind Mode",
		DisplayName = "Title")
	FText AccessibilityColorBlindModeText;

	/**
	 * @brief The text displayed when the normal vision value is used for the accessibility color blind mode setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Accessibility|Color Blind Mode",
		DisplayName = "Normal Vision Text")
	FText AccessibilityColorBlindModeNormalVisionText;

	/**
	 * @brief The text displayed when the deuteranopia value is used for the accessibility color blind mode setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Accessibility|Color Blind Mode",
		DisplayName = "Deuteranopia Text")
	FText AccessibilityColorBlindModeDeuteranopiaText;
	
	/**
	 * @brief The text displayed when the deuteranomaly value is used for the accessibility color blind mode setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Accessibility|Color Blind Mode",
		DisplayName = "Deuteranomaly Text")
	FText AccessibilityColorBlindModeDeuteranomalyText;

	/**
	 * @brief The text displayed when the protanopia value is used for the accessibility color blind mode setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Accessibility|Color Blind Mode",
		DisplayName = "Protanopia Text")
	FText AccessibilityColorBlindModeProtanopiaText;
	
	/**
	 * @brief The text displayed when the protanomaly value is used for the accessibility color blind mode setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Accessibility|Color Blind Mode",
		DisplayName = "Protanomaly Text")
	FText AccessibilityColorBlindModeProtanomalyText;

	/**
	 * @brief The text displayed when the tritanopia value is used for the accessibility color blind mode setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Accessibility|Color Blind Mode",
		DisplayName = "Tritanopia Text")
	FText AccessibilityColorBlindModeTritanopiaText;

	/**
	 * @brief The text displayed when the tritanomaly value is used for the accessibility color blind mode setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Accessibility|Color Blind Mode",
		DisplayName = "Tritanomaly Text")
	FText AccessibilityColorBlindModeTritanomalyText;

	/**
	 * @brief The implementation for the accessibility color blind mode severity settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Accessibility|Color Blind Mode Severity",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> AccessibilityColorBlindModeSeverityImplementation = USettingsItemAccessibilityColorBlindModeSeverity::StaticClass();

	/**
	 * @brief The text displayed in the accessibility color blind mode severity settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Accessibility|Color Blind Mode Severity",
		DisplayName = "Title")
	FText AccessibilityColorBlindModeSeverityText;

	/**
	 * @brief The implementation for the controls remap settings item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Controls",
		DisplayName = "Implementation")
	TSubclassOf<USettingsItem> ControlsRemapImplementation = USettingsItemControlsRemap::StaticClass();

	/**
	 * @brief The text displayed in the menu item while waiting for the user to press a new key
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings|Controls",
		DisplayName = "Waiting for key press text")
	FText ControlsWaitingForKeyPressText;
};