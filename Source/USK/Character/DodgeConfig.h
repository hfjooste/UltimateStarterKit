// Created by Henry Jooste

#pragma once

#include "DodgeConfig.generated.h"

/**
 * @brief Structure used to store dodge configurations
 */
USTRUCT(BlueprintType)
struct USK_API FDodgeConfig
{
	GENERATED_USTRUCT_BODY()

	/**
	 * @brief The minimum forward velocity of the dodge
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit")
	float MinForwardVelocity;

	/**
	 * @brief The maximum forward velocity of the dodge
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit")
	float MaxForwardVelocity;

	/**
	 * @brief The minimum right velocity of the dodge
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit")
	float MinRightVelocity;

	/**
	 * @brief The maximum right velocity of the dodge
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit")
	float MaxRightVelocity;

	/**
	 * @brief The minimum up velocity of the dodge
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit")
	float MinUpVelocity;

	/**
	 * @brief The maximum up velocity of the dodge
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit")
	float MaxUpVelocity;

	/**
	 * @brief Should the forward velocity be randomly inverted?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit")
	bool bRandomInvertForwardVelocity;

	/**
	 * @brief Should the right velocity be randomly inverted?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit")
	bool bRandomInvertRightVelocity;

	/**
	 * @brief Should the up velocity be randomly inverted?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit")
	bool bRandomInvertUpVelocity;
};
