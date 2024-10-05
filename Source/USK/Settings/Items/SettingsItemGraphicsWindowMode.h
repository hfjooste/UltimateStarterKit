// Created by Henry Jooste

#pragma once

#include "USK/Settings/SettingsItem.h"
#include "SettingsItemGraphicsWindowMode.generated.h"

/**
 * @brief An implementation for the graphics window mode settings item
 */
UCLASS()
class USettingsItemGraphicsWindowMode : public USettingsItem
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Configure the menu item
	 * @param Config The settings config specified in the game instance
	 * @param Settings The current settings data
	 * @param MenuItem The menu item to configure
	 */
	virtual void ConfigureMenuItem(const USettingsConfig* Config, const USettingsData* Settings, UMenuItem* MenuItem) override;

	/**
	 * @brief Save the settings managed by a menu item
	 * @param Settings The current settings data
	 * @param MenuItem The menu item containing the updated settings
	 * @return The updated settings data
	 */
	virtual USettingsData* SaveSettings(USettingsData* Settings, const UMenuItem* MenuItem) override;

	/**
	 * @brief Apply the settings
	 * @param World The world context
	 * @param Config The settings config specified in the game instance
	 * @param Settings The current settings data
	 */
	virtual void ApplySettings(UObject* World, const USettingsConfig* Config, const USettingsData* Settings) override;

private:
	/**
	 * @brief Notify other menu items that the setting was changed
	 * @param World The world context
	 * @param Value The new value of the setting
	 */
	void NotifySettingChanged(UObject* World, int Value) const;
};
