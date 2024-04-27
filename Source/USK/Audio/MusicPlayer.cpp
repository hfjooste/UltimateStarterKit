// Created by Henry Jooste

#include "MusicPlayer.h"

#include "USKAudioComponent.h"
#include "USK/Logger/Log.h"
#include "Components/AudioComponent.h"

/**
 * @brief Create a new instance of the MusicPlayer class
 */
AMusicPlayer::AMusicPlayer()
{
	PrimaryActorTick.bCanEverTick = false;
	AudioPlayer = CreateDefaultSubobject<UUSKAudioComponent>(TEXT("Audio Player"));
}

/**
 * @brief Get a reference to the audio component
 * @return A reference to the audio component
 */
UUSKAudioComponent* AMusicPlayer::GetAudioComponent() const
{
	return AudioPlayer;
}

/**
 * @brief Overridable native event for when play begins for this actor
 */
void AMusicPlayer::BeginPlay()
{
	Super::BeginPlay();

	Volume = AudioPlayer->VolumeMultiplier;
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
 * @param NewVolume The new volume of the music
 */
void AMusicPlayer::SetVolume(const float NewVolume)
{
	if (AudioPlayer == nullptr)
	{
		USK_LOG_ERROR("AudioPlayer is nullptr");
		return;
	}

	Volume = NewVolume;
	AudioPlayer->SetVolumeMultiplier(NewVolume);	
	USK_LOG_INFO(*FString::Format(TEXT("Volume changed to {0}"), { FString::SanitizeFloat(NewVolume, 5) }));
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

/**
 * @brief Fade out the music
 * @param FadeDuration The duration of the fade
 */
void AMusicPlayer::FadeOut(const float FadeDuration) const
{
	if (!IsValid(AudioPlayer))
	{
		USK_LOG_ERROR("AudioPlayer is not valid");
		return;
	}

	AudioPlayer->FadeOut(FadeDuration, 0.0f);
}

/**
 * @brief Fade in the music
 * @param FadeDuration The duration of the fade
 */
void AMusicPlayer::FadeIn(const float FadeDuration) const
{
	if (!IsValid(AudioPlayer))
	{
		USK_LOG_ERROR("AudioPlayer is not valid");
		return;
	}

	AudioPlayer->FadeIn(FadeDuration, Volume);
}
