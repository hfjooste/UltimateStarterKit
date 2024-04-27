// Created by Henry Jooste

#pragma once

#include "GameFramework/Actor.h"
#include "MusicPlayer.generated.h"

/**
 * @brief Actor responsible for playing, pausing and stopping music. It also allows you to adjust music volume
 */
UCLASS()
class USK_API AMusicPlayer final : public AActor
{
	GENERATED_BODY()

	/**
	 * @brief The audio player component is responsible for the music playback
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Audio", meta=(AllowPrivateAccess = "true"))
	class UUSKAudioComponent* AudioPlayer;
	
public:
	/**
	 * @brief Should the music automatically play when the actor is spawned?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Audio")
	bool PlayOnStart = true;
	
	/**
	 * @brief Create a new instance of the MusicPlayer class 
	 */
	AMusicPlayer();

	/**
	 * @brief Get a reference to the audio component
	 * @return A reference to the audio component
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Audio")
	UUSKAudioComponent* GetAudioComponent() const;
	
	/**
	 * @brief Adjust the playback volume of the music 
	 * @param NewVolume The new volume of the music
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Audio")
	void SetVolume(float NewVolume);

	/**
	 * @brief Play the music
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Audio")
	void Play() const;
	
	/**
	 * @brief Pause the music
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Audio")
	void Pause() const;

	/**
	 * @brief Stop the music
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Audio")
	void Stop() const;

	/**
	 * @brief Fade out the music
	 * @param FadeDuration The duration of the fade
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Audio")
	void FadeOut(float FadeDuration) const;

	/**
	 * @brief Fade in the music
	 * @param FadeDuration The duration of the fade
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Audio")
	void FadeIn(float FadeDuration) const;

protected:
	/**
	 * @brief Overridable native event for when play begins for this actor
	 */
	virtual void BeginPlay() override;

private:
	/**
	 * @brief The current volume of the music
	 */
	float Volume;
};