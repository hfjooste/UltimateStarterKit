// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "MenuItemValueUpdateMethod.generated.h"

/**
 * @brief The method used to update the value of a menu item
 */
UENUM(BlueprintType)
enum class EMenuItemValueUpdateMethod : uint8
{
	/**
	 * @brief The value is only updated when the button is pressed
	 */
	SinglePress,
	
	/**
	 * @brief The value is updated while the button is held down
	 */
	Hold,
};