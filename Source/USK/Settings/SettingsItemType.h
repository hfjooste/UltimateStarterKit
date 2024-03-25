// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Launch/Resources/Version.h"
#include "SettingsItemType.generated.h"

/**
 * @brief An enum of all supported settings items
 */
UENUM(BlueprintType)
enum class ESettingsItemType : uint8
{
	/**
	 * @brief A setting not managed by the game instance
	 */
	None = 0,

	/**
	 * @brief The game difficulty setting
	 */
	GameplayDifficulty = 1,

	/**
	 * @brief The master audio volume setting
	 */
	AudioMaster = 50,

	/**
	 * @brief The music audio volume setting
	 */
	AudioMusic = 51,

	/**
	 * @brief The effects audio volume setting
	 */
	AudioEffects = 52,

	/**
	 * @brief The UI audio volume setting
	 */
	AudioUi = 53,

	/**
	 * @brief The voice audio volume setting
	 */
	AudioVoice = 54,

	/**
	 * @brief The graphics resolution setting
	 */
	GraphicsResolution = 100,

	/**
	 * @brief The graphics fullscreen setting
	 */
	GraphicsFullscreen = 101,

	/**
	 * @brief The graphics view distance setting
	 */
	GraphicsViewDistance = 102,

	/**
	 * @brief The graphics anti-aliasing setting
	 */
	GraphicsAntiAliasing = 103,

	/**
	 * @brief The graphics post processing setting
	 */
	GraphicsPostProcessing = 104,

	/**
	 * @brief The graphics shadow quality setting
	 */
	GraphicsShadowQuality = 105,

	/**
	 * @brief The graphics texture quality setting
	 */
	GraphicsTextureQuality = 106,

	/**
	 * @brief The graphics visual effects setting
	 */
	GraphicsVisualEffects = 107,

	/**
	 * @brief The graphics shading quality setting
	 */
	GraphicsShadingQuality = 108,

	/**
	 * @brief The graphics vsync setting
	 */
	GraphicsVSync = 109,

	/**
	 * @brief The graphics FPS indicator setting
	 */
	GraphicsFpsIndicator = 110,

	/**
	 * @brief The accessibility color blind mode setting 
	 */
	AccessibilityColorBlindMode = 150,

	/**
	 * @brief The accessibility color blind mode severity setting
	 */
	AccessibilityColorBlindModeSeverity = 151,
	
	/**
	 * @brief Remap the controls
	 */
	ControlsRemap = 200,
};