// Created by Henry Jooste

#include "SaveManager.h"
#include "Kismet/GameplayStatics.h"
#include "USK/Logger/Log.h"

/**
 * @brief Get the save data that is currently loaded
 * @return A reference to the current save data
 */
UUSKSaveGame* ASaveManager::GetSaveData() const
{
	if (CurrentSaveGame == nullptr)
	{
		ULog::Warning("SaveManager::GetSaveData", "Save Game is nullptr");
	}

	return CurrentSaveGame;
}

/**
 * @brief Save the modified data currently in memory
 */
void ASaveManager::SaveData()
{
	if (CurrentSaveGame == nullptr)
	{
		ULog::Error("SaveManager::SaveData", "Save Game is nullptr");
		return;
	}

	ULog::Info("SaveManager::SaveData", "Saving data");
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, GetSaveSlotName(CurrentSaveSlot), 0);
}

/**
 * @brief Set the current save slot
 * @param Index The index of the save slot
 */
void ASaveManager::SetCurrentSaveSlot(const int Index)
{
	ULog::Info("SaveManager::SetCurrentSaveSlot",
		FString("Changing save slot index to ").Append(FString::FromInt(Index)));
	
	CurrentSaveSlot = Index;
	LoadData(Index);
}

/**
 * @brief Check if a save slot is used
 * @param Index The index of the save slot to check
 * @return A boolean value indicating if the save slot is used
 */
bool ASaveManager::IsSaveSlotUsed(const int Index)
{
	return UGameplayStatics::DoesSaveGameExist(GetSaveSlotName(Index), 0);
}

/**
 * @brief Load data at the specified index
 * @param Index The save slot index to load data from
 */
void ASaveManager::LoadData(const int Index)
{
	if (!IsSaveSlotUsed(Index))
	{
		ULog::Info("SaveManager::LoadData",
				FString("Creating new save data in slot ").Append(FString::FromInt(Index)));
		USaveGame* NewData = UGameplayStatics::CreateSaveGameObject(SaveGameClass);
		CurrentSaveGame = dynamic_cast<UUSKSaveGame*>(NewData);
		OnDataLoadedEvent.ExecuteIfBound();
		return;
	}

	ULog::Info("SaveManager::LoadData",
				FString("Loading data from slot ").Append(FString::FromInt(Index)));
	USaveGame* LoadedData = UGameplayStatics::LoadGameFromSlot(GetSaveSlotName(Index), 0); 
	CurrentSaveGame = dynamic_cast<UUSKSaveGame*>(LoadedData);
	OnDataLoadedEvent.ExecuteIfBound();
}

/**
 * @brief Get the save file name for the save slot
 * @param Index The index of the save slot
 * @return The file name of the save slot at the specified index
 */
FString ASaveManager::GetSaveSlotName(const int Index)
{
	return FString("SaveData").Append(FString::FromInt(Index));
}