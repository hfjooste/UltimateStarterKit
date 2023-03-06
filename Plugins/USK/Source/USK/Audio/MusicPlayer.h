// Created by Henry Jooste

#pragma once

#include "GameFramework/Actor.h"
#include "MusicPlayer.generated.h"

/**
 * @brief Actor that is responsible for play music
 */
UCLASS()
class USK_API AMusicPlayer final : public AActor
{
	GENERATED_BODY()

	/**
	 * @brief The audio player component is responsible for the music playback
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Audio", meta=(AllowPrivateAccess = "true"))
	class UAudioComponent* AudioPlayer;
	
public:
	/**
	 * @brief Should the music automatically play when the actor is spawned?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit")
	bool PlayOnStart = true;
	
	/**
	 * @brief Create a new instance of the MusicPlayer class 
	 */
	AMusicPlayer();
	
	/**
	 * @brief Adjust the playback volume of the music 
	 * @param Volume The new volume of the music
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Audio")
	void SetVolume(float Volume) const;

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

protected:
	/**
	 * @brief Overridable native event for when play begins for this actor
	 */
	virtual void BeginPlay() override;
};