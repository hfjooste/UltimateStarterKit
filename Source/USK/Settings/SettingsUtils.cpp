// Created by Henry Jooste

#include "SettingsUtils.h"

#include "Kismet/GameplayStatics.h"
#include "USK/Core/USKGameInstance.h"
#include "USK/Logger/Log.h"
#include "USK/Widgets/MenuItem.h"
#include "Runtime/Launch/Resources/Version.h"

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
		USK_LOG_ERROR("Unable to initialize settings. SettingsConfig is nullptr");
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

	USK_LOG_INFO("Applying gameplay settings");
	ApplySettingsInRange(GameInstance, Settings,
		ESettingsItemType::GameplayDifficulty, ESettingsItemType::GameplayDifficulty);

	USK_LOG_INFO("Applying audio settings");
	ApplySettingsInRange(GameInstance, Settings,
		ESettingsItemType::AudioMaster, ESettingsItemType::AudioVoice);

	USK_LOG_INFO("Applying graphics settings");
	ApplySettingsInRange(GameInstance, Settings,
		ESettingsItemType::GraphicsResolution, ESettingsItemType::GraphicsFpsIndicator);

	USK_LOG_INFO("Applying accessibility settings");
	ApplySettingsInRange(GameInstance, Settings,
		ESettingsItemType::AccessibilityColorBlindMode, ESettingsItemType::AccessibilityColorBlindModeSeverity);
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
	case ESettingsItemType::GameplayDifficulty:
		return Config->GameplayDifficultyImplementation->GetDefaultObject<USettingsItem>();
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
	case ESettingsItemType::GraphicsResolution:
		return Config->GraphicsResolutionImplementation->GetDefaultObject<USettingsItem>();
	case ESettingsItemType::GraphicsFullscreen:
		return Config->GraphicsFullscreenImplementation->GetDefaultObject<USettingsItem>();
	case ESettingsItemType::GraphicsViewDistance:
		return Config->GraphicsViewDistanceImplementation->GetDefaultObject<USettingsItem>();
	case ESettingsItemType::GraphicsAntiAliasing:
		return Config->GraphicsAntiAliasingImplementation->GetDefaultObject<USettingsItem>();
	case ESettingsItemType::GraphicsPostProcessing:
		return Config->GraphicsPostProcessingImplementation->GetDefaultObject<USettingsItem>();
	case ESettingsItemType::GraphicsShadowQuality:
		return Config->GraphicsShadowQualityImplementation->GetDefaultObject<USettingsItem>();
	case ESettingsItemType::GraphicsTextureQuality:
		return Config->GraphicsTextureQualityImplementation->GetDefaultObject<USettingsItem>();
	case ESettingsItemType::GraphicsVisualEffects:
		return Config->GraphicsVisualEffectsImplementation->GetDefaultObject<USettingsItem>();
	case ESettingsItemType::GraphicsShadingQuality:
		return Config->GraphicsShadingQualityImplementation->GetDefaultObject<USettingsItem>();
	case ESettingsItemType::GraphicsVSync:
		return Config->GraphicsVsyncImplementation->GetDefaultObject<USettingsItem>();
	case ESettingsItemType::GraphicsFpsIndicator:
		return Config->GraphicsFpsIndicatorImplementation->GetDefaultObject<USettingsItem>();
	case ESettingsItemType::AccessibilityColorBlindMode:
		return Config->AccessibilityColorBlindModeImplementation->GetDefaultObject<USettingsItem>();
	case ESettingsItemType::AccessibilityColorBlindModeSeverity:
		return Config->AccessibilityColorBlindModeSeverityImplementation->GetDefaultObject<USettingsItem>();
#if ENGINE_MAJOR_VERSION >= 5
	case ESettingsItemType::ControlsRemap:
		return Config->ControlsRemapImplementation->GetDefaultObject<USettingsItem>();
#endif
	default:
		USK_LOG_WARNING("Settings item type not yet implemented");
		return nullptr;
	}
}

/**
 * @brief Apply multiple settings from a specified range
 * @param GameInstance A reference to the game instance
 * @param Settings The current settings
 * @param Start The first (inclusive) setting type in the range
 * @param End The last (inclusive) setting type in the range
 */
void USettingsUtils::ApplySettingsInRange(const UUSKGameInstance* GameInstance, const USettingsData* Settings,
                                          ESettingsItemType Start, ESettingsItemType End)
{
	for (int Index = static_cast<int32>(Start); Index <= static_cast<int32>(End); ++Index)
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
