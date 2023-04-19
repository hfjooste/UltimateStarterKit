// Created by Henry Jooste

#include "SettingsItemGraphicsFullscreen.h"

#include "GameFramework/GameUserSettings.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemGraphicsFullscreen::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();
	MenuItem->ValueMapping.Add(0, Config->GraphicsFullscreenDisabledText);
	MenuItem->ValueMapping.Add(1, Config->GraphicsFullscreenEnabledText);
	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = 1;
	MenuItem->DefaultValue = Settings->GraphicsFullscreenModified
		? (Settings->GraphicsFullscreen ? 1 : 0)
		: (Config->GraphicsFullscreenDefault ? 1 : 0);
	MenuItem->SetTitle(Config->GraphicsFullscreenText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemGraphicsFullscreen::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->GraphicsFullscreenModified = true;
	Settings->GraphicsFullscreen = MenuItem->GetValue() == 1;
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemGraphicsFullscreen::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	const bool Value = Settings->GraphicsFullscreenModified
		? Settings->GraphicsFullscreen
		: Config->GraphicsFullscreenDefault;
	UGameUserSettings* GameSettings = UGameUserSettings::GetGameUserSettings();
	GameSettings->SetFullscreenMode(Value ? EWindowMode::Fullscreen : EWindowMode::Windowed);
	GameSettings->ApplySettings(false);
}