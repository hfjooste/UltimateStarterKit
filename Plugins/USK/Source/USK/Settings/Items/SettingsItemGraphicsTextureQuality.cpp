// Created by Henry Jooste

#include "SettingsItemGraphicsTextureQuality.h"

#include "GameFramework/GameUserSettings.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemGraphicsTextureQuality::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();
	MenuItem->ValueMapping.Add(0, Config->GraphicsTextureQualityLowValueText);
	MenuItem->ValueMapping.Add(1, Config->GraphicsTextureQualityMediumValueText);
	MenuItem->ValueMapping.Add(2, Config->GraphicsTextureQualityHighValueText);
	MenuItem->ValueMapping.Add(3, Config->GraphicsTextureQualityEpicValueText);
	MenuItem->ValueMapping.Add(4, Config->GraphicsTextureQualityCinematicValueText);
	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = 4;
	MenuItem->DefaultValue = Settings->GraphicsTextureQualityModified
		? Settings->GraphicsTextureQuality
		: Config->GraphicsTextureQualityDefault;
	MenuItem->SetTitle(Config->GraphicsTextureQualityText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemGraphicsTextureQuality::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->GraphicsTextureQualityModified = true;
	Settings->GraphicsTextureQuality = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemGraphicsTextureQuality::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	const int Value = Settings->GraphicsTextureQualityModified
		? Settings->GraphicsTextureQuality
		: Config->GraphicsTextureQualityDefault;
	UGameUserSettings* GameSettings = UGameUserSettings::GetGameUserSettings();
	GameSettings->SetTextureQuality(Value);
	GameSettings->ApplySettings(false);
}