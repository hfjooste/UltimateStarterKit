// Created by Henry Jooste

#include "SettingsItemVisualsMotionBlur.h"

#include "Kismet/GameplayStatics.h"
#include "USK/Core/USKGameInstance.h"
#include "USK/Core/USKPostProcessActor.h"
#include "USK/Logger/Log.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemVisualsMotionBlur::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();
	int Index = 0;
	for (const TTuple<float, FText> MotionBlurValue : Config->VisualsMotionBlurValues)
	{
		MenuItem->ValueMapping.Add(Index, MotionBlurValue.Value);
		Index++;
	}
	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = Config->VisualsMotionBlurValues.Num() - 1;
	MenuItem->DefaultValue = Settings->VisualsMotionBlurModified
		? Settings->VisualsMotionBlur
		: Config->VisualsMotionBlurDefault;
	MenuItem->SetTitle(Config->VisualsMotionBlurText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemVisualsMotionBlur::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->VisualsMotionBlurModified = true;
	Settings->VisualsMotionBlur = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemVisualsMotionBlur::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	const UUSKGameInstance* GameInstance = dynamic_cast<UUSKGameInstance*>(
		UGameplayStatics::GetGameInstance(World));
	if (!IsValid(GameInstance))
	{
		USK_LOG_ERROR("Unable to apply settings. GameInstance is not UUSKGameInstance");
		return;
	}
	
	const int Value = Settings->VisualsMotionBlurModified
		? Settings->VisualsMotionBlur
		: Config->VisualsMotionBlurDefault;

	TArray<float> MotionBlurKeys;
	Config->VisualsMotionBlurValues.GetKeys(MotionBlurKeys);
	if (Value < 0 || Value >= MotionBlurKeys.Num())
	{
		USK_LOG_ERROR("Unable to apply settings. Invalid motion blur value");
		return;
	}
	
	const TArray<AUSKPostProcessActor*> PostProcessActors = GameInstance->GetPostProcessActors();
	for (const AUSKPostProcessActor* PostProcessActor : PostProcessActors)
	{
		if (IsValid(PostProcessActor))
		{
			PostProcessActor->ApplyMotionBlurSettings(MotionBlurKeys[Value]);
		}
	}
}