// Created by Henry Jooste

#include "TrackableDataComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "USK/Core/USKGameInstance.h"
#include "USK/Logger/Log.h"

/**
 * @brief Create a new instance of UTrackableDataComponent
 */
UTrackableDataComponent::UTrackableDataComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

/**
 * @brief Begins Play for the component
 */
void UTrackableDataComponent::BeginPlay()
{
	Super::BeginPlay();

	UGameInstance* CurrentGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	GameInstance = dynamic_cast<UUSKGameInstance*>(CurrentGameInstance);
	
	LoadData();
	if (GameInstance != nullptr)
	{
		GameInstance->OnDataLoadedEvent.AddDynamic(this, &UTrackableDataComponent::LoadData);
	}
}

/**
 * @brief Function called every frame on this ActorComponent
 * @param DeltaTime The time since the last tick
 * @param TickType The kind of tick this is, for example, are we paused, or 'simulating' in the editor
 * @param ThisTickFunction Internal tick function struct that caused this to run
 */
void UTrackableDataComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<FName> Keys;
	Data.GetKeys(Keys);
	for (FName Key : Keys)
	{
		if (!Data[Key].AutoGenerate || Data[Key].GenerateAmount <= 0.0f ||
			Data[Key].CurrentValue >= Data[Key].MaxValue)
		{
			continue;
		}

		if (Data[Key].CurrentGenerateDelay > 0.0f)
		{
			USK_LOG_TRACE(*FString::Format(TEXT("Reducing regenerate delay for {0}"), { Key.ToString() }));
			Data[Key].CurrentGenerateDelay -= DeltaTime;
			continue;
		}

		Add(Key, Data[Key].GenerateAmount * DeltaTime);
	}
}

/**
 * @brief Get the amount of the data
 * @param Name The name of the data item
 * @return The current amount of the data item
 */
float UTrackableDataComponent::GetValue(const FName Name)
{
	if (!Data.Contains(Name))
	{
		USK_LOG_ERROR(*FString::Format(TEXT("Data not added to map ({0})"), { Name.ToString() }));
		return 0.0f;
	}

	return Data[Name].CurrentValue;
}

/**
 * @brief Get the value of the data as a percentage of to the max value
 * @param Name The name of the data item
 * @return The value of the data as a percentage of to the max value
 */
float UTrackableDataComponent::GetValuePercentage(const FName Name)
{
	if (!Data.Contains(Name))
	{
		USK_LOG_ERROR(*FString::Format(TEXT("Data not added to map ({0})"), { Name.ToString() }));
		return 0.0f;
	}

	if (Data[Name].MaxValue == 0.0f)
	{
		USK_LOG_ERROR(*FString::Format(TEXT("Max value is 0.0f ({0})"), { Name.ToString() }));
		return 0.0f;
	}

	return Data[Name].CurrentValue / Data[Name].MaxValue;
}

/**
 * @brief Add an amount to the data
 * @param Name The name of the data item
 * @param Amount The amount to add
 * @return The new amount of the data item
 */
float UTrackableDataComponent::Add(const FName Name, const float Amount)
{
	if (!Data.Contains(Name))
	{
		USK_LOG_ERROR(*FString::Format(TEXT("Data not added to map ({0})"), { Name.ToString() }));
		return 0.0f;
	}

	const float Max = Data[Name].EnforceMaxValue ? Data[Name].MaxValue : FLT_MAX;
	Data[Name].CurrentValue = FMath::Clamp(Data[Name].CurrentValue + Amount, 0.0f, Max);	
	const int NewValue = Data[Name].CurrentValue;
	OnValueUpdated.Broadcast(Name, NewValue, GetValuePercentage(Name));

	if (NewValue == 0.0f)
	{
		USK_LOG_INFO(*FString::Format(TEXT("Value is zero for {0}"), { Name.ToString() }));
		OnValueZero.Broadcast(Name);
	}

	if (Amount < 0.0f && Data[Name].AutoGenerate)
	{
		USK_LOG_INFO(*FString::Format(TEXT("Resetting regenerate delay for {0}"), { Name.ToString() }));
		Data[Name].CurrentGenerateDelay = Data[Name].GenerateDelay;
	}
	
	SaveValue(Name, NewValue);
	return NewValue;
}

/**
 * @brief Remove an amount from the data
 * @param Name The name of the data item
 * @param Amount The amount to remove
 * @return The new amount of the data item
 */
float UTrackableDataComponent::Remove(const FName Name, const float Amount)
{
	return Add(Name, -Amount);
}

/**
 * @brief Load the data managed by this component
 */
void UTrackableDataComponent::LoadData()
{
	bool DisableSaveData = false;
	if (GameInstance == nullptr)
	{
		DisableSaveData = true;
		USK_LOG_ERROR("GameInstance is nullptr");
	}

	UUSKSaveGame* SaveGame = GameInstance->GetSaveData();
	if (SaveGame == nullptr)
	{
		DisableSaveData = true;
		USK_LOG_ERROR("SaveGame is nullptr");
	}

	TArray<FName> Keys;
	Data.GetKeys(Keys);
	for (FName Key : Keys)
	{
		if (DisableSaveData || !Data[Key].AutoSave || !SaveGame->TrackableData.Contains(Key))
		{
			USK_LOG_INFO(*FString::Format(TEXT("Resetting {0} to initial value"), { Key.ToString() }));
			Data[Key].CurrentValue = Data[Key].InitialValue;
			continue;
		}

		USK_LOG_INFO(*FString::Format(TEXT("Loading saved value for {0}"), { Key.ToString() }));
		Data[Key].CurrentValue = SaveGame->TrackableData[Key];
	}
}

/**
 * @brief Save the value of the data
 * @param Name The name of the data item
 * @param Amount The current amount to save
 */
void UTrackableDataComponent::SaveValue(const FName Name, const int Amount)
{
	if (!Data[Name].AutoSave)
	{
		return;
	}

	if (GameInstance == nullptr)
	{
		USK_LOG_ERROR("GameInstance is nullptr");
		return;
	}

	UUSKSaveGame* SaveGame = GameInstance->GetSaveData();
	if (SaveGame == nullptr)
	{
		USK_LOG_ERROR("GameInstance is nullptr");
		return;
	}

	if (SaveGame->TrackableData.Contains(Name))
	{
		SaveGame->TrackableData[Name] = Amount;	
	}
	else
	{
		SaveGame->TrackableData.Add(Name, Amount);
	}

	GameInstance->SaveData();
}
