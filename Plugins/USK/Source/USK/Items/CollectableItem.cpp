// Created by Henry Jooste

#include "CollectableItem.h"

#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "USK/Audio/AudioUtils.h"
#include "USK/Character/PlatformerCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Event when this actor overlaps another actor
 * @param OtherActor The other actor that caused the overlap event
 */
void ACollectableItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (ShouldBeCollected(OtherActor))
	{
		CollectItem();
	}
}

/**
 * @brief Collect the item
 */
void ACollectableItem::CollectItem()
{
	USK_LOG_INFO("Collecting item");
	
	UAudioUtils::PlayRandomSound(this, CollectedSoundEffects);
	if (CollectedParticleFx != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), CollectedParticleFx,
			GetActorLocation() + CollectedParticleFxSpawnOffset);
	}
	
	OnItemCollected();
	if (DestroyOnCollected)
	{
		Destroy();
	}
}

/**
 * @brief Called after the item is collected
 */
void ACollectableItem::OnItemCollected_Implementation() { }

/**
 * @brief Should the item be collected?
 * @param OtherActor The other actor that caused the overlap event
 * @return A boolean value indicating if the item should be collected
 */
bool ACollectableItem::ShouldBeCollected(const AActor* OtherActor)
{
	if (OtherActor == nullptr)
	{
		USK_LOG_ERROR("Other actor shouldn't be nullptr");
		return false;
	}
	
	switch (AllowedCollector)
	{
	case EAllowedCollector::AnyActor:
		return true;
	case EAllowedCollector::AnyPawn:
		return OtherActor->IsA(APawn::StaticClass());
	case EAllowedCollector::AnyCharacter:
		return OtherActor->IsA(ACharacter::StaticClass());
	case EAllowedCollector::AnyPlatformerCharacter:
		return OtherActor->IsA(APlatformerCharacter::StaticClass());
	case EAllowedCollector::PossessedPawn:
		return UGameplayStatics::GetPlayerPawn(GetWorld(), 0) == OtherActor;
	case EAllowedCollector::Custom:
		for (const TSubclassOf<AActor> AllowedCollectorType : AllowedCollectorTypes)
		{
			if (OtherActor->IsA(AllowedCollectorType))
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