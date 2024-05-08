// Created by Henry Jooste

#pragma once

/**
 * @brief The different FPS Counter types
 */
UENUM(BlueprintType)
enum class ESettingsFpsCounterType : uint8
{
	/**
	 * @brief The FPS counter is disabled
	 */
	Disabled,

	/**
	 * @brief The FPS counter only displays the current framerate
	 */
	Simple,

	/**
	 * @brief The FPS counter displays the current framerate including additional information
	 */
	Detailed
};