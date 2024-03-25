// Created by Henry Jooste

#include "USKGameInstance.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputDevice.h"
#include "InputMappingContext.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "USK/Logger/Log.h"
#include "USK/Settings/SettingsUtils.h"
#include "USK/Utils/PlatformUtils.h"
#include "Runtime/Launch/Resources/Version.h"
#include "USK/Widgets/MessagePopupWidget.h"

/**
 * @brief Virtual function to allow custom GameInstances an opportunity to set up what it needs
 */
void UUSKGameInstance::Init()
{
	Super::Init();
	InitializeFeaturesAfterDelay();

#if UE_EDITOR || WITH_EDITOR
	ULog::Configure(LogConfigEditor);
#elif UE_BUILD_DEBUG
	ULog::Configure(LogConfigDebug);
#elif UE_BUILD_DEVELOPMENT
	ULog::Configure(LogConfigDevelopment);
#elif UE_BUILD_SHIPPING
	ULog::Configure(LogConfigShipping);
#endif
}

/**
 * @brief Virtual function called after a map is loaded
 * @param LoadTime The amount of time it took to load the map
 * @param MapName The name of the map that was loaded
 */
void UUSKGameInstance::LoadComplete(const float LoadTime, const FString& MapName)
{
	Super::LoadComplete(LoadTime, MapName);
	if (bIsFeaturesInitialized)
	{
		InitializeInputIndicatorsAfterDelay();
	}
}

/**
 * @brief Get the save data that is currently loaded
 * @return A reference to the current save data
 */
UUSKSaveGame* UUSKGameInstance::GetSaveData() const
{
	if (CurrentSaveGame == nullptr)
	{
		USK_LOG_WARNING("Save Game is nullptr");
	}

	return CurrentSaveGame;
}

/**
 * @brief Save the modified data currently in memory
 */
void UUSKGameInstance::SaveData()
{
	if (CurrentSaveGame == nullptr)
	{
		USK_LOG_ERROR("Save Game is nullptr");
		return;
	}

	USK_LOG_INFO("Saving data");
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, GetSaveSlotName(CurrentSaveSlot), 0);
}

/**
 * @brief Set the current save slot
 * @param Index The index of the save slot
 */
void UUSKGameInstance::SetCurrentSaveSlot(const int Index)
{	
	USK_LOG_INFO(*FString::Format(TEXT("Changing save slot index to {0}"), { FString::FromInt(Index) }));
	
	CurrentSaveSlot = Index;
	LoadData(Index);
}

/**
 * @brief Check if a save slot is used
 * @param Index The index of the save slot to check
 * @return A boolean value indicating if the save slot is used
 */
bool UUSKGameInstance::IsSaveSlotUsed(const int Index)
{
	return UGameplayStatics::DoesSaveGameExist(GetSaveSlotName(Index), 0);
}

/**
 * @brief Enable the input indicators feature
 */
void UUSKGameInstance::EnableInputIndicators()
{
	if (IsInputIndicatorsEnabled)
	{
		USK_LOG_WARNING("Input indicators are already enabled");
		return;
	}

	USK_LOG_INFO("Enabling input indicators");
	IsInputIndicatorsEnabled = true;
	InitializeInputIndicatorsAfterDelay();
}

/**
 * @brief Disable the input indicators feature
 */
void UUSKGameInstance::DisableInputIndicators()
{
	if (!IsInputIndicatorsEnabled)
	{
		USK_LOG_WARNING("Input indicators are not enabled");
		return;
	}

	USK_LOG_INFO("Disabling input indicators");
	IsInputIndicatorsEnabled = false;
	CurrentInputDevice = EInputDevice::Unknown;
	OnInputDeviceUpdated.Broadcast();
}

/**
 * @brief Get the input indicator icon for a specific action
 * @param InputAction The input action
 * @param Amount The amount of icons to retrieve
 * @return An array of input indicator icons for the specified action
 */
TArray<UTexture2D*> UUSKGameInstance::GetInputIndicatorIcon(UInputAction* InputAction, const int Amount)
{
	TArray<UTexture2D*> InputIndicators;
	if (InputMappingContext != nullptr)
	{
		TArray<FEnhancedActionKeyMapping> Mappings = InputMappingContext->GetMappings();
		for (FEnhancedActionKeyMapping Mapping : Mappings)
		{			
			if (MapActionKeyToInputIndicator(InputIndicators, Mapping.Action, Mapping.Key, InputAction, Amount))
			{
				return InputIndicators;
			}
		}	
	}

	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	const UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	
	TArray<FKey> Keys = Subsystem->QueryKeysMappedToAction(InputAction);
	for (const FKey Key : Keys)
	{
		if (MapActionKeyToInputIndicator(InputIndicators, InputAction, Key, InputAction, Amount))
		{
			return InputIndicators;
		}
	}
 
	return InputIndicators;
}

