// Created by Henry Jooste

#include "QuestManager.h"
#include "Quest.h"

/**
 * @brief Start the specified quest
 * @param Quest The quest to start
 */
void AQuestManager::StartQuest(UQuest* Quest)
{
	CurrentQuest = Quest;
	QuestPoint = 0;
	UpdateQuestWidget();
	
	OnQuestUpdated.Broadcast(CurrentQuest, QuestPoint);
}

/**
 * @brief Complete the current quest point
 */
void AQuestManager::OnQuestPointCompleted(const UQuest* Quest)
{
	if (!IsQuestActive(Quest))
	{
		return;
	}

	QuestPoint++;
	if (QuestPoint >= CurrentQuest->Points.Num())
	{
		OnQuestCompleted.Broadcast(CurrentQuest);
		StartQuest(nullptr);
		return;
	}

	UpdateQuestWidget();
	OnQuestUpdated.Broadcast(CurrentQuest, QuestPoint);
}

/**
 * @brief Get the current quest
 * @return The current quest
 */
UQuest* AQuestManager::GetCurrentQuest() const
{
	return CurrentQuest;
}

/**
 * @brief Get the current quest point
 * @return The current quest point
 */
int AQuestManager::GetCurrentQuestPoint() const
{
	return QuestPoint;
}

/**
 * @brief Check if the specified quest is active
 * @param Quest The quest to check
 * @return A boolean value indicating if the quest is active
 */
bool AQuestManager::IsQuestActive(const UQuest* Quest) const
{
	return IsValid(Quest) && IsValid(CurrentQuest) && Quest->Id == CurrentQuest->Id;
}

/**
 * @brief Update the quest widget
 */
void AQuestManager::UpdateQuestWidget()
{
	if (IsValid(QuestWidget))
	{
		QuestWidget->Hide();
		QuestWidget = nullptr;
	}

	if (IsValid(CurrentQuest) && IsValid(QuestWidgetClass))
	{
		QuestWidget = CreateWidget<UQuestWidget>(GetWorld(), QuestWidgetClass);
		QuestWidget->Show(CurrentQuest, QuestPoint);
	}
}