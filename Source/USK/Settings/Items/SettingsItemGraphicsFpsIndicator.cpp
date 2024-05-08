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
	MenuItem->ValueMapping.Add(0,
		Config->GraphicsFpsIndicatorValueText.Contains(ESettingsFpsCounterType::Disabled)
			? Config->GraphicsFpsIndicatorValueText[ESettingsFpsCounterType::Disabled]
			: FText::GetEmpty());
	MenuItem->ValueMapping.Add(1,
		Config->GraphicsFpsIndicatorValueText.Contains(ESettingsFpsCounterType::Simple)
			? Config->GraphicsFpsIndicatorValueText[ESettingsFpsCounterType::Simple]
			: FText::GetEmpty());
	MenuItem->ValueMapping.Add(2,
		Config->GraphicsFpsIndicatorValueText.Contains(ESettingsFpsCounterType::Detailed)
			? Config->GraphicsFpsIndicatorValueText[ESettingsFpsCounterType::Detailed]
			: FText::GetEmpty());
	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = 2;
	MenuItem->DefaultValue = Settings->GraphicsFpsIndicatorTypeModified
		? static_cast<int>(Settings->GraphicsFpsIndicatorType)
		: static_cast<int>(Config->GraphicsFpsIndicatorTypeDefault);
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
	Settings->GraphicsFpsIndicatorTypeModified = true;
	Settings->GraphicsFpsIndicatorType = static_cast<ESettingsFpsCounterType>(MenuItem->GetValue());
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
	TArray<UUserWidget*> Widgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(World, Widgets, UFpsCounter::StaticClass(), false);
	for (UUserWidget* Widget : Widgets)
	{
		UFpsCounter* FpsCounter = dynamic_cast<UFpsCounter*>(Widget);
		if (IsValid(FpsCounter))
		{
			FpsCounter->LoadSettings();
		}
	}
}