/**
 * @brief Get the input indicator icon for a specific key
 * @param Key The key used to retrieve the input indicator icon
 * @param InputDevice The input device used to retrieve the input indicator icon
 * @return The input indicator icon for the specified key
 */
UTexture2D* UUSKGameInstance::GetInputIndicatorIconForKey(const FKey Key, const EInputDevice InputDevice) const
{
	if (!IsInputIndicatorsEnabled)
	{
		return nullptr;
	}
	
	switch (InputDevice)
	{
	case EInputDevice::KeyboardMouse:
		return KeyboardMouseInputMappings.FindRef(Key);
	case EInputDevice::GenericController:
		return GenericControllerInputMappings.FindRef(Key);
	case EInputDevice::MxController:
		return MxControllerInputMappings.FindRef(Key);
	case EInputDevice::SpController:
		return SpControllerInputMappings.FindRef(Key);
	case EInputDevice::NsController:
		return NsControllerInputMappings.FindRef(Key);
	default:
		USK_LOG_ERROR("Unsupported input device");
		return nullptr;
	}
}

/**
 * @brief Get the key used by a specific input action
 * @param Context The input mapping context
 * @param InputAction The input action
 * @param MappableName The player mappable name for the action
 * @return The key used by the specified input action
 */
FKey UUSKGameInstance::GetKeyForInputAction(UInputMappingContext* Context, UInputAction* InputAction,
                                            const FName MappableName) const
{
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION < 3
	if (Context == nullptr || InputAction == nullptr)
	{
		return EKeys::Invalid;
	}
	
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr)
	{
		USK_LOG_WARNING("Unable to update player mappable input. PlayerController is nullptr");
		return EKeys::Invalid;
	}
	
	const UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (Subsystem == nullptr)
	{
		USK_LOG_WARNING("Unable to update player mappable input. Subsystem is nullptr");
		return EKeys::Invalid;
	}

	TArray<FEnhancedActionKeyMapping> Mappings = Context->GetMappings();
	for (FEnhancedActionKeyMapping Mapping : Mappings)
	{
		if (Mapping.Action == InputAction && Mapping.PlayerMappableOptions.Name == MappableName)
		{
			return Mapping.Key;
		}
	}
#endif
	
	return EKeys::Invalid;
}

/**
 * @brief Update the key bindings that was changed by the player
 */
void UUSKGameInstance::UpdateKeyBindings() const
{
#if ENGINE_MAJOR_VERSION >= 5
	if (SettingsConfig == nullptr)
	{
		return;
	}

	const USettingsData* Settings = USettingsUtils::LoadSettings();
	if (Settings == nullptr || Settings->KeyBindings.IsEmpty())
	{
		return;
	}
	
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr)
	{
		USK_LOG_WARNING("Unable to update player mappable input. PlayerController is nullptr");
		return;
	}
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (Subsystem == nullptr)
	{
		USK_LOG_WARNING("Unable to update player mappable input. Subsystem is nullptr");
		return;
	}

	USK_LOG_TRACE("Adding player mappable input configs to subsystem");
	
	TArray<FName> Keys;
	Settings->KeyBindings.GetKeys(Keys);
	for (const FName Key : Keys)
	{
#if ENGINE_MINOR_VERSION >= 2
		Subsystem->RemovePlayerMappedKeyInSlot(Key);
		Subsystem->AddPlayerMappedKeyInSlot(Key, Settings->KeyBindings[Key]);
#else
		Subsystem->RemovePlayerMappedKey(Key);
		Subsystem->AddPlayerMappedKey(Key, Settings->KeyBindings[Key]);
#endif
	}
#endif
}

/**
 * @brief Pause the game
 */
void UUSKGameInstance::PauseGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	OnGamePaused.Broadcast();
}

/**
 * @brief Unpause the game
 */
void UUSKGameInstance::UnpauseGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	OnGameUnpaused.Broadcast();
}

