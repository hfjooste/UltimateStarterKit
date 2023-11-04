// Created by Henry Jooste

#include "QuestWidget.h"

#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"
#include "USK/Logger/Log.h"
#include "USK/Quests/Quest.h"

/**
 * @brief Show the quest widget
 * @param Quest The current quest
 * @param Point The current quest point
 */
void UQuestWidget::Show(UQuest* Quest, const int Point)
{
	if (!IsValid(Quest) || Point < 0 || Point >= Quest->Points.Num())
	{
		USK_LOG_ERROR("Invalid quest data");
		return;
	}

	if (IsValid(QuestTitleText))
	{
		QuestTitleText->SetText(Quest->Name);
	}

	if (IsValid(QuestDetailsText))
	{
		QuestDetailsText->SetText(Quest->Points[Point]);
	}
	
	USK_LOG_TRACE("Showing quest widget");
	AddToViewport();
	
	if (IsValid(ShowAnimation))
	{
		USK_LOG_TRACE("Playing show animation");
		PlayAnimation(ShowAnimation);
	}
}

/**
 * @brief Hide the quest widget
 */
void UQuestWidget::Hide()
{
	USK_LOG_TRACE("Hiding quest widget");
	RemoveFromParent();
}