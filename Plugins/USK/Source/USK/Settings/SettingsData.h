// Created by Henry Jooste

#pragma once

#include "GameFramework/SaveGame.h"
#include "InputCoreTypes.h"
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
	 * @brief Was the gameplay difficulty setting modified?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool GameplayDifficultyModified;

	/**
	 * @brief The gameplay difficulty setting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	int GameplayDifficulty;
	
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

	/**
	 * @brief The X value of the saved resolution
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	int GraphicsResolutionX;

	/**
	 * @brief The Y value of the saved resolution
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	int GraphicsResolutionY;

	/**
	 * @brief Was the graphics fullscreen setting modified?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool GraphicsFullscreenModified;

	/**
	 * @brief The graphics fullscreen value
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool GraphicsFullscreen;

	/**
	 * @brief Was the graphics view distance setting modified?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool GraphicsViewDistanceModified;

	/**
	 * @brief The graphics view distance value
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	int GraphicsViewDistance;

	/**
	 * @brief Was the graphics anti-aliasing setting modified?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool GraphicsAntiAliasingModified;

	/**
	 * @brief The graphics anti-aliasing value
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	int GraphicsAntiAliasing;

	/**
	 * @brief Was the graphics post processing setting modified?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool GraphicsPostProcessingModified;

	/**
	 * @brief The graphics post processing value
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	int GraphicsPostProcessing;

	/**
	 * @brief Was the graphics shadow quality setting modified?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool GraphicsShadowQualityModified;

	/**
	 * @brief The graphics shadow quality value
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	int GraphicsShadowQuality;

	/**
	 * @brief Was the graphics texture quality setting modified?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool GraphicsTextureQualityModified;

	/**
	 * @brief The graphics texture quality value
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	int GraphicsTextureQuality;

	/**
	 * @brief Was the graphics visual effects setting modified?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool GraphicsVisualEffectsModified;

	/**
	 * @brief The graphics visual effects value
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	int GraphicsVisualEffects;

	/**
	 * @brief Was the graphics shading quality setting modified?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool GraphicsShadingQualityModified;

	/**
	 * @brief The graphics shading quality value
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	int GraphicsShadingQuality;

	/**
	 * @brief Was the graphics vsync setting modified?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool GraphicsVsyncModified;

	/**
	 * @brief The graphics vsync value
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool GraphicsVsync;

	/**
	 * @brief Was the graphics FPS indicator setting modified?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool GraphicsFpsIndicatorModified;

	/**
	 * @brief The graphics FPS indicator value
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	bool GraphicsFpsIndicator;

	/**
	 * @brief The color blind mode
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	int AccessibilityColorBlindMode;

	/**
	 * @brief The severity of the color blind mode
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	float AccessibilityColorBlindModeSeverity = 100.0f;

	/**
	 * @brief A map of all key bindings changed by the player
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	TMap<FName, FKey> KeyBindings;
};