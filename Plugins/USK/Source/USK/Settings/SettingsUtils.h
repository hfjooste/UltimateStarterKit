// Created by Henry Jooste

#pragma once

#include "SettingsData.h"
#include "SettingsConfig.h"
#include "SettingsItemType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SettingsUtils.generated.h"

class UMenuItem;
class USettingsItem;
class UUSKGameInstance;

/**
 * @brief A Blueprint Function Library class used to load, save and apply all settings
 */
UCLASS()
class USK_API USettingsUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Initialize the settings
	 * @param GameInstance A reference to the game instance
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Settings")
	static void Initialize(const UUSKGameInstance* GameInstance);

	/**
	 * @brief Load the settings
	 * @return The loaded settings data
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Settings")
	static USettingsData* LoadSettings();

	/**
	 * @brief Save the settings
	 * @param Settings The updated settings data
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Settings")
	static void SaveSettings(USettingsData* Settings);

	/**
	 * @brief Apply the settings
	 * @param World The world context
	 * @param Settings The settings data to apply
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Settings", meta=(WorldContext="World"))
	static void ApplySettingsInWorld(const UObject* World, const USettingsData* Settings);

	/**
	 * @brief Apply the settings
	 * @param GameInstance A reference to the game instance
	 * @param Settings The settings data to apply
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Settings")
	static void ApplySettings(const UUSKGameInstance* GameInstance, const USettingsData* Settings);

	/**
	 * @brief Configure the menu item to manage the specified settings item
	 * @param MenuItem The menu item to configure
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Settings")
	static void ConfigureMenuItem(UMenuItem* MenuItem);

	/**
	 * @brief Save the settings managed by the menu item
	 * @param MenuItem The menu item containing the updated settings
	 * @param ApplySettings Should the settings also be applied?
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Settings")
	static void SaveMenuItemSettings(const UMenuItem* MenuItem, const bool ApplySettings);

	/**
	 * @brief Apply the settings managed by the menu item
	 * @param MenuItem The menu item containing the updated settings
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Settings")
	static void ApplyMenuItemSettings(const UMenuItem* MenuItem);

	/**
	 * @brief Get the settings item for the specified menu item
	 * @param MenuItem The menu item to get the settings item for
	 * @param Config The settings config specified in the game instance
	 * @return The settings item
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Settings")
	static USettingsItem* GetSettingsItemForMenuItem(const UMenuItem* MenuItem, const USettingsConfig* Config);

	/**
	 * @brief Get the settings item for the specified settings item type
	 * @param SettingsItemType The menu item to get the settings item for
	 * @param Config The settings config specified in the game instance
	 * @return The settings item
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Settings")
	static USettingsItem* GetSettingsItem(const ESettingsItemType SettingsItemType, const USettingsConfig* Config);

private:
	/**
	 * @brief Apply multiple settings from a specified range
	 * @param GameInstance A reference to the game instance
	 * @param Settings The current settings
	 * @param Start The first (inclusive) setting type in the range
	 * @param End The last (inclusive) setting type in the range
	 */
	static void ApplySettingsInRange(const UUSKGameInstance* GameInstance, const USettingsData* Settings,
	                                 ESettingsItemType Start, ESettingsItemType End);
};
