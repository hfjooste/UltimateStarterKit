// Created by Henry Jooste

#include "USKPostProcessActor.h"

#include "Components/PostProcessComponent.h"
#include "USK/Core/USKGameInstance.h"
#include "USK/Logger/Log.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Constructor for the post process actor
 */
AUSKPostProcessActor::AUSKPostProcessActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComponent"));
	PostProcessComponent->SetupAttachment(RootComponent);
}

/**
 * @brief Overridable native event for when play begins for this actor
 */
void AUSKPostProcessActor::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = dynamic_cast<UUSKGameInstance*>(GetGameInstance());
	if (!IsValid(GameInstance))
	{
		USK_LOG_ERROR("Game instance is not UUSKGameInstance");
		return;
	}

	GameInstance->AddPostProcessActor(this);
	const USettingsData* SettingsData = USettingsUtils::LoadSettings();
	
	const int Value = SettingsData->VisualsMotionBlurModified
		? SettingsData->VisualsMotionBlur
		: GameInstance->SettingsConfig->VisualsMotionBlurDefault;

	TArray<float> MotionBlurKeys;
	GameInstance->SettingsConfig->VisualsMotionBlurValues.GetKeys(MotionBlurKeys);
	if (Value < 0 || Value >= MotionBlurKeys.Num())
	{
		USK_LOG_ERROR("Unable to apply settings. Invalid motion blur value");
		return;
	}
	
	ApplyMotionBlurSettings(MotionBlurKeys[Value]);
}

/**
 * @brief Overridable native event for when the actor is being destroyed
 */
void AUSKPostProcessActor::BeginDestroy()
{
	Super::BeginDestroy();
	if (IsValid(GameInstance))
	{
		GameInstance->RemovePostProcessActor(this);
	}
}

/**
 * @brief Apply the motion blur setting
 * @param MotionBlurAmount The amount of motion blur to apply
 */
void AUSKPostProcessActor::ApplyMotionBlurSettings(const float MotionBlurAmount) const
{
	PostProcessComponent->Settings.MotionBlurAmount = MotionBlurAmount;
}
