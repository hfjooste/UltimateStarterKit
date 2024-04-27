// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "USKAudioComponent.generated.h"

/**
 * @brief Audio component used to adjust the pitch of the sound based on the game's time dilation
 */
UCLASS(Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent))
class USK_API UUSKAudioComponent : public UAudioComponent
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Should the slomo effect be enabled?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Audio")
	bool bEnableSlomoEffect;
	
	/**
	 * @brief The interp speed used to adjust the pitch of the sound
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "bEnableSlomoEffect", EditConditionHides),
		Category = "Ultimate Starter Kit|Audio")
	float PitchMultiplierInterpSpeed = 10.0f;

	/**
	 * @brief Constructor for the USK audio component
	 */
	UUSKAudioComponent();

protected:
	/**
	 * @brief Function called every frame on this ActorComponent
	 * @param DeltaTime The time since the last tick
	 * @param TickType The kind of tick this is, for example, are we paused, or 'simulating' in the editor
	 * @param ThisTickFunction Internal tick function struct that caused this to run
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;
};