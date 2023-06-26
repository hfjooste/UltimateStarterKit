// Created by Henry Jooste

#include "SettingsItemAudioVoice.h"

#include "Kismet/GameplayStatics.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemAudioVoice::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();	
	MenuItem->MinValue = Config->AudioVoiceMin;
	MenuItem->MaxValue = Config->AudioVoiceMax;
	MenuItem->DefaultValue = Settings->AudioVoiceModified ? Settings->AudioVoice : Config->AudioVoiceDefault;
	MenuItem->SetTitle(Config->AudioVoiceText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemAudioVoice::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->AudioVoiceModified = true;
	Settings->AudioVoice = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemAudioVoice::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	const float Master = Settings->AudioMasterModified ? Settings->AudioMaster : Config->AudioMasterDefault;
	const float Volume = Settings->AudioVoiceModified ? Settings->AudioVoice : Config->AudioVoiceDefault;
	const float MasterModifier = Master / Config->AudioMasterMax;
	UGameplayStatics::SetSoundMixClassOverride(World, Config->AudioMasterSoundMix,
		Config->AudioVoiceSoundClass, Volume / Config->AudioVoiceMax * MasterModifier);
}