// Created by Henry Jooste

#include "SettingsItemGraphicsResolution.h"

#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Configure the menu item
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 * @param MenuItem The menu item to configure
 */
void USettingsItemGraphicsResolution::ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings,
	UMenuItem* MenuItem)
{
	MenuItem->ValueMapping.Empty();
	TArray<FIntPoint> Resolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);
	int DefaultValue = Resolutions.Num() - 1;
	
	for (int Index = 0; Index < Resolutions.Num(); Index++)
	{
		const int X = Resolutions[Index].X;
		const int Y = Resolutions[Index].Y;
		const FString Resolution = FString::FromInt(X).Append("x").Append(FString::FromInt(Y));
		MenuItem->ValueMapping.Add(Index, FText::FromString(Resolution));

		if (X == Settings->GraphicsResolutionX && Y == Settings->GraphicsResolutionY)
		{
			DefaultValue = Index;
		}
	}
	
	MenuItem->MinValue = 0;
	MenuItem->MaxValue = Resolutions.Num() - 1;
	MenuItem->DefaultValue = DefaultValue;
	MenuItem->SetTitle(Config->GraphicsResolutionText);
}

/**
 * @brief Save the settings managed by a menu item
 * @param Settings The current settings data
 * @param MenuItem The menu item containing the updated settings
 * @return The updated settings data
 */
USettingsData* USettingsItemGraphicsResolution::SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem)
{
	TArray<FIntPoint> Resolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);
	const FIntPoint Resolution = Resolutions[MenuItem->GetValue()];
	Settings->GraphicsResolutionX = Resolution.X;
	Settings->GraphicsResolutionY = Resolution.Y;
	USettingsUtils::SaveSettings(Settings);
	return Settings;
} 

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Config The settings config specified in the game instance
 * @param Settings The current settings data
 */
void USettingsItemGraphicsResolution::ApplySettings(UObject* World, const USettingsConfig* Config,
	const USettingsData* Settings)
{
	TArray<FIntPoint> Resolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);
	FIntPoint Resolution = Resolutions[Resolutions.Num() - 1];
	
	for (int Index = 0; Index < Resolutions.Num(); Index++)
	{
		if (Resolutions[Index].X == Settings->GraphicsResolutionX &&
			Resolutions[Index].Y == Settings->GraphicsResolutionY)
		{
			Resolution = Resolutions[Index];
			break;
		}
	}
	
	UGameUserSettings* GameSettings = UGameUserSettings::GetGameUserSettings();
	GameSettings->SetScreenResolution(Resolution);
	GameSettings->ApplySettings(false);
}