/**
 * @brief Update the difficulty
 * @param Difficulty The new difficulty
 */
void UUSKGameInstance::UpdateDifficulty(const int Difficulty) const
{
	USK_LOG_INFO("Updating difficulty: " + FString::FromInt(Difficulty));
	OnDifficultyUpdated.Broadcast(Difficulty);
}

/**
 * @brief Get the current difficulty
 * @return The current difficulty
 */
int UUSKGameInstance::GetDifficulty() const
{
	const int DefaultDifficulty = IsValid(SettingsConfig) ? SettingsConfig->GameplayDifficultyDefault : 0;
	const USettingsData* Settings = USettingsUtils::LoadSettings();
	if (IsValid(Settings))
	{
		return Settings->GameplayDifficultyModified ? Settings->GameplayDifficulty : DefaultDifficulty;
	}

	USK_LOG_WARNING("Failed to load settings. Using default difficulty value");
	return DefaultDifficulty;
}

/**
 * @brief Show a message popup
 * @param Data The data displayed in the message popup
 * @return A reference to the message popup
 */
UMessagePopupWidget* UUSKGameInstance::ShowMessagePopup(const FMessagePopupData Data)
{
	if (!IsValid(MessagePopupWidgetClass))
	{
		USK_LOG_WARNING("Unable to show message popup widget. Class not specified");
		return nullptr;
	}
	
	HideMessagePopup();
	MessagePopup = CreateWidget<UMessagePopupWidget>(GetWorld(), MessagePopupWidgetClass);
	
	if (IsValid(MessagePopup))
	{
		MessagePopup->Show(Data);
	}

	return MessagePopup;
}

/**
 * @brief Hide the message popup
 */
void UUSKGameInstance::HideMessagePopup()
{
	if (IsValid(MessagePopup))
	{
		MessagePopup->Hide();
		MessagePopup = nullptr;
	}
}

/**
 * @brief Load data at the specified index
 * @param Index The save slot index to load data from
 */
void UUSKGameInstance::LoadData(const int Index)
{
	if (!IsSaveSlotUsed(Index))
	{
		USK_LOG_INFO(*FString::Format(TEXT("Creating new save data in slot {0}"), { FString::FromInt(Index) }));
		USaveGame* NewData = UGameplayStatics::CreateSaveGameObject(SaveGameClass);
		CurrentSaveGame = dynamic_cast<UUSKSaveGame*>(NewData);
		OnDataLoadedEvent.Broadcast();
		return;
	}

	USK_LOG_INFO(*FString::Format(TEXT("Loading data from slot {0}"), { FString::FromInt(Index) }));
	USaveGame* LoadedData = UGameplayStatics::LoadGameFromSlot(GetSaveSlotName(Index), 0); 
	CurrentSaveGame = dynamic_cast<UUSKSaveGame*>(LoadedData);
	OnDataLoadedEvent.Broadcast();
}

/**
 * @brief Get the save file name for the save slot
 * @param Index The index of the save slot
 * @return The file name of the save slot at the specified index
 */
FString UUSKGameInstance::GetSaveSlotName(const int Index) const
{
	return *FString::Format(TEXT("SaveData{0}"), { FString::FromInt(Index) });
}

/**
 * @brief Initialize the features of the game instance after a delay
 */
void UUSKGameInstance::InitializeFeaturesAfterDelay()
{	
	USK_LOG_INFO(*FString::Format(TEXT("Delaying feature initialization by {0} seconds"),
			{ FString::SanitizeFloat(InitializeFeaturesDelay, 5) }));

	FLatentActionInfo LatentAction;
	LatentAction.Linkage = 0;
	LatentAction.CallbackTarget = this;
	LatentAction.UUID = GetUniqueID();
	LatentAction.ExecutionFunction = "InitializeFeatures";
	UKismetSystemLibrary::Delay(GetWorld(), InitializeFeaturesDelay, LatentAction);
}

/**
 * @brief Initialize the features of the game instance
 */
void UUSKGameInstance::InitializeFeatures()
{
	InitializeInputIndicators();

	USK_LOG_INFO("Initializing settings");
    USettingsUtils::Initialize(this);
	bIsFeaturesInitialized = true;
}

/**
 * @brief Start a timer to initialize the input indicators
 */
