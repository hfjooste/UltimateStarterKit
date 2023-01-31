// Created by Henry Jooste

#pragma once

#include "USKSaveGame.h"
#include "USKGameInstance.generated.h"

/**
 * @brief Game instance with support for saving/loading data
 */
UCLASS()
class USK_API UUSKGameInstance : public UGameInstance
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameInstanceOnDataLoadedDelegate);
	
public:
	/**
	 * @brief The class that holds the data that should be saved/loaded
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Save Data")
	TSubclassOf<UUSKSaveGame> SaveGameClass;

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
	 * @brief Event used to notify other classes when the save data is loaded
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Save Data|Events")
	FGameInstanceOnDataLoadedDelegate OnDataLoadedEvent;

private:
	
	/**
	 * @brief A reference to the loaded save data
	 */
	UPROPERTY()
	UUSKSaveGame* CurrentSaveGame;
	
	/**
	 * @brief The index of the save slot currently loaded
	 */
	int CurrentSaveSlot;

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
};
