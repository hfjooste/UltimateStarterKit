// Created by Henry Jooste

#pragma once

#include "GameFramework/SaveGame.h"
#include "SettingsData.generated.h"

/**
 * @brief The settings data that is saved/loaded 
 */
UCLASS()
class USK_API USettingsData : public USaveGame
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Was the master audio volume modified?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool AudioMasterModified;

	/**
	 * @brief The master audio volume
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	float AudioMaster;

	/**
	 * @brief Was the music volume modified?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool AudioMusicModified;

	/**
	 * @brief The music volume
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	float AudioMusic;

	/**
	 * @brief Was the effects volume modified?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool AudioEffectsModified;

	/**
	 * @brief The effects volume
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	float AudioEffects;

	/**
	 * @brief Was the UI volume modified?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool AudioUiModified;

	/**
	 * @brief The UI volume
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	float AudioUi;

	/**
	 * @brief Was the voice volume modified?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool AudioVoiceModified;

	/**
	 * @brief The voice volume
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
    float AudioVoice;
};