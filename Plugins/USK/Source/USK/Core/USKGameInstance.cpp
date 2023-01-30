// Created by Henry Jooste

#include "USKGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "USK/Logger/Log.h"

/**
 * @brief Get the save data that is currently loaded
 * @return A reference to the current save data
 */
UUSKSaveGame* UUSKGameInstance::GetSaveData() const
{
	if (CurrentSaveGame == nullptr)
	{
		ULog::Warning("USKSaveGame::GetSaveData", "Save Game is nullptr");
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
		ULog::Error("USKSaveGame::SaveData", "Save Game is nullptr");
		return;
	}

	ULog::Info("USKSaveGame::SaveData", "Saving data");
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, GetSaveSlotName(CurrentSaveSlot), 0);
}

/**
 * @brief Set the current save slot
 * @param Index The index of the save slot
 */
void UUSKGameInstance::SetCurrentSaveSlot(const int Index)
{
	ULog::Info("USKSaveGame::SetCurrentSaveSlot",
		FString("Changing save slot index to ").Append(FString::FromInt(Index)));
	
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
 * @brief Load data at the specified index
 * @param Index The save slot index to load data from
 */
void UUSKGameInstance::LoadData(const int Index)
{
	if (!IsSaveSlotUsed(Index))
	{
		ULog::Info("USKSaveGame::LoadData",
				FString("Creating new save data in slot ").Append(FString::FromInt(Index)));
		USaveGame* NewData = UGameplayStatics::CreateSaveGameObject(SaveGameClass);
		CurrentSaveGame = dynamic_cast<UUSKSaveGame*>(NewData);
		OnDataLoadedEvent.Broadcast();
		return;
	}

	ULog::Info("USKSaveGame::LoadData",
				FString("Loading data from slot ").Append(FString::FromInt(Index)));
	USaveGame* LoadedData = UGameplayStatics::LoadGameFromSlot(GetSaveSlotName(Index), 0); 
	CurrentSaveGame = dynamic_cast<UUSKSaveGame*>(LoadedData);
	OnDataLoadedEvent.Broadcast();
}

/**
 * @brief Get the save file name for the save slot
 * @param Index The index of the save slot
 * @return The file name of the save slot at the specified index
 */
FString UUSKGameInstance::GetSaveSlotName(const int Index)
{
	return FString("SaveData").Append(FString::FromInt(Index));
}