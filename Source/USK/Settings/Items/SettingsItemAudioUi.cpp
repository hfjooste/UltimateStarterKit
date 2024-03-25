// Created by Henry Jooste

#include "SettingsItemAudioUi.h"

#include "Kismet/GameplayStatics.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemAudioUi::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();	
	MenuItem->MinValue = Config->AudioUiMin;
	MenuItem->MaxValue = Config->AudioUiMax;
	MenuItem->DefaultValue = Settings->AudioUiModified ? Settings->AudioUi : Config->AudioUiDefault;
	MenuItem->SetTitle(Config->AudioUiText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemAudioUi::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->AudioUiModified = true;
	Settings->AudioUi = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemAudioUi::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	const float Master = Settings->AudioMasterModified ? Settings->AudioMaster : Config->AudioMasterDefault;
	const float Volume = Settings->AudioUiModified ? Settings->AudioUi : Config->AudioUiDefault;
	const float MasterModifier = Master / Config->AudioMasterMax;
	UGameplayStatics::SetSoundMixClassOverride(World, Config->AudioMasterSoundMix,
		Config->AudioUiSoundClass, Volume / Config->AudioUiMax * MasterModifier);
}