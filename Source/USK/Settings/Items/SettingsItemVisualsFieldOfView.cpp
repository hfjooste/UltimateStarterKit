// Created by Henry Jooste

#include "SettingsItemVisualsFieldOfView.h"

#include "Kismet/GameplayStatics.h"
#include "USK/Character/USKCharacter.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemVisualsFieldOfView::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();	
	MenuItem->MinValue = Config->VisualFieldOfViewMin;
	MenuItem->MaxValue = Config->VisualFieldOfViewMax;
	MenuItem->DefaultValue = Settings->VisualsFieldOfViewModified
		? Settings->VisualsFieldOfView
		: Config->VisualsFieldOfViewDefault;
	MenuItem->SetTitle(Config->VisualsFieldOfViewText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemVisualsFieldOfView::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->VisualsFieldOfViewModified = true;
	Settings->VisualsFieldOfView = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemVisualsFieldOfView::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	TArray<AActor*> CharacterActors;
	UGameplayStatics::GetAllActorsOfClass(World, AUSKCharacter::StaticClass(), CharacterActors);

	for (AActor* CharacterActor : CharacterActors)
	{
		AUSKCharacter* Character = dynamic_cast<AUSKCharacter*>(CharacterActor);
		if (IsValid(Character))
		{
			Character->InitializeCameraFieldOfView();
		}
	}
}