// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Platform.generated.h"

/**
 * @brief The types of supported platform types
 */
UENUM(BlueprintType)
enum class EPlatform : uint8
{
	/**
	 * @brief An unknown or unsupported platform
	 */
	Unknown,

	/**
	 * @brief Windows (any architecture)
	 */
	Windows,

	/**
	 * @brief MacOS (any architecture)
	 */
	MacOS,

	/**
	 * @brief Linux (any architecture)
	 */
	Linux,

	/**
	 * @brief Console MX
	 */
	ConsoleMx,

	/**
	 * @brief Console SP
	 */
	ConsoleSp,

	/**
	 * @brief Console NS
	 */
	ConsoleNs,

	/**
	 * @brief Android (any architecture)
	 */
	Android,

	/**
	 * @brief iOS
	 */
	IOS
};