// Created by Henry Jooste

#include "SettingsItemAudioMusic.h"

#include "Kismet/GameplayStatics.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemAudioMusic::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();	
	MenuItem->MinValue = Config->AudioMusicMin;
	MenuItem->MaxValue = Config->AudioMusicMax;
	MenuItem->DefaultValue = Settings->AudioMusicModified ? Settings->AudioMusic : Config->AudioMusicDefault;
	MenuItem->SetTitle(Config->AudioMusicText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemAudioMusic::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->AudioMusicModified = true;
	Settings->AudioMusic = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemAudioMusic::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	const float Master = Settings->AudioMasterModified ? Settings->AudioMaster : Config->AudioMasterDefault;
	const float Volume = Settings->AudioMusicModified ? Settings->AudioMusic : Config->AudioMusicDefault;
	const float MasterModifier = Master / Config->AudioMasterMax;
	UGameplayStatics::SetSoundMixClassOverride(World, Config->AudioMasterSoundMix,
		Config->AudioMusicSoundClass, Volume / Config->AudioMusicMax * MasterModifier);
}