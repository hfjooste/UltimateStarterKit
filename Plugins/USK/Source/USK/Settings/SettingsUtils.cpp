// Created by Henry Jooste

#include "SettingsUtils.h"

#include "Kismet/GameplayStatics.h"
#include "USK/Core/USKGameInstance.h"
#include "USK/Logger/Log.h"
#include "USK/Widgets/MenuItem.h"

/**
 * @brief Initialize the settings
 * @param GameInstance A reference to the game instance
 */
void USettingsUtils::Initialize(const UUSKGameInstance* GameInstance)
{
	if (GameInstance == nullptr)
	{
		USK_LOG_ERROR("Unable to initialize settings. GameInstance is nullptr");	
		return;
	}

	if (GameInstance->SettingsConfig == nullptr)
	{
		USK_LOG_ERROR("Unable to initialize settings.SettingsConfig is nullptr");
		return;
	}
	
	ApplySettings(GameInstance, LoadSettings());
}

/**
 * @brief Load the settings
 * @return The loaded settings data
 */
USettingsData* USettingsUtils::LoadSettings()
{
	if (!UGameplayStatics::DoesSaveGameExist("settings", 0))
	{
		USK_LOG_INFO("Creating new settings file");
		USaveGame* NewSettings = UGameplayStatics::CreateSaveGameObject(USettingsData::StaticClass());
		USettingsData* SettingsData = dynamic_cast<USettingsData*>(NewSettings);
		SaveSettings(SettingsData);
		return SettingsData;
	}
	
	USK_LOG_INFO("Loading settings");
	USaveGame* SavedSettings = UGameplayStatics::LoadGameFromSlot("settings", 0);
	return dynamic_cast<USettingsData*>(SavedSettings);
}

/**
 * @brief Save the settings
 * @param Settings The updated settings data
 */
void USettingsUtils::SaveSettings(USettingsData* Settings)
{
	USK_LOG_INFO("Saving settings");
	UGameplayStatics::SaveGameToSlot(Settings, "settings", 0);
}

/**
 * @brief Apply the settings
 * @param World The world context
 * @param Settings The settings data to apply
 */
void USettingsUtils::ApplySettingsInWorld(const UObject* World, const USettingsData* Settings)
{
	UGameInstance* CurrentGameInstance = UGameplayStatics::GetGameInstance(World);
	const UUSKGameInstance* GameInstance = dynamic_cast<UUSKGameInstance*>(CurrentGameInstance);
	if (GameInstance == nullptr)
	{
		USK_LOG_ERROR("Unable to access settings item. GameInstance is not UUSKGameInstance");	
		return;
	}

	ApplySettings(GameInstance, Settings);
}

/**
 * @brief Apply the settings
 * @param GameInstance A reference to the game instance
 * @param Settings The settings data to apply
 */
void USettingsUtils::ApplySettings(const UUSKGameInstance* GameInstance, const USettingsData* Settings)
{
	if (GameInstance == nullptr)
	{
		USK_LOG_ERROR("Unable to apply settings. GameInstance is nullptr");	
		return;
	}

	USK_LOG_INFO("Applying settings");
	for (int Index = static_cast<int32>(ESettingsItemType::AudioMaster);
		Index <= static_cast<int32>(ESettingsItemType::AudioVoice);
		++Index)
	{
		const ESettingsItemType SettingsItemType = static_cast<ESettingsItemType>(Index);
		USettingsItem* SettingsItem = GetSettingsItem(SettingsItemType, GameInstance->SettingsConfig);
		if (SettingsItem == nullptr)
		{
			USK_LOG_WARNING(*FString::Format(TEXT("Setting not implemented (Index: {0})"), { FString::FromInt(Index) }));
			continue;
		}

		USK_LOG_INFO(*FString::Format(TEXT("Applying setting (Index: {0})"), { FString::FromInt(Index) }));
		SettingsItem->ApplySettings(GameInstance->GetWorld(), GameInstance->SettingsConfig, Settings);
	}
}

/**
 * @brief Configure the menu item to manage the specified settings item
 * @param MenuItem The menu item to configure
 */
void USettingsUtils::ConfigureMenuItem(UMenuItem* MenuItem)
{
	UGameInstance* CurrentGameInstance = UGameplayStatics::GetGameInstance(MenuItem->GetWorld());
	const UUSKGameInstance* GameInstance = dynamic_cast<UUSKGameInstance*>(CurrentGameInstance);
	if (GameInstance == nullptr)
	{
		USK_LOG_ERROR("Unable to configure menu item. GameInstance is not UUSKGameInstance");	
		return;
	}

	if (GameInstance->SettingsConfig == nullptr)
	{
		USK_LOG_ERROR("Unable to configure menu item. SettingsConfig is nullptr");
		return;
	}
	
	USettingsItem* SettingsItem = GetSettingsItemForMenuItem(MenuItem, GameInstance->SettingsConfig);
	if (SettingsItem == nullptr)
	{
		USK_LOG_ERROR("Unable to configure menu item. SettingsItem is nullptr");
		return;
	}

	USK_LOG_INFO("Configuring menu item");
	SettingsItem->ConfigureMenuItem(GameInstance->SettingsConfig, LoadSettings(), MenuItem);
}

