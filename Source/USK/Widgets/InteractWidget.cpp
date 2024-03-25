// Created by Henry Jooste

#include "InteractWidget.h"

#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"
#include "USK/Logger/Log.h"

/**
 * @brief Show the interact widget
 * @param BeforeText The text displayed before the input indicator
 * @param AfterText The text displayed after the input indicator
 */
void UInteractWidget::Show(const FText BeforeText, const FText AfterText)
{
	USK_LOG_TRACE("Showing interact widget");
	AddToViewport();

	if (IsValid(BeforeTextBlock))
	{
		BeforeTextBlock->SetText(BeforeText);
	}

	if (IsValid(AfterTextBlock))
	{
		AfterTextBlock->SetText(AfterText);
	}
	
	if (IsValid(ShowAnimation))
	{
		USK_LOG_TRACE("Playing show animation");
		PlayAnimation(ShowAnimation);
	}
}

/**
 * @brief Hide the interact widget
 */
void UInteractWidget::Hide()
{
	USK_LOG_TRACE("Hiding interact widget");
	RemoveFromParent();
}