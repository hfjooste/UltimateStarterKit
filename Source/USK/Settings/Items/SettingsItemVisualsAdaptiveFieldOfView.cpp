// Created by Henry Jooste

#include "SettingsItemVisualsAdaptiveFieldOfView.h"

#include "Kismet/GameplayStatics.h"
#include "USK/Character/USKCharacter.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemVisualsAdaptiveFieldOfView::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();
	MenuItem->ValueMapping.Add(0, Config->VisualsAdaptiveFieldOfViewDisabledText);
	MenuItem->ValueMapping.Add(1, Config->VisualsAdaptiveFieldOfViewEnabledText);
	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = 1;
	MenuItem->DefaultValue = Settings->VisualsAdaptiveFieldOfViewModified
		? (Settings->VisualsAdaptiveFieldOfView ? 1 : 0)
		: (Config->VisualsAdaptiveFieldOfViewDefault ? 1 : 0);
	MenuItem->SetTitle(Config->VisualsAdaptiveFieldOfViewText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemVisualsAdaptiveFieldOfView::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->VisualsAdaptiveFieldOfViewModified = true;
	Settings->VisualsAdaptiveFieldOfView = MenuItem->GetValue() == 1;
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemVisualsAdaptiveFieldOfView::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	TArray<AActor*> CharacterActors;
	UGameplayStatics::GetAllActorsOfClass(World, AUSKCharacter::StaticClass(), CharacterActors);

	for (AActor* CharacterActor : CharacterActors)
	{
		AUSKCharacter* Character = dynamic_cast<AUSKCharacter*>(CharacterActor);
		if (IsValid(Character))
		{
			Character->UpdateAdaptiveFieldOfViewStatus();
		}
	}
}