// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "InputDevice.generated.h"

/**
 * @brief An enum of all the supported input devices
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
	 * @brief Using an Xbox controller
	 */
	XboxController,

	/**
	 * @brief Using a Playstation controller
	 */
	PlaystationController,

	/**
	 * @brief Using a Nintendo Switch controller
	 */
	SwitchController,

	/**
	 * @brief Unknown device (used before initializing the input indicators)
	 */
	Unknown,
};