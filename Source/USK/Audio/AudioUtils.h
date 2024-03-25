// Created by Henry Jooste

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AudioUtils.generated.h"

/**
 * @brief The audio utils class is used to easily play sound effects
 */
UCLASS()
class USK_API UAudioUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Play a 2D sound
	 * @param WorldContext The top level object representing a map
	 * @param SoundFX The USoundBase to play
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Ultimate Starter Kit|Audio", meta=(WorldContext="WorldContext"))
	static void PlaySound2D(const UObject* WorldContext, USoundBase* SoundFX);

	/**
	 * @brief Play a random 2D sound
	 * @param WorldContext The top level object representing a map
	 * @param SoundFX The array of USoundBase to select the random sound from
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Ultimate Starter Kit|Audio", meta=(WorldContext="WorldContext"))
	static void PlayRandomSound2D(const UObject* WorldContext, TArray<USoundBase*> SoundFX);
	
	/**
	 * @brief Play a sound at the specified actor's location
	 * @param Actor The actor where the sound will be played
	 * @param SoundFX The USoundBase to play
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Audio")
	static void PlaySound(AActor* Actor, USoundBase* SoundFX);

	/**
	 * @brief Play a random sound at the specified actor's location
	 * @param Actor The actor where the sound will be played
	 * @param SoundFX The array of USoundBase to select the random sound from
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Audio")
	static void PlayRandomSound(AActor* Actor, TArray<USoundBase*> SoundFX);
};
