// Created by Henry Jooste

#include "InteractWidget.h"

#include "Animation/WidgetAnimation.h"
#include "USK/Logger/Log.h"

/**
 * @brief Show the interact widget
 */
void UInteractWidget::Show()
{
	USK_LOG_TRACE("Showing interact widget");
	AddToViewport();
	
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