// Created by Henry Jooste

#include "SettingsItemControlsRemap.h"

#include "Kismet/GameplayStatics.h"
#include "USK/Core/USKGameInstance.h"
#include "USK/Logger/Log.h"
#include "USK/Settings/SettingsUtils.h"
#include "Runtime/Launch/Resources/Version.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemControlsRemap::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
#if ENGINE_MAJOR_VERSION >= 5
	MenuItem->ValueMapping.Empty();
	MenuItem->VerticalNavigation = MenuItem->VerticalNavigation == EMenuNavigation::IncreaseDecreaseValue
		? EMenuNavigation::Disabled
		: MenuItem->VerticalNavigation;
	MenuItem->HorizontalNavigation = MenuItem->VerticalNavigation == EMenuNavigation::IncreaseDecreaseValue
		? EMenuNavigation::Disabled
		: MenuItem->VerticalNavigation;
	MenuItem->AllowSelection = true;
	MenuItem->AutoSaveSettingsOnValueChanged = false;
	MenuItem->AutoSaveSettingsOnHighlightRemoved = false;
	MenuItem->AutoSaveSettingsOnSelected = false;
#endif
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemControlsRemap::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
#if ENGINE_MAJOR_VERSION >= 5	
	Settings->KeyBindings.Remove(MenuItem->MappableName);
	Settings->KeyBindings.Add(MenuItem->MappableName, MenuItem->GetInputActionKey());
	USettingsUtils::SaveSettings(Settings);
#endif
	
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemControlsRemap::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
#if ENGINE_MAJOR_VERSION >= 5
	UGameInstance* CurrentGameInstance = UGameplayStatics::GetGameInstance(World);
	const UUSKGameInstance* GameInstance = dynamic_cast<UUSKGameInstance*>(CurrentGameInstance);
	if (GameInstance == nullptr)
	{
		USK_LOG_ERROR("Unable to access settings item. GameInstance is not UUSKGameInstance");	
		return;
	}

	GameInstance->UpdateKeyBindings();
#endif
}