// Created by Henry Jooste

#include "SettingsItemGameplayControllerSensitivityY.h"

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
void USettingsItemGameplayControllerSensitivityY::ConfigureMenuItem(const USettingsConfig* Config,
	const USettingsData* Settings, UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();	
	MenuItem->MinValue = Config->GameplayControllerSensitivityYMin;
	MenuItem->MaxValue = Config->GameplayControllerSensitivityYMax;
	MenuItem->DefaultValue = Settings->GameplayControllerSensitivityYModified
		? Settings->GameplayControllerSensitivityY
		: Config->GameplayControllerSensitivityYDefault;
	MenuItem->SetTitle(Config->GameplayControllerSensitivityYText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemGameplayControllerSensitivityY::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->GameplayControllerSensitivityYModified = true;
	Settings->GameplayControllerSensitivityY = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
}

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemGameplayControllerSensitivityY::ApplySettings(UObject* World, const USettingsConfig* Config,
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