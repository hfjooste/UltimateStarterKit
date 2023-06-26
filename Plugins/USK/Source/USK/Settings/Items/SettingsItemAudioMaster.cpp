// Created by Henry Jooste

#include "SettingsItemAudioMaster.h"

#include "SettingsItemAudioMusic.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemAudioMaster::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();	
	MenuItem->MinValue = Config->AudioMasterMin;
	MenuItem->MaxValue = Config->AudioMasterMax;
	MenuItem->DefaultValue = Settings->AudioMasterModified ? Settings->AudioMaster : Config->AudioMasterDefault;
	MenuItem->SetTitle(Config->AudioMasterText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemAudioMaster::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->AudioMasterModified = true;
	Settings->AudioMaster = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
}

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemAudioMaster::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	USettingsUtils::GetSettingsItem(ESettingsItemType::AudioMusic, Config)->ApplySettings(World, Config, Settings);
	USettingsUtils::GetSettingsItem(ESettingsItemType::AudioEffects, Config)->ApplySettings(World, Config, Settings);
	USettingsUtils::GetSettingsItem(ESettingsItemType::AudioUi, Config)->ApplySettings(World, Config, Settings);
	USettingsUtils::GetSettingsItem(ESettingsItemType::AudioVoice, Config)->ApplySettings(World, Config, Settings);
}