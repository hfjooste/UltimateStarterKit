// Created by Henry Jooste

#include "USK/Stats/StatsComponent.h"
#include "USK/Logger/Log.h"

/**
 * @brief Create a new UStatsComponent instance
 */
UStatsComponent::UStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

/**
 * @brief Function called every frame on this ActorComponent
 * @param DeltaTime The time since the last tick
 * @param TickType The kind of tick this is, for example, are we paused, or 'simulating' in the editor
 * @param ThisTickFunction Internal tick function struct that caused this to run
 */
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<FName> Keys;
	Stats.GetKeys(Keys);
	for (FName Key : Keys)
	{
		if (Stats[Key].RegenerateAmount <= 0.0f || Stats[Key].Value >= Stats[Key].MaxValue)
		{
			continue;
		}

		if (Stats[Key].CurrentRegenerateDelay > 0.0f)
		{
			ULog::Info("StatsComponent::TickComponent",
				FString("Reducing regenerate delay for ").Append(Key.ToString()));
			Stats[Key].CurrentRegenerateDelay -= DeltaTime;
			continue;
		}

		Add(Key, Stats[Key].RegenerateAmount * DeltaTime);
	}
}

/**
 * @brief Load the data managed by this component
 */
void UStatsComponent::LoadData()
{
	if (GameInstance == nullptr)
	{
		ULog::Error("StatsComponent::LoadValues", "GameInstance is nullptr");
		return;
	}

	UUSKSaveGame* SaveGame = GameInstance->GetSaveData();
	if (SaveGame == nullptr)
	{
		ULog::Error("StatsComponent::LoadValues", "SaveGame is nullptr");
		return;
	}

	TArray<FName> StatsKeys;
	Stats.GetKeys(StatsKeys);
	for (FName Key : StatsKeys)
	{
		if (!Stats[Key].AutoSave || !SaveGame->Stats.Contains(Key))
		{
			ULog::Info("StatsComponent::LoadValues",
				FString("Resetting ").Append(Key.ToString()).Append(" to initial value"));
			Stats[Key].Value = Stats[Key].InitialValue;
			continue;
		}

		ULog::Info("StatsComponent::LoadValues",
				FString("Loading saved value for ").Append(Key.ToString()));
		Stats[Key].Value = SaveGame->Stats[Key];
	}
}

/**
 * @brief Get the value of a stat
 * @param StatName The name of the stat
 * @return The current value of the stat
 */
float UStatsComponent::GetValue(const FName StatName) const
{
	if (!Stats.Contains(StatName))
	{
		ULog::Error("StatsComponent::GetAmount", "Stat not added to map");
		return 0;
	}

	return Stats[StatName].Value;
}

/**
 * @brief Get the value of a stat as a percentage of to the max value
 * @param StatName The name of the stat
 * @return The value of a stat as a percentage of to the max value
 */
float UStatsComponent::GetValuePercentage(const FName StatName) const
{
	if (!Stats.Contains(StatName))
	{
		ULog::Error("StatsComponent::GetValuePercentage", "Stat not added to map");
		return 0;
	}

	return Stats[StatName].Value / Stats[StatName].MaxValue;
}

/**
 * @brief Add a value to the stat
 * @param StatName The name of the stat
 * @param Amount The amount to add
 * @return The new value of the stat
 */
float UStatsComponent::Add(const FName StatName, const float Amount)
{
	if (!Stats.Contains(StatName))
	{
		ULog::Error("StatsComponent::Add", "Stat not added to map");
		return 0.0f;
	}

	Stats[StatName].Value = FMath::Clamp(Stats[StatName].Value + Amount, 0.0f, Stats[StatName].MaxValue);	
	const float NewValue = Stats[StatName].Value;
	OnValueUpdated.Broadcast(StatName, NewValue, NewValue / Stats[StatName].MaxValue);

	if (NewValue == 0.0f)
	{
		ULog::Info("StatsComponent::Add", FString("Value is zero for ").Append(StatName.ToString()));
		OnValueZero.Broadcast(StatName);
	}

	if (Amount < 0.0f)
	{
		ULog::Info("StatsComponent::Add",
			FString("Resetting regenerate delay for ").Append(StatName.ToString()));
		Stats[StatName].CurrentRegenerateDelay = Stats[StatName].RegenerateDelay;
	}
	
	SaveValue(StatName, NewValue);
	return NewValue;
}

/**
 * @brief Remove a value from the stat
 * @param StatName The name of the stat
 * @param Amount The amount to remove
 * @return The new value of the stat
 */
float UStatsComponent::Remove(const FName StatName, const float Amount)
{
	return Add(StatName, -Amount);
}

/**
 * @brief Save the value of a stat
 * @param StatName The name of the stat
 * @param Value The current value to save
 */
void UStatsComponent::SaveValue(const FName StatName, const float Value) const
{
	if (!Stats[StatName].AutoSave)
	{
		return;
	}

	if (GameInstance == nullptr)
	{
		ULog::Error("StatsComponent::SaveValue", "GameInstance is nullptr");
		return;
	}

	UUSKSaveGame* SaveGame = GameInstance->GetSaveData();
	if (SaveGame == nullptr)
	{
		ULog::Error("StatsComponent::SaveValue", "GameInstance is nullptr");
		return;
	}

	if (SaveGame->Stats.Contains(StatName))
	{
		SaveGame->Stats[StatName] = Value;	
	}
	else
	{
		SaveGame->Stats.Add(StatName, Value);
	}

	GameInstance->SaveData();
}
