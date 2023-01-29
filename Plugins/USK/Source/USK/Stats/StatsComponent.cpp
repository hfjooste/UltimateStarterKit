// Created by Henry Jooste

#include "USK/Stats/StatsComponent.h"

#include "USK/Data/SaveManager.h"
#include "USK/Logger/Log.h"

/**
 * @brief Create a new instance of the stats component
 */
UStatsComponent::UStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

/**
 * @brief Begins Play for the component
 */
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	ULog::Info("StatsComponent::BeginPlay", "Initializing Stats component");

	LoadValue();
	if (SaveManager != nullptr)
	{
		SaveManager->OnDataLoadedEvent.AddDynamic(this, &UStatsComponent::LoadValue);
	}	
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
	if (Regenerate <= 0.0f || Value >= MaxValue)
	{
		return;
	}

	if (CurrentRegenerateDelay > 0.0f)
	{
		ULog::Info("StatsComponent::TickComponent", "Reducing regenerate delay");
		CurrentRegenerateDelay -= DeltaTime;
		return;
	}

	ULog::Info("StatsComponent::TickComponent", "Regenerating value");
	UpdateValue(Regenerate * DeltaTime);
}

/**
 * @brief Get the current stat value
 * @return The current stat value
 */
float UStatsComponent::GetValue() const
{
	return Value;
}

/**
 * @brief Get the current stat value as a percentage of the max value
 * @return The current stat value as a percentage of the max value
 */
float UStatsComponent::GetValuePercentage() const
{
	return Value / MaxValue;
}

/**
 * @brief Update the current stat value
 * @param Amount The amount to add to the stat value
 * @return The new stat value
 */
float UStatsComponent::UpdateValue(const float Amount)
{
	const float PreviousValue = Value;
	Value = FMath::Clamp(Value + Amount, 0.0f, MaxValue);
	OnValueUpdated.Broadcast(Value, GetValuePercentage());
	SaveValue();
	
	ULog::Info("StatsComponent::UpdateValue", FString("Value updated: ").Append(FString::FromInt(Value)));
	if (Regenerate > 0.0f && PreviousValue > Value)
	{
		ULog::Info("StatsComponent::UpdateValue", "Resetting regenerate delay");
		CurrentRegenerateDelay = RegenerateDelay;
	}

	if (Value == 0.0f)
	{
		ULog::Info("StatsComponent::UpdateValue", "Value is zero");
		OnValueZero.Broadcast();
	}
	
	return Value;
}

/**
 * @brief Load the saved value for the stat using the save manager
 */
void UStatsComponent::LoadValue()
{
	if (SaveManager == nullptr)
	{
		ULog::Info("StatsComponent::LoadValue",
			FString("Not loading value for ").Append(ID).Append(". Save manager not set"));
		UpdateValue(InitialValue);
		return;
	}

	ULog::Info("StatsComponent::LoadValue", FString("Loading value for ").Append(ID));
	UUSKSaveGame* SaveGame = SaveManager->GetSaveData();
	if (SaveGame == nullptr)
	{
		ULog::Error("StatsComponent::LoadValue",
			FString("Failed to load value for ").Append(ID).Append(". Save game is nullptr"));
		UpdateValue(InitialValue);
		return;
	}

	if (SaveGame->Stats.Contains(ID))
	{
		UpdateValue(SaveGame->Stats[ID]);
		return;
	}

	ULog::Info("StatsComponent::LoadValue", FString("No saved value for ").Append(ID));
	UpdateValue(InitialValue);
}

/**
 * @brief Save the stat value using the save manager
 */
void UStatsComponent::SaveValue()
{
	if (SaveManager == nullptr)
	{
		return;
	}

	ULog::Info("StatsComponent::SaveValue", FString("Saving value for ").Append(ID));
	UUSKSaveGame* SaveGame = SaveManager->GetSaveData();
	if (SaveGame == nullptr)
	{
		ULog::Error("StatsComponent::SaveValue",
			FString("Failed to save value for ").Append(ID).Append(". Save game is nullptr"));
		return;
	}

	if (SaveGame->Stats.Contains(ID))
	{
		ULog::Info("StatsComponent::SaveValue", FString("Updating value for ").Append(ID));
		SaveGame->Stats[ID] = GetValue();	
	}
	else
	{
		ULog::Info("StatsComponent::SaveValue", FString("Setting initial value for ").Append(ID));
		SaveGame->Stats.Add(ID, GetValue());
	}

	SaveManager->SaveData();
	ULog::Info("StatsComponent::SaveValue", FString("Value saved for ").Append(ID));
}
