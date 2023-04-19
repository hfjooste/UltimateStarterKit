// Created by Henry Jooste

#include "SettingsItemGraphicsShadowQuality.h"

#include "GameFramework/GameUserSettings.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemGraphicsShadowQuality::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();
	MenuItem->ValueMapping.Add(0, Config->GraphicsShadowQualityLowValueText);
	MenuItem->ValueMapping.Add(1, Config->GraphicsShadowQualityMediumValueText);
	MenuItem->ValueMapping.Add(2, Config->GraphicsShadowQualityHighValueText);
	MenuItem->ValueMapping.Add(3, Config->GraphicsShadowQualityEpicValueText);
	MenuItem->ValueMapping.Add(4, Config->GraphicsShadowQualityCinematicValueText);
	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = 4;
	MenuItem->DefaultValue = Settings->GraphicsShadowQualityModified
		? Settings->GraphicsShadowQuality
		: Config->GraphicsShadowQualityDefault;
	MenuItem->SetTitle(Config->GraphicsShadowQualityText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemGraphicsShadowQuality::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->GraphicsShadowQualityModified = true;
	Settings->GraphicsShadowQuality = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemGraphicsShadowQuality::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	const int Value = Settings->GraphicsShadowQualityModified
		? Settings->GraphicsShadowQuality
		: Config->GraphicsShadowQualityDefault;
	UGameUserSettings* GameSettings = UGameUserSettings::GetGameUserSettings();
	GameSettings->SetShadowQuality(Value);
	GameSettings->ApplySettings(false);
}