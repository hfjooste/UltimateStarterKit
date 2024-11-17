// Created by Henry Jooste

#include "SettingsItemGameplayMouseSensitivityY.h"

#include "SettingsItemAudioMusic.h"
#include "Kismet/GameplayStatics.h"
#include "USK/Character/USKCharacter.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemGameplayMouseSensitivityY::ConfigureMenuItem(const USettingsConfig* Config,
	const USettingsData* Settings, UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();	
	MenuItem->MinValue = Config->GameplayMouseSensitivityYMin;
	MenuItem->MaxValue = Config->GameplayMouseSensitivityYMax;
	MenuItem->DefaultValue = Settings->GameplayMouseSensitivityYModified
		? Settings->GameplayMouseSensitivityY
		: Config->GameplayMouseSensitivityYDefault;
	MenuItem->SetTitle(Config->GameplayMouseSensitivityYText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemGameplayMouseSensitivityY::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->GameplayMouseSensitivityYModified = true;
	Settings->GameplayMouseSensitivityY = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
}

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemGameplayMouseSensitivityY::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	TArray<AActor*> CharacterActors;
	UGameplayStatics::GetAllActorsOfClass(World, AUSKCharacter::StaticClass(), CharacterActors);

	for (AActor* CharacterActor : CharacterActors)
	{
		AUSKCharacter* Character = dynamic_cast<AUSKCharacter*>(CharacterActor);
		if (IsValid(Character))
		{
			Character->InitializeSensitivity();
		}
	}
}