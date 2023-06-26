// Created by Henry Jooste

#include "SettingsItemAudioEffects.h"

#include "Kismet/GameplayStatics.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemAudioEffects::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
                                                  UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();	
	MenuItem->MinValue = Config->AudioEffectsMin;
	MenuItem->MaxValue = Config->AudioEffectsMax;
	MenuItem->DefaultValue = Settings->AudioEffectsModified ? Settings->AudioEffects : Config->AudioEffectsDefault;
	MenuItem->SetTitle(Config->AudioEffectsText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemAudioEffects::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->AudioEffectsModified = true;
	Settings->AudioEffects = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
}

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemAudioEffects::ApplySettings(UObject* World, const USettingsConfig* Config,
                                              const USettingsData* Settings)
{
	const float Master = Settings->AudioMasterModified ? Settings->AudioMaster : Config->AudioMasterDefault;
	const float Volume = Settings->AudioEffectsModified ? Settings->AudioEffects : Config->AudioEffectsDefault;
	const float MasterModifier = Master / Config->AudioMasterMax;
	UGameplayStatics::SetSoundMixClassOverride(World, Config->AudioMasterSoundMix,
		Config->AudioEffectsSoundClass, Volume / Config->AudioEffectsMax * MasterModifier);
}