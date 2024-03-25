// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "InputDevice.generated.h"

/**
 * @brief Supported input devices. This is used to update the input indicators when using different input devices
 */
UENUM(BlueprintType)
enum class EInputDevice : uint8
{
	/**
	 * @brief Using a keyboard and mouse
	 */
	KeyboardMouse,

	/**
	 * @brief Using a controller on a desktop build
	 */
	GenericController,

	/**
	 * @brief Using an Console MX controller
	 */
	MxController,

	/**
	 * @brief Using a Console SP controller
	 */
	SpController,

	/**
	 * @brief Using a Console NS controller
	 */
	NsController,

	/**
	 * @brief Unknown device (used before initializing the input indicators)
	 */
	Unknown,
};