/**
 * @brief Save the settings managed by the menu item
 * @param MenuItem The menu item containing the updated settings
 * @param ApplySettings Should the settings also be applied?
 */
void USettingsUtils::SaveMenuItemSettings(const UMenuItem* MenuItem, const bool ApplySettings)
{
	UGameInstance* CurrentGameInstance = UGameplayStatics::GetGameInstance(MenuItem->GetWorld());
	const UUSKGameInstance* GameInstance = dynamic_cast<UUSKGameInstance*>(CurrentGameInstance);
	if (GameInstance == nullptr)
	{
		USK_LOG_ERROR("Unable to save menu item settings. GameInstance is not UUSKGameInstance");	
		return;
	}

	if (GameInstance->SettingsConfig == nullptr)
	{
		USK_LOG_ERROR("Unable to configure menu item. SettingsConfig is nullptr");
		return;
	}
	
	USettingsItem* SettingsItem = GetSettingsItemForMenuItem(MenuItem, GameInstance->SettingsConfig);
	if (SettingsItem == nullptr)
	{
		USK_LOG_ERROR("Unable to save menu item settings. SettingsItem is nullptr");
		return;
	}	
	
	USK_LOG_INFO("Saving menu item settings");
	const USettingsData* UpdatedSettings = SettingsItem->SaveSettings(LoadSettings(), MenuItem);
	if (ApplySettings)
	{
		USK_LOG_INFO("Applying menu item settings");
		SettingsItem->ApplySettings(GameInstance->GetWorld(), GameInstance->SettingsConfig, UpdatedSettings);
	}
}

/**
 * @brief Apply the settings managed by the menu item
 * @param MenuItem The menu item containing the updated settings
 */
void USettingsUtils::ApplyMenuItemSettings(const UMenuItem* MenuItem)
{
	UGameInstance* CurrentGameInstance = UGameplayStatics::GetGameInstance(MenuItem->GetWorld());
	const UUSKGameInstance* GameInstance = dynamic_cast<UUSKGameInstance*>(CurrentGameInstance);
	if (GameInstance == nullptr)
	{
		USK_LOG_ERROR("Unable to apply menu item settings. GameInstance is not UUSKGameInstance");	
		return;
	}

	if (GameInstance->SettingsConfig == nullptr)
	{
		USK_LOG_ERROR("Unable to configure menu item. SettingsConfig is nullptr");
		return;
	}

	USettingsItem* SettingsItem = GetSettingsItemForMenuItem(MenuItem, GameInstance->SettingsConfig);
	if (SettingsItem == nullptr)
	{
		USK_LOG_ERROR("Unable to apply menu item settings. SettingsItem is nullptr");
		return;
	}

	USK_LOG_INFO("Applying menu item settings");
	SettingsItem->ApplySettings(GameInstance->GetWorld(), GameInstance->SettingsConfig, LoadSettings());
}

/**
 * @brief Get the settings item for the specified menu item
 * @param MenuItem The menu item to get the settings item for
 * @param Config The settings config specified in the game instance
 * @return The settings item
 */
USettingsItem* USettingsUtils::GetSettingsItemForMenuItem(const UMenuItem* MenuItem, const USettingsConfig* Config)
{
	if (MenuItem == nullptr)
	{
		USK_LOG_ERROR("Unable to get settings item. Menu item is nullptr");
		return nullptr;
	}

	if (Config == nullptr)
	{
		USK_LOG_ERROR("Unable to get settings item. SettingsConfig is nullptr");
		return nullptr;
	}
	
	return GetSettingsItem(MenuItem->SettingsItemType, Config);
}

/**
 * @brief Get the settings item for the specified settings item type
 * @param SettingsItemType The menu item to get the settings item for
 * @param Config The settings config specified in the game instance
 * @return The settings item
 */
USettingsItem* USettingsUtils::GetSettingsItem(const ESettingsItemType SettingsItemType, const USettingsConfig* Config)
{
	if (Config == nullptr)
	{
		USK_LOG_ERROR("Unable to get settings item. SettingsConfig is nullptr");
		return nullptr;
	}
	
	switch (SettingsItemType)
	{
	case ESettingsItemType::None:
		return nullptr;
	case ESettingsItemType::AudioMaster:
		return Config->AudioMasterImplementation->GetDefaultObject<USettingsItem>();
	case ESettingsItemType::AudioMusic:
		return Config->AudioMusicImplementation->GetDefaultObject<USettingsItem>();
	case ESettingsItemType::AudioEffects:
		return Config->AudioEffectsImplementation->GetDefaultObject<USettingsItem>();
	case ESettingsItemType::AudioUi:
		return Config->AudioUiImplementation->GetDefaultObject<USettingsItem>();
	case ESettingsItemType::AudioVoice:
		return Config->AudioVoiceImplementation->GetDefaultObject<USettingsItem>();
	default:
		USK_LOG_WARNING("Settings item type not yet implemented");
		return nullptr;
	}
}