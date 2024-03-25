// Created by Henry Jooste

#include "QuestComponent.h"

#include "Quest.h"
#include "QuestManager.h"
#include "Kismet/GameplayStatics.h"
#include "USK/Logger/Log.h"

/**
 * @brief Overridable native event for when play begins for this actor
 */
void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();

	QuestManager = dynamic_cast<AQuestManager*>(
		UGameplayStatics::GetActorOfClass(GetWorld(), AQuestManager::StaticClass()));
	if (!IsValid(QuestManager))
	{
		USK_LOG_ERROR("Quest manager not found");
		return;
	}

	UpdateVisibility(QuestManager->GetCurrentQuest(), QuestManager->GetCurrentQuestPoint());
	QuestManager->OnQuestUpdated.AddDynamic(this, &UQuestComponent::UpdateVisibility);
}

/**
 * @brief Called after the quest point is completed
 */
void UQuestComponent::OnQuestPointCompleted() const
{
	if (!IsValid(QuestManager))
	{
		USK_LOG_ERROR("Quest manager is invalid");
		return;
	}

	QuestManager->OnQuestPointCompleted(Quest);
}

/**
 * @brief Update the visibility of the actor
 * @param CurrentQuest The current active quest
 * @param CurrentPoint The current point of the active quest
 */
void UQuestComponent::UpdateVisibility(UQuest* CurrentQuest, int CurrentPoint)
{
	AActor* OwnerActor = GetOwner();
	if (!IsValid(OwnerActor))
	{
		USK_LOG_ERROR("Owner actor is not valid");
		return;
	}

	if (!IsValid(Quest))
	{
		USK_LOG_ERROR("Quest is not valid");
		OwnerActor->SetActorHiddenInGame(true);
		OwnerActor->SetActorEnableCollision(false);
		return;
	}
	
	if (!IsValid(CurrentQuest) || !QuestManager->IsQuestActive(Quest))
	{
		OwnerActor->SetActorHiddenInGame(bHideIfQuestNotActive);
		OwnerActor->SetActorEnableCollision(!bHideIfQuestNotActive);
		return;
	}

	const bool ShouldShow = CurrentPoint == RequiredPoint || (!bHideAfterPointCompleted && CurrentPoint >= RequiredPoint);
	OwnerActor->SetActorHiddenInGame(!ShouldShow);
	OwnerActor->SetActorEnableCollision(ShouldShow);
}
