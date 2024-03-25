// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestComponent.generated.h"

class AQuestManager;
class UQuest;

/**
 * @brief Component used to update the actor based on the current quest and point
 */
UCLASS(ClassGroup=("UltimateStarterKit"), DisplayName="Quest Component", meta=(BlueprintSpawnableComponent))
class USK_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/**
	 * @brief The quest associated with the component
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Quests")
	UQuest* Quest;

	/**
	 * @brief The point of the quest associated with the component
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Quests")
	int RequiredPoint;

	/**
	 * @brief Should the actor be hidden if the quest is not active?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Quests")
	bool bHideIfQuestNotActive = true;

	/**
	 * @brief Should the actor be hidden if the quest point has been completed?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Quests")
	bool bHideAfterPointCompleted = true;

	/**
	 * @brief Called after the quest point is completed
	 */
	void OnQuestPointCompleted() const;

protected:
	/**
	 * @brief Overridable native event for when play begins for this actor
	 */
	virtual void BeginPlay() override;

private:
	/**
	 * @brief A reference to the quest manager
	 */
	UPROPERTY()
	AQuestManager* QuestManager;

	/**
	 * @brief Update the visibility of the actor
	 * @param CurrentQuest The current active quest
	 * @param CurrentPoint The current point of the active quest
	 */
	UFUNCTION()
	void UpdateVisibility(UQuest* CurrentQuest, int CurrentPoint);
};
