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
	FText Title;

	/**
	 * @brief The text displayed in the message popup
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	FText Message;

	/**
	 * @brief Should the positive button be shown?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	bool bShowPositiveButton;

	/**
	 * @brief The text displayed on the positive button
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI",
		meta = (EditCondition = "bShowPositiveButton", EditConditionHides))
	FText PositiveButtonText;

	/**
	 * @brief Should the negative button be shown?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	bool bShowNegativeButton;

	/**
	 * @brief The text displayed on the negative button
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI",
		meta = (EditCondition = "bShowNegativeButton", EditConditionHides))
	FText NegativeButtonText;

	/**
	 * @brief Should the neutral button be shown?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	bool bShowNeutralButton;

	/**
	 * @brief The text displayed on the neutral button
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI",
		meta = (EditCondition = "bShowNeutralButton", EditConditionHides))
	FText NeutralButtonText;
};
