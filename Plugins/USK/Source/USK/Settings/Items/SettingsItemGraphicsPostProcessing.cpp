// Created by Henry Jooste

#include "SettingsItemGraphicsPostProcessing.h"

#include "GameFramework/GameUserSettings.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemGraphicsPostProcessing::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();
	MenuItem->ValueMapping.Add(0, Config->GraphicsPostProcessingLowValueText);
	MenuItem->ValueMapping.Add(1, Config->GraphicsPostProcessingMediumValueText);
	MenuItem->ValueMapping.Add(2, Config->GraphicsPostProcessingHighValueText);
	MenuItem->ValueMapping.Add(3, Config->GraphicsPostProcessingEpicValueText);
	MenuItem->ValueMapping.Add(4, Config->GraphicsPostProcessingCinematicValueText);
	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = 4;
	MenuItem->DefaultValue = Settings->GraphicsPostProcessingModified
		? Settings->GraphicsPostProcessing
		: Config->GraphicsPostProcessingDefault;
	MenuItem->SetTitle(Config->GraphicsPostProcessingText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemGraphicsPostProcessing::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->GraphicsPostProcessingModified = true;
	Settings->GraphicsPostProcessing = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemGraphicsPostProcessing::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	const int Value = Settings->GraphicsPostProcessingModified
		? Settings->GraphicsPostProcessing
		: Config->GraphicsPostProcessingDefault;
	UGameUserSettings* GameSettings = UGameUserSettings::GetGameUserSettings();
	GameSettings->SetPostProcessingQuality(Value);
	GameSettings->ApplySettings(false);
}