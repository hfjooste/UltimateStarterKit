// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "DialogueTransitionType.generated.h"

/**
 * @brief The type of transition used by the dialogue entry
 */
UENUM(BlueprintType)
enum class EDialogueTransitionType : uint8
{
	/**
	 * @brief Automatically advance to the next dialogue entry
	 */
	Auto,

	/**
	 * @brief Give the player a few choices used to create branches in the dialogue
	 */
	Choice
};