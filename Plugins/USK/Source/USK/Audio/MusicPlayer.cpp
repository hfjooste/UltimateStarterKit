// Created by Henry Jooste

#include "MusicPlayer.h"
#include "USK/Logger/Log.h"
#include "Components/AudioComponent.h"

/**
 * @brief Create a new instance of the MusicPlayer class
 */
AMusicPlayer::AMusicPlayer()
{
	PrimaryActorTick.bCanEverTick = false;
	AudioPlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Player"));
}

/**
 * @brief Overridable native event for when play begins for this actor
 */
void AMusicPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (!PlayOnStart)
	{
		AudioPlayer->Stop();
		return;
	}

	USK_LOG_INFO("Automatically playing music");
	AudioPlayer->Play();
}

/**
 * @brief Adjust the playback volume of the music
 * @param Volume The new volume of the music
 */
void AMusicPlayer::SetVolume(const float Volume) const
{
	if (AudioPlayer == nullptr)
	{
		USK_LOG_ERROR("AudioPlayer is nullptr");
		return;
	}

	AudioPlayer->SetVolumeMultiplier(Volume);	
	USK_LOG_INFO(*FString::Format(TEXT("Volume changed to {0}"), { FString::SanitizeFloat(Volume, 5) }));
}

/**
 * @brief Play the music
 */
void AMusicPlayer::Play() const
{
	if (AudioPlayer == nullptr)
	{
		USK_LOG_ERROR("AudioPlayer is nullptr");
		return;
	}

	if (AudioPlayer->bIsPaused)
	{
		AudioPlayer->SetPaused(false);
		USK_LOG_INFO("Music resumed");
		return;
	}

	if (!AudioPlayer->IsPlaying())
	{
		AudioPlayer->Play();
		USK_LOG_INFO("Music played");
		return;
	}

	USK_LOG_WARNING("Music already playing and is not paused");
}

/**
 * @brief Pause the music
 */
void AMusicPlayer::Pause() const
{
	if (AudioPlayer == nullptr)
	{
		USK_LOG_ERROR("AudioPlayer is nullptr");
		return;
	}

	if (AudioPlayer->bIsPaused)
	{
		USK_LOG_WARNING("Music already paused");
		return;
	}

	if (!AudioPlayer->IsPlaying())
	{
		USK_LOG_WARNING("Music is not playing");
		return;
	}

	AudioPlayer->SetPaused(true);
	USK_LOG_INFO("Music paused");
}
/**
 * @brief Stop the music
 */
void AMusicPlayer::Stop() const
{
	if (AudioPlayer == nullptr)
	{
		USK_LOG_ERROR("AudioPlayer is nullptr");
		return;
	}

	if (!AudioPlayer->bIsPaused && !AudioPlayer->IsPlaying())
	{
		USK_LOG_WARNING("Music already stopped");
		return;
	}

	AudioPlayer->Stop();
	USK_LOG_INFO("Music stopped");
}