void UUSKGameInstance::InitializeInputIndicatorsAfterDelay()
{
	if (!IsInputIndicatorsEnabled)
	{
		USK_LOG_INFO("Input indicators are disabled");
		return;
	}
	
	USK_LOG_INFO(*FString::Format(TEXT("Delaying input indicator initialization by {0} seconds"),
			{ FString::SanitizeFloat(InitializeInputIndicatorsDelay, 5) }));

	FLatentActionInfo LatentAction;
	LatentAction.Linkage = 0;
	LatentAction.CallbackTarget = this;
	LatentAction.UUID = GetUniqueID();
	LatentAction.ExecutionFunction = "InitializeInputIndicators";
	UKismetSystemLibrary::Delay(GetWorld(), InitializeInputIndicatorsDelay, LatentAction);
}

/**
 * @brief Set the default input device and add an any key binding to keep the input device updated
 */
void UUSKGameInstance::InitializeInputIndicators()
{
	UpdateKeyBindings();
	
	USK_LOG_INFO("Setting default input device");
	CurrentInputDevice = EInputDevice::Unknown;
	if (UPlatformUtils::IsDesktop())
	{
		UpdateInputDevice(EKeys::SpaceBar);	
	}
	else
	{
		UpdateInputDevice(EKeys::Gamepad_FaceButton_Bottom);
	}

	OnInputDeviceUpdated.Broadcast();

	USK_LOG_INFO("Adding input binding");
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!IsValid(PlayerController))
	{
		USK_LOG_ERROR("Failed to add input binding. PlayerController is not valid");
		return;
	}

	if (!IsValid(PlayerController->InputComponent))
	{
		USK_LOG_ERROR("Failed to add input binding. InputComponent is not valid");
		return;
	}

	PlayerController->InputComponent->BindKey(EKeys::AnyKey, IE_Pressed,
		this, &UUSKGameInstance::UpdateInputDevice);
}

/**
 * @brief Update the current input device used by the player
 * @param Key The key that was pressed that caused the update
 */
void UUSKGameInstance::UpdateInputDevice(const FKey Key)
{
	if (!IsInputIndicatorsEnabled)
	{
		return;
	}
	
	const EInputDevice NewInputDevice = GetInputDevice(Key);
	if (NewInputDevice == CurrentInputDevice)
	{
		return;
	}

	CurrentInputDevice = NewInputDevice;
	bIsUsingGamepad = CurrentInputDevice != EInputDevice::KeyboardMouse;

	USK_LOG_INFO("Input device updated");
	OnInputDeviceUpdated.Broadcast();
}

/**
 * @brief Map an action and key to an input indicator icon
 * @param InputIndicators The array of input indicators already extracted for the action
 * @param Action The action that caused the update event
 * @param Key The key that caused the update event
 * @param RequiredAction The required action used to extract the correct input indicator icon
 * @param RequiredAmount The maximum amount of icons that should be extracted
 * @return A boolean value indicating if we've finished extracting the required amount of input indicator icons
 */
bool UUSKGameInstance::MapActionKeyToInputIndicator(TArray<UTexture2D*>& InputIndicators,
                                                    const UInputAction* Action, const FKey Key,
                                                    const UInputAction* RequiredAction, const int RequiredAmount)
{
	if (Action != RequiredAction || Key.IsGamepadKey() != bIsUsingGamepad)
	{
		return false;
	}

	UTexture2D* InputIndicator = GetInputIndicatorIconForKey(Key, CurrentInputDevice);
	if (InputIndicator == nullptr)
	{
		USK_LOG_WARNING("Unable to add input indicator to array. InputIndicator is nullptr");
		return false;
	}

	USK_LOG_TRACE("Adding input indicator to array");
	InputIndicators.AddUnique(InputIndicator);
	return InputIndicators.Num() >= RequiredAmount;
}

/**
 * @brief Get the input device based on the specified key
 * @param Key The key used to detect the input device
 * @return The input device based on the specified key
 */
EInputDevice UUSKGameInstance::GetInputDevice(const FKey Key)
{
	if (!Key.IsGamepadKey())
	{
		return EInputDevice::KeyboardMouse;
	}

	if (UPlatformUtils::IsConsoleMx())
	{
		return EInputDevice::MxController;
	}

	if (UPlatformUtils::IsConsoleSp())
	{
		return EInputDevice::SpController;
	}

	if (UPlatformUtils::IsConsoleNs())
	{
		return EInputDevice::NsController;
	}
	
	return EInputDevice::GenericController;
}