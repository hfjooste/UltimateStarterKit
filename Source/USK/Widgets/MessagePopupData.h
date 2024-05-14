// Created by Henry Jooste

#pragma once

#include "MessagePopupData.generated.h"

/**
 * @brief The data used to display a message popup
 */
USTRUCT(BlueprintType)
struct USK_API FMessagePopupData
{
	GENERATED_USTRUCT_BODY()

	/**
	 * @brief The title displayed in the message popup
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	FText Title = FText::GetEmpty();

	/**
	 * @brief The text displayed in the message popup
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	FText Message = FText::GetEmpty();

	/**
	 * @brief The text displayed on the positive button
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	FText PositiveButtonText = FText::GetEmpty();

	/**
	 * @brief The text displayed on the negative button
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	FText NegativeButtonText = FText::GetEmpty();

	/**
	 * @brief The text displayed on the neutral button
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	FText NeutralButtonText = FText::GetEmpty();
};
