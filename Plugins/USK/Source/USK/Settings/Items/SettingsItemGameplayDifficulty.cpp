// Created by Henry Jooste

#include "SettingsItemGameplayDifficulty.h"

#include "Kismet/GameplayStatics.h"
#include "USK/Core/USKGameInstance.h"
#include "USK/Logger/Log.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemGameplayDifficulty::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();
	for (int Index = 0; Index < Config->GameplayDifficultyOptions.Num(); Index++)
	{
		MenuItem->ValueMapping.Add(Index, Config->GameplayDifficultyOptions[Index]);
	}
	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = Config->GameplayDifficultyOptions.Num() - 1;
	MenuItem->DefaultValue = Settings->GameplayDifficultyModified
		? Settings->GameplayDifficulty
		: Config->GameplayDifficultyDefault;
	MenuItem->SetTitle(Config->GameplayDifficultyText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemGameplayDifficulty::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->GameplayDifficultyModified = true;
	Settings->GameplayDifficulty = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemGameplayDifficulty::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	UGameInstance* CurrentGameInstance = UGameplayStatics::GetGameInstance(World);
	const UUSKGameInstance* GameInstance = dynamic_cast<UUSKGameInstance*>(CurrentGameInstance);
	if (!IsValid(GameInstance))
	{
		USK_LOG_ERROR("Unable to apply settings. GameInstance is not UUSKGameInstance");	
		return;
	}

	const int Value = Settings->GameplayDifficultyModified
		? Settings->GameplayDifficulty
		: Config->GameplayDifficultyDefault;
	GameInstance->UpdateDifficulty(Value);
}