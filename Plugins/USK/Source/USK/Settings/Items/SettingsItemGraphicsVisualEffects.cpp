// Created by Henry Jooste

#include "SettingsItemGraphicsVisualEffects.h"

#include "GameFramework/GameUserSettings.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemGraphicsVisualEffects::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();
	MenuItem->ValueMapping.Add(0, Config->GraphicsVisualEffectsLowValueText);
	MenuItem->ValueMapping.Add(1, Config->GraphicsVisualEffectsMediumValueText);
	MenuItem->ValueMapping.Add(2, Config->GraphicsVisualEffectsHighValueText);
	MenuItem->ValueMapping.Add(3, Config->GraphicsVisualEffectsEpicValueText);
	MenuItem->ValueMapping.Add(4, Config->GraphicsVisualEffectsCinematicValueText);
	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = 4;
	MenuItem->DefaultValue = Settings->GraphicsVisualEffectsModified
		? Settings->GraphicsVisualEffects
		: Config->GraphicsVisualEffectsDefault;
	MenuItem->SetTitle(Config->GraphicsVisualEffectsText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemGraphicsVisualEffects::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->GraphicsVisualEffectsModified = true;
	Settings->GraphicsVisualEffects = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemGraphicsVisualEffects::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	const int Value = Settings->GraphicsVisualEffectsModified
		? Settings->GraphicsVisualEffects
		: Config->GraphicsVisualEffectsDefault;
	UGameUserSettings* GameSettings = UGameUserSettings::GetGameUserSettings();
	GameSettings->SetVisualEffectQuality(Value);
	GameSettings->ApplySettings(false);
}