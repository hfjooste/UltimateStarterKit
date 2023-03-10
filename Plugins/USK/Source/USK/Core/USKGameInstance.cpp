// Created by Henry Jooste

#include "USKGameInstance.h"

#include "EnhancedInputSubsystems.h"
#include "InputDevice.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"
#include "USK/Logger/Log.h"

/**
 * @brief Virtual function to allow custom GameInstances an opportunity to set up what it needs
 */
void UUSKGameInstance::Init()
{
	Super::Init();
	GetWorld()->OnWorldBeginPlay.AddUObject(this, &UUSKGameInstance::InitializeInputIndicatorsAfterDelay);
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
 * @brief Initialize the input indicators after a delay
 */
void UUSKGameInstance::InitializeInputIndicatorsAfterDelay()
{
	USK_LOG_INFO(*FString::Format(TEXT("Delaying input indicator initialization by {0} seconds"),
		{ FString::SanitizeFloat(InitializeInputIndicatorsDelay, 5) }));
	
	FLatentActionInfo LatentAction;
	LatentAction.Linkage = 0;
	LatentAction.CallbackTarget = this;
	LatentAction.UUID = GetUniqueID();
	LatentAction.ExecutionFunction = "InitializeInputIndicators";
	UKismetSystemLibrary::RetriggerableDelay(GetWorld(), InitializeInputIndicatorsDelay, LatentAction);
}

/**
 * @brief Set the default input device and add an any key binding to keep the input device updated
 */
void UUSKGameInstance::InitializeInputIndicators()
{
	USK_LOG_INFO("Setting default input device");

	CurrentInputDevice = EInputDevice::Unknown;
#if PLATFORM_DESKTOP || PLATFORM_WINDOWS || PLATFORM_LINUX || PLATFORM_MAC
	UpdateInputDevice(EKeys::SpaceBar);
#else
	UpdateInputDevice(EKeys::Gamepad_FaceButton_Bottom);
#endif

	OnInputDeviceUpdated.Broadcast();

	USK_LOG_INFO("Adding input binding");
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr)
	{
		USK_LOG_ERROR("Failed to add input binding. PlayerController is nullptr");
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

	UTexture2D* InputIndicator = GetInputIndicatorIconForKey(Key);
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

	const FString Platform = UGameplayStatics::GetPlatformName();
	if (Platform.Contains("xbox"))
	{
		return EInputDevice::XboxController;
	}

	if (Platform.Contains("ps") || Platform.Contains("station"))
	{
		return EInputDevice::PlaystationController;
	}

	if (Platform.Contains("nintendo") || Platform.Contains("switch"))
	{
		return EInputDevice::SwitchController;
	}
	
	return EInputDevice::GenericController;
}

/**
 * @brief Get the input indicator icon for a specific key
 * @param Key The key used to retrieve the input indicator icon
 * @return The input indicator icon for the specified key
 */
UTexture2D* UUSKGameInstance::GetInputIndicatorIconForKey(const FKey Key) const
{
	switch (CurrentInputDevice)
	{
	case EInputDevice::KeyboardMouse:
		return KeyboardMouseInputMappings.FindRef(Key);
	case EInputDevice::GenericController:
		return GenericControllerInputMappings.FindRef(Key);
	case EInputDevice::XboxController:
		return XboxControllerInputMappings.FindRef(Key);
	case EInputDevice::PlaystationController:
		return PlaystationControllerInputMappings.FindRef(Key);
	case EInputDevice::SwitchController:
		return SwitchControllerInputMappings.FindRef(Key);
	default:
		USK_LOG_ERROR("Unsupported input device");
		return nullptr;
	}
}
