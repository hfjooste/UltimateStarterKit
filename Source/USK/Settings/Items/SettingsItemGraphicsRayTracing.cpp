// Created by Henry Jooste

#include "SettingsItemGraphicsRayTracing.h"

#include "GameFramework/GameUserSettings.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemGraphicsRayTracing::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();
	MenuItem->ValueMapping.Add(0, Config->GraphicsRayTracingDisabledText);
	MenuItem->ValueMapping.Add(1, Config->GraphicsRayTracingEnabledText);
	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = 1;
	MenuItem->DefaultValue = Settings->GraphicsRayTracingModified
		? (Settings->GraphicsRayTracing ? 1 : 0)
		: (Config->GraphicsRayTracingDefault ? 1 : 0);
	MenuItem->SetTitle(Config->GraphicsRayTracingText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemGraphicsRayTracing::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->GraphicsRayTracingModified = true;
	Settings->GraphicsRayTracing = MenuItem->GetValue() == 1;
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemGraphicsRayTracing::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	const bool Value = Settings->GraphicsRayTracingModified
		? Settings->GraphicsRayTracing
		: Config->GraphicsRayTracingDefault;
	const IConsoleManager& ConsoleManager = IConsoleManager::Get();
	IConsoleVariable* RayTracingVariable = ConsoleManager.FindConsoleVariable(TEXT("r.Lumen.HardwareRayTracing"));
	if (RayTracingVariable != nullptr)
	{
		RayTracingVariable->Set(Value ? 1 : 0);
	}
}