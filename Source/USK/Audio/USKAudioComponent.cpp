// Created by Henry Jooste

#include "USKAudioComponent.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

/**
 * @brief Constructor for the USK audio component
 */
UUSKAudioComponent::UUSKAudioComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

/**
 * @brief Function called every frame on this ActorComponent
 * @param DeltaTime The time since the last tick
 * @param TickType The kind of tick this is, for example, are we paused, or 'simulating' in the editor
 * @param ThisTickFunction Internal tick function struct that caused this to run
 */
void UUSKAudioComponent::TickComponent(const float DeltaTime, const ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bEnableSlomoEffect)
	{
		const float TimeDilation = UGameplayStatics::GetGlobalTimeDilation(GetWorld());
		SetPitchMultiplier(FMath::FInterpTo(PitchMultiplier, TimeDilation,
			DeltaTime, PitchMultiplierInterpSpeed));	
	}
}