// Created by Henry Jooste

#include "SettingsItemGraphicsAntiAliasing.h"

#include "GameFramework/GameUserSettings.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemGraphicsAntiAliasing::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();
	MenuItem->ValueMapping.Add(0, Config->GraphicsAntiAliasingLowValueText);
	MenuItem->ValueMapping.Add(1, Config->GraphicsAntiAliasingMediumValueText);
	MenuItem->ValueMapping.Add(2, Config->GraphicsAntiAliasingHighValueText);
	MenuItem->ValueMapping.Add(3, Config->GraphicsAntiAliasingEpicValueText);
	MenuItem->ValueMapping.Add(4, Config->GraphicsAntiAliasingCinematicValueText);
	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = 4;
	MenuItem->DefaultValue = Settings->GraphicsAntiAliasingModified
		? Settings->GraphicsAntiAliasing
		: Config->GraphicsAntiAliasingDefault;
	MenuItem->SetTitle(Config->GraphicsAntiAliasingText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemGraphicsAntiAliasing::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->GraphicsAntiAliasingModified = true;
	Settings->GraphicsAntiAliasing = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemGraphicsAntiAliasing::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	const int Value = Settings->GraphicsAntiAliasingModified
		? Settings->GraphicsAntiAliasing
		: Config->GraphicsAntiAliasingDefault;
	UGameUserSettings* GameSettings = UGameUserSettings::GetGameUserSettings();
	GameSettings->SetAntiAliasingQuality(Value);
	GameSettings->ApplySettings(false);
}