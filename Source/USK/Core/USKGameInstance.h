// Created by Henry Jooste

#pragma once

#include "InputDevice.h"
#include "Engine/GameInstance.h"
#include "USKSaveGame.h"
#include "USK/Settings/SettingsConfig.h"
#include "USK/Widgets/MessagePopupData.h"
#include "USKGameInstance.generated.h"

class UMessagePopupWidget;
class ULogConfig;
class UInputAction;
class UInputMappingContext;

/**
 * @brief A base game instance with support for saving and loading game data using multiple save slots
 */
UCLASS()
class USK_API UUSKGameInstance : public UGameInstance
{
	GENERATED_BODY()

	/**
	 * @brief Event used to notify other classes when the save data is loaded
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameInstanceOnDataLoadedDelegate);

	/**
	 * @brief Event used to notify other classes when the current input device is updated
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameInstanceOnInputDeviceUpdatedDelegate);

	/**
	 * @brief Event used to notify other classes when the game is paused
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGamePausedDelegate);

	/**
	 * @brief Event used to notify other classes when the game is unpaused
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameUnpausedDelegate);

	/**
	 * @brief Event used to notify other classes when the difficulty is updated
	 * @param Difficulty The new difficulty value
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameInstanceDifficultyUpdatedDelegate, int, Difficulty);
	
public:
	/**
	 * @brief The log configuration used when running the game in the editor
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Logger")
	ULogConfig* LogConfigEditor;

	/**
	 * @brief The log configuration used by debug builds
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Logger")
	ULogConfig* LogConfigDebug;

	/**
	 * @brief The log configuration used by development builds
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Logger")
	ULogConfig* LogConfigDevelopment;

	/**
	 * @brief The log configuration used by shipping builds
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Logger")
	ULogConfig* LogConfigShipping;
	
	/**
	 * @brief The class that holds the data that should be saved/loaded
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Save Data")
	TSubclassOf<UUSKSaveGame> SaveGameClass;

	/**
	 * @brief The configuration for the settings
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Settings")
	USettingsConfig* SettingsConfig;

	/**
	 * @brief Event used to notify other classes when the save data is loaded
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Save Data|Events")
	FGameInstanceOnDataLoadedDelegate OnDataLoadedEvent;

	/**
	 * @brief Is the input indicators feature enabled?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Input")
	bool IsInputIndicatorsEnabled = true;

	/**
	 * @brief The input mapping context used to extract the keys based on specific input actions
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Input",
		DisplayName = "Input Mapping Context (Optional)",
		meta=(EditCondition = "IsInputIndicatorsEnabled", EditConditionHides))
	UInputMappingContext* InputMappingContext;

	/**
	 * @brief A map of all keyboard/mouse keys and the texture displayed in the indicator
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Input",
		meta=(EditCondition = "IsInputIndicatorsEnabled", EditConditionHides))
	TMap<FKey, UTexture2D*> KeyboardMouseInputMappings;

	/**
	 * @brief A map of all generic controller keys and the texture displayed in the indicator
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Input",
		meta=(EditCondition = "IsInputIndicatorsEnabled", EditConditionHides))
	TMap<FKey, UTexture2D*> GenericControllerInputMappings;

	/**
	 * @brief A map of all Console MX controller keys and the texture displayed in the indicator
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Input",
		meta=(EditCondition = "IsInputIndicatorsEnabled", EditConditionHides))
	TMap<FKey, UTexture2D*> MxControllerInputMappings;

	/**
	 * @brief A map of all Console SP controller keys and the texture displayed in the indicator
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Input",
		meta=(EditCondition = "IsInputIndicatorsEnabled", EditConditionHides))
	TMap<FKey, UTexture2D*> SpControllerInputMappings;

	/**
	 * @brief A map of all Console NS controller keys and the texture displayed in the indicator
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Input",
		meta=(EditCondition = "IsInputIndicatorsEnabled", EditConditionHides))
	TMap<FKey, UTexture2D*> NsControllerInputMappings;

	/**
	 * @brief The widget class used to display message popups
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	TSubclassOf<UMessagePopupWidget> MessagePopupWidgetClass;

	/**
	 * @brief Event used to notify other classes when the current input device is updated
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Input|Events")
	FGameInstanceOnInputDeviceUpdatedDelegate OnInputDeviceUpdated;

	/**
	 * @brief Event used to notify other classes when the game is paused
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Input|Events")
	FGamePausedDelegate OnGamePaused;

	/**
	 * @brief Event used to notify other classes when the game is unpaused
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Input|Events")
	FGameUnpausedDelegate OnGameUnpaused;

	/**
	 * @brief Event used to notify other classes when the difficulty is updated
	 * @param Difficulty The new difficulty value
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Input|Events")
	FGameInstanceDifficultyUpdatedDelegate OnDifficultyUpdated;

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
	 * @brief Enable the input indicators feature
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Input")
	void EnableInputIndicators();

	/**
	 * @brief Disable the input indicators feature
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Input")
	void DisableInputIndicators();

	/**
	 * @brief Get the input indicator icon for a specific action
	 * @param InputAction The input action
	 * @param Amount The amount of icons to retrieve
	 * @return An array of input indicator icons for the specified action
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Input")
	TArray<UTexture2D*> GetInputIndicatorIcon(UInputAction* InputAction, int Amount);
	
	/**
	 * @brief Get the input indicator icon for a specific key
	 * @param Key The key used to retrieve the input indicator icon
	 * @param InputDevice The input device used to retrieve the input indicator icon
	 * @return The input indicator icon for the specified key
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Input")
	UTexture2D* GetInputIndicatorIconForKey(FKey Key, EInputDevice InputDevice) const;

	/**
	 * @brief Get the key used by a specific input action
	 * @param Context The input mapping context
	 * @param InputAction The input action
	 * @param MappableName The player mappable name for the action
	 * @return The key used by the specified input action
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Input")
	FKey GetKeyForInputAction(UInputMappingContext* Context, UInputAction* InputAction, FName MappableName) const;

	/**
	 * @brief Update the key bindings that was changed by the player 
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Input")
	void UpdateKeyBindings() const;

	/**
	 * @brief Pause the game
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Pause")
	void PauseGame();

	/**
	 * @brief Unpause the game
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Pause")
	void UnpauseGame();

	/**
	 * @brief Update the difficulty
	 * @param Difficulty The new difficulty
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Difficulty")
	void UpdateDifficulty(int Difficulty) const;

	/**
	 * @brief Get the current difficulty
	 * @return The current difficulty
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Difficulty")
	int GetDifficulty() const;

	/**
	 * @brief Show a message popup
	 * @param Data The data displayed in the message popup
	 * @return A reference to the message popup
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	UMessagePopupWidget* ShowMessagePopup(FMessagePopupData Data);

	/**
	 * @brief Hide the message popup
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void HideMessagePopup();

protected:
	/**
	 * @brief Virtual function to allow custom GameInstances an opportunity to set up what it needs
	 */
	virtual void Init() override;

	/**
	 * @brief Virtual function called after a map is loaded
	 * @param LoadTime The amount of time it took to load the map
	 * @param MapName The name of the map that was loaded
	 */
	virtual void LoadComplete(const float LoadTime, const FString& MapName) override;
	
private:	
	/**
	 * @brief A reference to the loaded save data
	 */
	UPROPERTY()
	UUSKSaveGame* CurrentSaveGame;

	/**
	 * @brief A reference to the message popup widget
	 */
	UPROPERTY()
	UMessagePopupWidget* MessagePopup;

	/**
	 * @brief A boolean flag used to check if the features of the game instance was initialized
	 */
	bool bIsFeaturesInitialized = false;

	/**
	 * @brief The delay before initializing the features of the game instance
	 */
	float InitializeFeaturesDelay = 0.2f;

	/**
	 * @brief The delay before initializing the input indicators
	 */
	float InitializeInputIndicatorsDelay = 0.2f;
	
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
	 * @brief Initialize the features of the game instance after a delay
	 */
	void InitializeFeaturesAfterDelay();

	/**
	 * @brief Initialize the features of the game instance
	 */
	UFUNCTION()
	void InitializeFeatures();

	/**
	 * @brief Start a timer to initialize the input indicators
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
};