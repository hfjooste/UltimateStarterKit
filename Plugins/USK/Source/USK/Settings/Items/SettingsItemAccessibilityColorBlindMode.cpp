// Created by Henry Jooste

#include "SettingsItemAccessibilityColorBlindMode.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/GameUserSettings.h"
#include "USK/Logger/Log.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemAccessibilityColorBlindMode::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();
	MenuItem->ValueMapping.Add(0, Config->AccessibilityColorBlindModeNormalVisionText);
	MenuItem->ValueMapping.Add(1, Config->AccessibilityColorBlindModeDeuteranopiaText);
	MenuItem->ValueMapping.Add(2, Config->AccessibilityColorBlindModeDeuteranomalyText);
	MenuItem->ValueMapping.Add(3, Config->AccessibilityColorBlindModeProtanopiaText);
	MenuItem->ValueMapping.Add(4, Config->AccessibilityColorBlindModeProtanomalyText);
	MenuItem->ValueMapping.Add(5, Config->AccessibilityColorBlindModeTritanopiaText);
	MenuItem->ValueMapping.Add(6, Config->AccessibilityColorBlindModeTritanomalyText);
	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = 6;
	MenuItem->DefaultValue = Settings->AccessibilityColorBlindMode;
	MenuItem->SetTitle(Config->AccessibilityColorBlindModeText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemAccessibilityColorBlindMode::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	Settings->AccessibilityColorBlindMode = MenuItem->GetValue();
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemAccessibilityColorBlindMode::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	float SeverityMultiplier = 1.0f;
	EColorVisionDeficiency Type;
	
	switch (Settings->AccessibilityColorBlindMode)
	{
	case 0:
		Type = EColorVisionDeficiency::NormalVision;
		break;
	case 1:
		Type = EColorVisionDeficiency::Deuteranope;
		break;
	case 2:
		SeverityMultiplier = 0.5f;
		Type = EColorVisionDeficiency::Deuteranope;
		break;
	case 3:
		Type = EColorVisionDeficiency::Protanope;
		break;
	case 4:
		SeverityMultiplier = 0.5f;
		Type = EColorVisionDeficiency::Protanope;
		break;
	case 5:
		Type = EColorVisionDeficiency::Tritanope;
		break;
	case 6:
		SeverityMultiplier = 0.5f;
		Type = EColorVisionDeficiency::Tritanope;
		break;
	default:
		USK_LOG_ERROR("Invalid color blind mode");
		Type = EColorVisionDeficiency::NormalVision;
		break;		
	}

	if (Type == EColorVisionDeficiency::NormalVision)
	{
		UWidgetBlueprintLibrary::SetColorVisionDeficiencyType(EColorVisionDeficiency::NormalVision,
			1.0f, false, false);
		return;
	}

	const float Severity = FMath::Clamp(
		Settings->AccessibilityColorBlindModeSeverity * SeverityMultiplier / 100.0f, 0.0f, 1.0f);
	UWidgetBlueprintLibrary::SetColorVisionDeficiencyType(Type, Severity, true, false);
}