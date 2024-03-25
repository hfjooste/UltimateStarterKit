// Created by Henry Jooste

#include "CollectableItem.h"

#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "USK/Audio/AudioUtils.h"
#include "USK/Character/USKCharacter.h"
#include "USK/Components/AttractComponent.h"
#include "USK/Components/InteractTrigger.h"
#include "USK/Logger/Log.h"
#include "USK/Quests/QuestComponent.h"

/**
 * @brief Overridable native event for when play begins for this actor
 */
void ACollectableItem::BeginPlay()
{
	Super::BeginPlay();
	bCollectOnInteract = IsValid(GetComponentByClass(UInteractTrigger::StaticClass()));
}

/**
 * @brief Event when this actor overlaps another actor
 * @param OtherActor The other actor that caused the overlap event
 */
void ACollectableItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (!bCollectOnInteract && CanCollectItem(OtherActor) &&
		!IsValid(GetComponentByClass(UAttractComponent::StaticClass())))
	{
		CollectItem(OtherActor);
	}
}

/**
 * @brief Check if the item can be collected
 * @param Collector A pointer to the actor that is trying to collect the item
 * @return A boolean value indicating if the item can be collected
 */
bool ACollectableItem::CanCollectItem_Implementation(AActor* Collector) const
{
	if (!IsValid(Collector))
	{
		USK_LOG_ERROR("Collector is invalid");
		return false;
	}
	
	switch (AllowedCollector)
	{
	case EAllowedCollector::AnyActor:
		return true;
	case EAllowedCollector::AnyPawn:
		return Collector->IsA(APawn::StaticClass());
	case EAllowedCollector::AnyCharacter:
		return Collector->IsA(ACharacter::StaticClass());
	case EAllowedCollector::AnyUskCharacter:
		return Collector->IsA(AUSKCharacter::StaticClass());
	case EAllowedCollector::PossessedPawn:
		return UGameplayStatics::GetPlayerPawn(GetWorld(), 0) == Collector;
	case EAllowedCollector::Custom:
		for (const TSubclassOf<AActor> AllowedCollectorType : AllowedCollectorTypes)
		{
			if (Collector->IsA(AllowedCollectorType))
			{
				return true;
			}
		}
		return false;
	default:
		USK_LOG_WARNING("Unknown allowed collector type");
		return false;
	}
}

/**
 * @brief Collect the item
 * @param Collector A pointer to the actor that collected the item
 */
void ACollectableItem::CollectItem(AActor* Collector)
{
	USK_LOG_INFO("Collecting item");
	
	UAudioUtils::PlayRandomSound(this, CollectedSoundEffects);
	if (CollectedParticleFx != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), CollectedParticleFx,
			GetActorLocation() + CollectedParticleFxSpawnOffset);
	}

	UQuestComponent* QuestComponent = dynamic_cast<UQuestComponent*>(
		GetComponentByClass(UQuestComponent::StaticClass()));
	if (IsValid(QuestComponent) && bCompleteQuestPointAfterCollecting)
	{
		QuestComponent->OnQuestPointCompleted();
	}
	
	OnItemCollected(Collector);
	if (DestroyOnCollected)
	{
		Destroy();
	}
}

/**
 * @brief Called after the item is collected
 * @param Collector A pointer to the actor that collected the item
 */
void ACollectableItem::OnItemCollected_Implementation(AActor* Collector) { }