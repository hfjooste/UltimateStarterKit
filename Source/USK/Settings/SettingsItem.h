// Created by Henry Jooste

#pragma once

#include "USK/Settings/SettingsData.h"
#include "USK/Widgets/MenuItem.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SettingsItem.generated.h"

class UUSKGameInstance;
class USettingsConfig;

/**
 * @brief An implementation for a settings item controlling how the setting is configured, saved and applied
 */
UCLASS()
class USettingsItem : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Configure the menu item
	 * @param Config The settings config specified in the game instance
	 * @param Settings The current settings data
	 * @param MenuItem The menu item to configure
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Ultimate Starter Kit|Settings")
	virtual void ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings, UMenuItem* MenuItem) { }

	/**
	 * @brief Save the settings managed by a menu item
	 * @param Settings The current settings data
	 * @param MenuItem The menu item containing the updated settings
	 * @return The updated settings data
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Ultimate Starter Kit|Settings")
	virtual USettingsData* SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem) { return nullptr; }

	/**
	 * @brief Apply the settings
	 * @param World The world context
	 * @param Config The settings config specified in the game instance
	 * @param Settings The current settings data
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Ultimate Starter Kit|Settings", meta=(WorldContext="World"))
	virtual void ApplySettings(UObject* World, const USettingsConfig* Config, const USettingsData* Settings) { }
};