// Created by Henry Jooste

#include "SettingsItemAudioAmbience.h"

#include "Kismet/GameplayStatics.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemAudioAmbience::ConfigureMenuItem(const USettingsConfig* Config,
	const USettingsData* Settings, UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();	
	MenuItem->MinValue = Config->AudioAmbienceMin;
	MenuItem->MaxValue = Config->AudioAmbienceMax;
	MenuItem->DefaultValue = Settings->AudioAmbienceModified ? Settings->AudioAmbience : Config->AudioAmbienceDefault;
	MenuItem->SetTitle(Config->AudioAmbienceText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemAudioAmbience::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->AudioAmbienceModified = true;
	Settings->AudioAmbience = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
}

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemAudioAmbience::ApplySettings(UObject* World, const USettingsConfig* Config,
                                              const USettingsData* Settings)
{
	const float Master = Settings->AudioMasterModified ? Settings->AudioMaster : Config->AudioMasterDefault;
	const float Volume = Settings->AudioAmbienceModified ? Settings->AudioAmbience : Config->AudioAmbienceDefault;
	const float MasterModifier = Master / Config->AudioMasterMax;
	UGameplayStatics::SetSoundMixClassOverride(World, Config->AudioMasterSoundMix,
		Config->AudioAmbienceSoundClass, Volume / Config->AudioAmbienceMax * MasterModifier);
}