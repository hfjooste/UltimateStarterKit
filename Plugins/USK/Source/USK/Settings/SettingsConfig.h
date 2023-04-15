// Created by Henry Jooste

#pragma once

#include "SettingsItem.h"
#include "Engine/DataAsset.h"
#include "Engine/Classes/Sound/SoundMix.h"
#include "Engine/Classes/Sound/SoundClass.h"
#include "Items/SettingsItemAudioMaster.h"
#include "Items/SettingsItemAudioMusic.h"
#include "Items/SettingsItemAudioEffects.h"
#include "Items/SettingsItemAudioUi.h"
#include "Items/SettingsItemAudioVoice.h"
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
		DisplayName = "Text")
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
		DisplayName = "Text")
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
		DisplayName = "Text")
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
		DisplayName = "Text")
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
		DisplayName = "Text")
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
};