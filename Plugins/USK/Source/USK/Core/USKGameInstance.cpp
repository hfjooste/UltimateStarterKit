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
