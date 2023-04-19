// Created by Henry Jooste

#include "SettingsItemGraphicsViewDistance.h"

#include "GameFramework/GameUserSettings.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemGraphicsViewDistance::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();
	MenuItem->ValueMapping.Add(0, Config->GraphicsViewDistanceNearValueText);
	MenuItem->ValueMapping.Add(1, Config->GraphicsViewDistanceMediumValueText);
	MenuItem->ValueMapping.Add(2, Config->GraphicsViewDistanceFarValueText);
	MenuItem->ValueMapping.Add(3, Config->GraphicsViewDistanceEpicValueText);
	MenuItem->ValueMapping.Add(4, Config->GraphicsViewDistanceCinematicValueText);
	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = 4;
	MenuItem->DefaultValue = Settings->GraphicsViewDistanceModified
		? Settings->GraphicsViewDistance
		: Config->GraphicsViewDistanceDefault;
	MenuItem->SetTitle(Config->GraphicsViewDistanceText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemGraphicsViewDistance::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->GraphicsViewDistanceModified = true;
	Settings->GraphicsViewDistance = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemGraphicsViewDistance::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	const int Value = Settings->GraphicsViewDistanceModified
		? Settings->GraphicsViewDistance
		: Config->GraphicsViewDistanceDefault;
	UGameUserSettings* GameSettings = UGameUserSettings::GetGameUserSettings();
	GameSettings->SetViewDistanceQuality(Value);
	GameSettings->ApplySettings(false);
}