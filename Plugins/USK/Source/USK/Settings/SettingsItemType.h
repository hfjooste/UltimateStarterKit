// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
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
	None,

	/**
	 * @brief The master audio volume setting
	 */
	AudioMaster,

	/**
	 * @brief The music audio volume setting
	 */
	AudioMusic,

	/**
	 * @brief The effects audio volume setting
	 */
	AudioEffects,

	/**
	 * @brief The UI audio volume setting
	 */
	AudioUi,

	/**
	 * @brief The voice audio volume setting
	 */
	AudioVoice,

	/**
	 * @brief The graphics resolution setting
	 */
	GraphicsResolution,

	/**
	 * @brief The graphics fullscreen setting
	 */
	GraphicsFullscreen,

	/**
	 * @brief The graphics view distance setting
	 */
	GraphicsViewDistance,

	/**
	 * @brief The graphics anti-aliasing setting
	 */
	GraphicsAntiAliasing,

	/**
	 * @brief The graphics post processing setting
	 */
	GraphicsPostProcessing,

	/**
	 * @brief The graphics shadow quality setting
	 */
	GraphicsShadowQuality,

	/**
	 * @brief The graphics texture quality setting
	 */
	GraphicsTextureQuality,

	/**
	 * @brief The graphics visual effects setting
	 */
	GraphicsVisualEffects,

	/**
	 * @brief The graphics shading quality setting
	 */
	GraphicsShadingQuality,

	/**
	 * @brief The graphics vsync setting
	 */
	GraphicsVSync,

	/**
	 * @brief The graphics FPS indicator setting
	 */
	GraphicsFpsIndicator
};