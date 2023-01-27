// Created by Henry Jooste

#include "CurrencyManagerComponent.h"
#include "Math/UnrealMathUtility.h"
#include "USK/Logger/Log.h"

/**
 * @brief Get the current amount of currency
 * @return The amount of currency
 */
int UCurrencyManagerComponent::GetAmount() const
{
	return Currency;
}

/**
 * @brief Add to the currency
 * @param Amount The amount to add
 * @return The new amount of currency
 */
int UCurrencyManagerComponent::Add(const int Amount)
{
	ULog::Info("CurrencyManagerComponent::Add",
		FString("Adding ").Append(FString::FromInt(Amount)).Append(" to ").Append(ID));
	Currency = FMath::Max(Currency + Amount, 0);
	ULog::Info("CurrencyManagerComponent::Add",
		FString("Current value of ").Append(ID).Append(" is ").Append(FString::FromInt(Currency)));
	SaveCurrency();
	return Currency;
}

/**
 * @brief Remove from the currency
 * @param Amount The amount to remove
 * @return The new amount of currency
 */
int UCurrencyManagerComponent::Remove(const int Amount)
{
	ULog::Info("CurrencyManagerComponent::Remove",
		FString("Removing ").Append(FString::FromInt(Amount)).Append(" from ").Append(ID));
	Currency = FMath::Max(Currency - Amount, 0);
	ULog::Info("CurrencyManagerComponent::Remove",
		FString("Current value of ").Append(ID).Append(" is ").Append(FString::FromInt(Currency)));
	SaveCurrency();
	return Currency;
}

/**
 * @brief Check if there is enough currency
 * @param RequiredAmount The required amount of currency
 * @return A boolean value indicating if there is enough currency
 */
bool UCurrencyManagerComponent::HaveEnough(const int RequiredAmount) const
{
	return Currency >= RequiredAmount;
}

/**
 * @brief Load the saved currency value using the save manager
 * @return The saved value of the currency
 */
void UCurrencyManagerComponent::LoadSavedCurrency()
{
	if (SaveManager == nullptr)
	{
		ULog::Info("CurrencyManagerComponent::LoadSavedCurrency",
			FString("Not loading value for ").Append(ID).Append(". Save manager not set"));
		Currency = 0;
		return;
	}

	ULog::Info("CurrencyManagerComponent::LoadSavedCurrency", FString("Loading value for ").Append(ID));
	UUSKSaveGame* SaveGame = SaveManager->GetSaveData();
	if (SaveGame == nullptr)
	{
		ULog::Error("CurrencyManagerComponent::LoadSavedCurrency",
			FString("Failed to load value for ").Append(ID).Append(". Save game is nullptr"));
		Currency = 0;
		return;
	}

	if (SaveGame->Currency.Contains(ID))
	{
		Currency = SaveGame->Currency[ID];
		return;
	}

	ULog::Info("CurrencyManagerComponent::LoadSavedCurrency",
	FString("No saved value for ").Append(ID).Append(". Resetting value to 0"));
	Currency = 0;
}

/**
 * @brief Save the currency value using the save manager
 */
void UCurrencyManagerComponent::SaveCurrency()
{
	if (SaveManager == nullptr)
	{
		ULog::Info("CurrencyManagerComponent::SaveCurrency",
			FString("Not saving value for ").Append(ID).Append(". Save manager not set"));
		return;
	}

	ULog::Info("CurrencyManagerComponent::SaveCurrency", FString("Saving value for ").Append(ID));
	UUSKSaveGame* SaveGame = SaveManager->GetSaveData();
	if (SaveGame == nullptr)
	{
		ULog::Error("CurrencyManagerComponent::SaveCurrency",
			FString("Failed to save value for ").Append(ID).Append(". Save game is nullptr"));
		return;
	}

	if (SaveGame->Currency.Contains(ID))
	{
		ULog::Info("CurrencyManagerComponent::SaveCurrency",
		FString("Updating value for ").Append(ID));
		SaveGame->Currency[ID] = GetAmount();	
	}
	else
	{
		ULog::Info("CurrencyManagerComponent::SaveCurrency",
			FString("Setting initial value for ").Append(ID));
		SaveGame->Currency.Add(ID, GetAmount());
	}

	SaveManager->SaveData();
	ULog::Info("CurrencyManagerComponent::SaveCurrency", FString("Value saved for ").Append(ID));
}