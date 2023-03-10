// Created by Henry Jooste

#pragma once

#include "InputDevice.h"
#include "Engine/GameInstance.h"
#include "USKSaveGame.h"
#include "USK/Character/PlatformerAnimationInstance.h"
#include "USKGameInstance.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * @brief Game instance with support for saving/loading data
 */
UCLASS()
class USK_API UUSKGameInstance : public UGameInstance
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameInstanceOnDataLoadedDelegate);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameInstanceOnInputDeviceUpdatedDelegate);
	
public:
	/**
	 * @brief The class that holds the data that should be saved/loaded
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Save Data")
	TSubclassOf<UUSKSaveGame> SaveGameClass;

	/**
	 * @brief Event used to notify other classes when the save data is loaded
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Save Data|Events")
	FGameInstanceOnDataLoadedDelegate OnDataLoadedEvent;

	/**
	 * @brief The input mapping context used to extract the keys based on specific input actions
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Input",
		DisplayName = "Input Mapping Context (Optional)")
	UInputMappingContext* InputMappingContext;

	/**
	 * @brief A map of all keyboard/mouse keys and the texture displayed in the indicator
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Input")
	TMap<FKey, UTexture2D*> KeyboardMouseInputMappings;

	/**
	 * @brief A map of all generic controller keys and the texture displayed in the indicator
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Input")
	TMap<FKey, UTexture2D*> GenericControllerInputMappings;

	/**
	 * @brief A map of all Xbox controller keys and the texture displayed in the indicator
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Input")
	TMap<FKey, UTexture2D*> XboxControllerInputMappings;

	/**
	 * @brief A map of all Playstation controller keys and the texture displayed in the indicator
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Input")
	TMap<FKey, UTexture2D*> PlaystationControllerInputMappings;

	/**
	 * @brief A map of all Switch controller keys and the texture displayed in the indicator
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Input")
	TMap<FKey, UTexture2D*> SwitchControllerInputMappings;

	/**
	 * @brief Event used to notify other classes when the current input device is updated
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Input|Events")
	FGameInstanceOnInputDeviceUpdatedDelegate OnInputDeviceUpdated;

	/**
	 * @brief Get the save data that is currently loaded
	 * @return A reference to the current save data
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Save Data")
	UUSKSaveGame* GetSaveData() const;

	/**
	 * @brief Save the modified data currently in memory
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Save Data")
	void SaveData();

	/**
	 * @brief Set the current save slot
	 * @param Index The index of the save slot
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Save Data")
	void SetCurrentSaveSlot(int Index);

	/**
	 * @brief Check if a save slot is used
	 * @param Index The index of the save slot to check
	 * @return A boolean value indicating if the save slot is used
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Save Data")
	bool IsSaveSlotUsed(int Index);

	/**
	 * @brief Get the input indicator icon for a specific action
	 * @param InputAction The input action
	 * @param Amount The amount of icons to retrieve
	 * @return An array of input indicator icons for the specified action
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Input")
	TArray<UTexture2D*> GetInputIndicatorIcon(UInputAction* InputAction, int Amount);

protected:
	/**
	 * @brief Virtual function to allow custom GameInstances an opportunity to set up what it needs
	 */
	virtual void Init() override;
	
private:	
	/**
	 * @brief A reference to the loaded save data
	 */
	UPROPERTY()
	UUSKSaveGame* CurrentSaveGame;

	/**
	 * @brief The delay before initializing the input indicators
	 */
	float InitializeInputIndicatorsDelay = 0.1f;
	
	/**
	 * @brief The index of the save slot currently loaded
	 */
	int CurrentSaveSlot;

	/**
	 * @brief The current input device used by the player
	 */
	EInputDevice CurrentInputDevice = EInputDevice::Unknown;

	/**
	 * @brief Is the current input device a gamepad/controller?
	 */
	bool bIsUsingGamepad;

	/**
	 * @brief Load data at the specified index
	 * @param Index The save slot index to load data from
	 */
	void LoadData(int Index);
	
	/**
	 * @brief Get the save file name for the save slot
	 * @param Index The index of the save slot
	 * @return The file name of the save slot at the specified index
	 */
	FString GetSaveSlotName(int Index) const;

	/**
	 * @brief Initialize the input indicators after a delay
	 */
	void InitializeInputIndicatorsAfterDelay();
	
	/**
	 * @brief Set the default input device and add an any key binding to keep the input device updated
	 */
	UFUNCTION()
	void InitializeInputIndicators();

	/**
	 * @brief Update the current input device used by the player
	 * @param Key The key that was pressed that caused the update
	 */
	void UpdateInputDevice(FKey Key);

	/**
	 * @brief Map an action and key to an input indicator icon
	 * @param InputIndicators The array of input indicators already extracted for the action
	 * @param Action The action that caused the update event
	 * @param Key The key that caused the update event
	 * @param RequiredAction The required action used to extract the correct input indicator icon
	 * @param RequiredAmount The maximum amount of icons that should be extracted
	 * @return A boolean value indicating if we've finished extracting the required amount of input indicator icons
	 */
	bool MapActionKeyToInputIndicator(TArray<UTexture2D*>& InputIndicators, const UInputAction* Action,
	                                  const FKey Key, const UInputAction* RequiredAction, const int RequiredAmount);

	/**
	 * @brief Get the input device based on the specified key
	 * @param Key The key used to detect the input device
	 * @return The input device based on the specified key
	 */
	EInputDevice GetInputDevice(FKey Key);

	/**
	 * @brief Get the input indicator icon for a specific key
	 * @param Key The key used to retrieve the input indicator icon
	 * @return The input indicator icon for the specified key
	 */
	UTexture2D* GetInputIndicatorIconForKey(FKey Key) const;
};
