// Created by Henry Jooste

#include "SettingsItemGraphicsVsync.h"

#include "GameFramework/GameUserSettings.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemGraphicsVsync::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();
	MenuItem->ValueMapping.Add(0, Config->GraphicsVsyncDisabledText);
	MenuItem->ValueMapping.Add(1, Config->GraphicsVsyncEnabledText);
	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = 1;
	MenuItem->DefaultValue = Settings->GraphicsVsyncModified
		? (Settings->GraphicsVsync ? 1 : 0)
		: (Config->GraphicsVsyncDefault ? 1 : 0);
	MenuItem->SetTitle(Config->GraphicsVsyncText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemGraphicsVsync::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->GraphicsVsyncModified = true;
	Settings->GraphicsVsync = MenuItem->GetValue() == 1;
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemGraphicsVsync::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	const bool Value = Settings->GraphicsVsyncModified
		? Settings->GraphicsVsync
		: Config->GraphicsVsyncDefault;
	UGameUserSettings* GameSettings = UGameUserSettings::GetGameUserSettings();
	GameSettings->SetVSyncEnabled(Value);
	GameSettings->ApplySettings(false);
}