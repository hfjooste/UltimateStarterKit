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
	AudioVoice	
};	
