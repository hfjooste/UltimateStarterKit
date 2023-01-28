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
		ULog::Error("MusicPlayer::SetVolume", "AudioPlayer is nullptr");
		return;
	}

	AudioPlayer->SetVolumeMultiplier(Volume);
	ULog::Info("MusicPlayer::SetVolume",
		FString("Volume changed to ").Append(FString::SanitizeFloat(Volume, 5)));
}

/**
 * @brief Play the music
 */
void AMusicPlayer::Play() const
{
	if (AudioPlayer == nullptr)
	{
		ULog::Error("MusicPlayer::Play", "AudioPlayer is nullptr");
		return;
	}

	if (AudioPlayer->bIsPaused)
	{
		AudioPlayer->SetPaused(false);
		ULog::Info("MusicPlayer::Play", "Music resumed");
		return;
	}

	if (!AudioPlayer->IsPlaying())
	{
		AudioPlayer->Play();
		ULog::Info("MusicPlayer::Play", "Music played");
		return;
	}

	ULog::Warning("MusicPlayer::Play", "Music already playing and is not paused");
}

/**
 * @brief Pause the music
 */
void AMusicPlayer::Pause() const
{
	if (AudioPlayer == nullptr)
	{
		ULog::Error("MusicPlayer::Pause", "AudioPlayer is nullptr");
		return;
	}

	if (AudioPlayer->bIsPaused)
	{
		ULog::Warning("MusicPlayer::Pause", "Music already paused");
		return;
	}

	if (!AudioPlayer->IsPlaying())
	{
		ULog::Warning("MusicPlayer::Pause", "Music is not playing");
		return;
	}

	AudioPlayer->SetPaused(true);
	ULog::Info("MusicPlayer::Pause", "Music paused");
}
/**
 * @brief Stop the music
 */
void AMusicPlayer::Stop() const
{
	if (AudioPlayer == nullptr)
	{
		ULog::Error("MusicPlayer::Stop", "AudioPlayer is nullptr");
		return;
	}

	if (!AudioPlayer->bIsPaused && !AudioPlayer->IsPlaying())
	{
		ULog::Warning("MusicPlayer::Stop", "Music already stopped");
		return;
	}

	AudioPlayer->Stop();
	ULog::Info("MusicPlayer::Stop", "Music stopped");
}