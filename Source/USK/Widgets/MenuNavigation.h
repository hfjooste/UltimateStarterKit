// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "MenuNavigation.generated.h"

/**
 * @brief All the supported menu navigation types
 */
UENUM(BlueprintType)
enum class EMenuNavigation : uint8
{
	/**
	 * @brief No navigation allowed
	 */
	Disabled,
	
	/**
	 * @brief Highlight a different menu item
	 */
	HighlightItem,

	/**
	 * @brief Increase or decrease the value
	 */
	IncreaseDecreaseValue
};