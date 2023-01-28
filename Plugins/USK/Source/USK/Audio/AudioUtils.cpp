// Created by Henry Jooste

#include "AudioUtils.h"
#include "Kismet/GameplayStatics.h"
#include "USK/Logger/Log.h"

/**
 * @brief Play a 2D sound
 * @param WorldContext The top level object representing a map
 * @param SoundFX The USoundBase to play
 */
void UAudioUtils::PlaySound2D(const UObject* WorldContext, USoundBase* SoundFX)
{
	if (SoundFX == nullptr)
	{
		ULog::Error("AudioUtils::PlaySound2D", "Trying to play a nullptr 2D sound");
		return;
	}

	ULog::Info("AudioUtils::PlaySound2D", "Playing 2D sound");
	UGameplayStatics::PlaySound2D(WorldContext, SoundFX);
}

/**
 * @brief Play a random 2D sound
 * @param WorldContext The top level object representing a map
 * @param SoundFX The array of USoundBase to select the random sound from
 */
void UAudioUtils::PlayRandomSound2D(const UObject* WorldContext, TArray<USoundBase*> SoundFX)
{
	ULog::Info("AudioUtils::PlayRandomSound2D", "Playing random 2D sound");
	const int Index = FMath::RandRange(0, SoundFX.Num() - 1);
	PlaySound2D(WorldContext, SoundFX[Index]);
}

/**
 * @brief Play a sound at the specified actor's location
 * @param Actor The actor where the sound will be player
 * @param SoundFX The USoundBase to play
 */
void UAudioUtils::PlaySound(AActor* Actor, USoundBase* SoundFX)
{
	if (Actor == nullptr || SoundFX == nullptr)
	{
		ULog::Error("AudioUtils::PlaySound", "Trying to play a nullptr sound at actor location");
		return;
	}

	ULog::Info("AudioUtils::PlaySound", "Playing sound at actor location");
	UGameplayStatics::PlaySoundAtLocation(Actor->GetWorld(), SoundFX, Actor->GetActorLocation());
}

/**
 * @brief Play a random sound at the specified actor's location
 * @param Actor The actor where the sound will be player
 * @param SoundFX The array of USoundBase to select the random sound from
 */
void UAudioUtils::PlayRandomSound(AActor* Actor, TArray<USoundBase*> SoundFX)
{
	ULog::Info("AudioUtils::PlayRandomSound", "Playing random sound at actor location");
	const int Index = FMath::RandRange(0, SoundFX.Num() - 1);
	PlaySound(Actor, SoundFX[Index]);
}
