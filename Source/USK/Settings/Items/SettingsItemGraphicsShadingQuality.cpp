// Created by Henry Jooste

#include "SettingsItemGraphicsShadingQuality.h"

#include "GameFramework/GameUserSettings.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemGraphicsShadingQuality::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();
	MenuItem->ValueMapping.Add(0, Config->GraphicsShadingQualityLowValueText);
	MenuItem->ValueMapping.Add(1, Config->GraphicsShadingQualityMediumValueText);
	MenuItem->ValueMapping.Add(2, Config->GraphicsShadingQualityHighValueText);
	MenuItem->ValueMapping.Add(3, Config->GraphicsShadingQualityEpicValueText);
	MenuItem->ValueMapping.Add(4, Config->GraphicsShadingQualityCinematicValueText);
	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = 4;
	MenuItem->DefaultValue = Settings->GraphicsShadingQualityModified
		? Settings->GraphicsShadingQuality
		: Config->GraphicsShadingQualityDefault;
	MenuItem->SetTitle(Config->GraphicsShadingQualityText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemGraphicsShadingQuality::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->GraphicsShadingQualityModified = true;
	Settings->GraphicsShadingQuality = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemGraphicsShadingQuality::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	const int Value = Settings->GraphicsShadingQualityModified
		? Settings->GraphicsShadingQuality
		: Config->GraphicsShadingQualityDefault;
	UGameUserSettings* GameSettings = UGameUserSettings::GetGameUserSettings();
	GameSettings->SetShadingQuality(Value);
	GameSettings->ApplySettings(false);
}