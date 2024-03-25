// Created by Henry Jooste

#pragma once

#include "CreditsEntry.generated.h"

/**
 * @brief An single credits entry displayed by the credits widget
 */
USTRUCT(BlueprintType)
struct USK_API FCreditsEntry
{
	GENERATED_USTRUCT_BODY()

	/**
	 * @brief The title for the credits entry
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Credits")
	FText Title;

	/**
	 * @brief The text for the credits entry
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Credits")
	FText Text;

	/**
	 * @brief The duration of the credits entry
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Credits")
	float Duration = 5.0f;

	/**
	 * @brief The horizontal alignment applied to the credits widget when displaying this entry
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Credits")
	TEnumAsByte<EHorizontalAlignment> HorizontalAlignment = HAlign_Center;

	/**
	 * @brief The vertical alignment applied to the credits widget when displaying this entry
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Credits")
	TEnumAsByte<EVerticalAlignment> VerticalAlignment = VAlign_Center;
};