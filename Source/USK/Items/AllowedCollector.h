// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "AllowedCollector.generated.h"

/**
 * @brief The types of actor(s) that can collect an item
 */
UENUM(BlueprintType)
enum class EAllowedCollector : uint8
{
	/**
	 * @brief Any actor can collect the item
	 */
	AnyActor,

	/**
	 * @brief Any pawn can collect the item
	 */
	AnyPawn,

	/**
	 * @brief Any character can collect the item
	 */
	AnyCharacter,

	/**
	 * @brief Any USK character can collect the item
	 */
	AnyUskCharacter,

	/**
	 * @brief Only the possessed pawn can collect the item
	 */
	PossessedPawn,

	/**
	 * @brief A custom array of actor types can collect the item
	 */
	Custom
};	
