// Created by Henry Jooste

#include "SettingsItemAccessibilityColorBlindModeSeverity.h"

#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemAccessibilityColorBlindModeSeverity::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = 100;
	MenuItem->DefaultValue = Settings->AccessibilityColorBlindModeSeverity;
	MenuItem->SetTitle(Config->AccessibilityColorBlindModeSeverityText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemAccessibilityColorBlindModeSeverity::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->AccessibilityColorBlindModeSeverity = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemAccessibilityColorBlindModeSeverity::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	USettingsUtils::GetSettingsItem(ESettingsItemType::AccessibilityColorBlindMode, Config)->ApplySettings(World, Config, Settings);
}