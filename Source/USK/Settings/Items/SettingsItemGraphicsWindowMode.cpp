// Created by Henry Jooste

#include "SettingsItemGraphicsWindowMode.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/GameUserSettings.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemGraphicsWindowMode::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();
	MenuItem->ValueMapping.Add(0, Config->GraphicsWindowModeFullscreenText);
	MenuItem->ValueMapping.Add(1, Config->GraphicsWindowModeBorderlessText);
	MenuItem->ValueMapping.Add(2, Config->GraphicsWindowModeWindowedText);
	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = 2;
	MenuItem->DefaultValue = Settings->GraphicsWindowModeModified
		? Settings->GraphicsWindowMode
		: Config->GraphicsWindowModeDefault;
	MenuItem->SetTitle(Config->GraphicsWindowModeText);
	NotifySettingChanged(MenuItem, MenuItem->DefaultValue);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemGraphicsWindowMode::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->GraphicsWindowModeModified = true;
	Settings->GraphicsWindowMode = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemGraphicsWindowMode::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	const int Value = Settings->GraphicsWindowModeModified
		? Settings->GraphicsWindowMode
		: Config->GraphicsWindowModeDefault;
	UGameUserSettings* GameSettings = UGameUserSettings::GetGameUserSettings();
	GameSettings->SetFullscreenMode(static_cast<EWindowMode::Type>(Value));
	GameSettings->ApplySettings(false);
	NotifySettingChanged(World, Value);	
}

/**
 * @brief Notify other menu items that the setting was changed
 * @param World The world context
 * @param Value The new value of the setting
 */
void USettingsItemGraphicsWindowMode::NotifySettingChanged(UObject* World, int Value) const
{
	TArray<UUserWidget*> MenuItemWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(World, MenuItemWidgets,
		UMenuItem::StaticClass(), false);

	for (UUserWidget* MenuItemWidget : MenuItemWidgets)
	{
		dynamic_cast<UMenuItem*>(MenuItemWidget)->OnWindowModeUpdated(static_cast<EWindowMode::Type>(Value));
	}
}
