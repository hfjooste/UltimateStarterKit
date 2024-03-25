// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USK/Widgets/QuestWidget.h"
#include "QuestManager.generated.h"

class UQuest;

/**
 * @brief Actor responsible for managing quests
 */
UCLASS()
class USK_API AQuestManager : public AActor
{
	GENERATED_BODY()

	/**
	 * @brief Event used to notify other classes when a quest is completed
	 * @param Quest The quest that was completed
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuestCompleted, UQuest*, Quest);

	/**
	 * @brief Event used to notify other classes when a quest is updated
	 * @param CurrentQuest The current active quest
	 * @param CurrentPoint The current point of the active quest
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FQuestUpdated, UQuest*, CurrentQuest, int, CurrentPoint);
	
public:
	/**
	 * @brief The widget class used to display the current quest
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Quests")
	TSubclassOf<UQuestWidget> QuestWidgetClass;

	/**
	 * @brief Event used to notify other classes when a quest is completed
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Quests")
	FQuestCompleted OnQuestCompleted;

	/**
	 * @brief Event used to notify other classes when a quest is updated
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Quests")
	FQuestUpdated OnQuestUpdated;

	/**
	 * @brief Start the specified quest
	 * @param Quest The quest to start
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Quests")
	void StartQuest(UQuest* Quest);

	/**
	 * @brief Complete the current quest point
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Quests")
	void OnQuestPointCompleted(const UQuest* Quest);

	/**
	 * @brief Get the current quest
	 * @return The current quest
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Quests")
	UQuest* GetCurrentQuest() const;

	/**
	 * @brief Get the current quest point
	 * @return The current quest point
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Quests")
	int GetCurrentQuestPoint() const;

	/**
	 * @brief Check if the specified quest is active
	 * @param Quest The quest to check
	 * @return A boolean value indicating if the quest is active
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Quests")
	bool IsQuestActive(const UQuest* Quest) const;

private:
	/**
	 * @brief A reference to the quest widget
	 */
	UPROPERTY()
	UQuestWidget* QuestWidget;

	/**
	 * @brief The current active quest
	 */
	UPROPERTY()
	UQuest* CurrentQuest;

	/**
	 * @brief The current active quest point
	 */
	int QuestPoint;

	/**
	 * @brief Update the quest widget
	 */
	void UpdateQuestWidget();
};
