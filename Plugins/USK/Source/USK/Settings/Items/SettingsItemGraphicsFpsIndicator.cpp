// Created by Henry Jooste

#include "SettingsItemGraphicsFpsIndicator.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/GameUserSettings.h"
#include "USK/Logger/Log.h"
#include "USK/Settings/SettingsUtils.h"
#include "USK/Widgets/FpsCounter.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemGraphicsFpsIndicator::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();
	MenuItem->ValueMapping.Add(0, Config->GraphicsFpsIndicatorDisabledText);
	MenuItem->ValueMapping.Add(1, Config->GraphicsFpsIndicatorEnabledText);
	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = 1;
	MenuItem->DefaultValue = Settings->GraphicsFpsIndicatorModified
		? (Settings->GraphicsFpsIndicator ? 1 : 0)
		: (Config->GraphicsFpsIndicatorDefault ? 1 : 0);
	MenuItem->SetTitle(Config->GraphicsFpsIndicatorText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemGraphicsFpsIndicator::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->GraphicsFpsIndicatorModified = true;
	Settings->GraphicsFpsIndicator = MenuItem->GetValue() == 1;
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemGraphicsFpsIndicator::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	const bool Value = Settings->GraphicsFpsIndicatorModified
		? Settings->GraphicsFpsIndicator
		: Config->GraphicsFpsIndicatorDefault;

	TArray<UUserWidget*> Widgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(World, Widgets, UFpsCounter::StaticClass(), false);
	for (UUserWidget* Widget : Widgets)
	{
		UFpsCounter* FpsCounter = dynamic_cast<UFpsCounter*>(Widget);
		if (FpsCounter != nullptr)
		{
			FpsCounter->UpdateVisibility(Value);
		}
	}
}