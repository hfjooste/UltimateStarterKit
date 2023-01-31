// Created by Henry Jooste

#include "CurrencyComponent.h"
#include "Math/UnrealMathUtility.h"
#include "USK/Core/USKGameInstance.h"
#include "USK/Logger/Log.h"

/**
 * @brief Get the amount of a currency
 * @param CurrencyName The name of the currency
 * @return The current amount of the currency
 */
int UCurrencyComponent::GetAmount(const FName CurrencyName)
{
	if (!Currencies.Contains(CurrencyName))
	{
		USK_LOG_ERROR("Currency not added to map");
		return 0;
	}

	return Currencies[CurrencyName].Amount;
}

/**
 * @brief Add an amount to a currency
 * @param CurrencyName The name of the currency
 * @param Amount The amount to add
 * @return The new amount of the currency
 */
int UCurrencyComponent::Add(const FName CurrencyName, const int Amount)
{
	if (!Currencies.Contains(CurrencyName))
	{
		USK_LOG_ERROR("Currency not added to map");
		return 0;
	}

	Currencies[CurrencyName].Amount = FMath::Max(Currencies[CurrencyName].Amount + Amount, 0);	
	const int NewAmount = Currencies[CurrencyName].Amount;
	SaveValue(CurrencyName, NewAmount);
	return NewAmount;
}

/**
 * @brief Add an amount to a currency
 * @param CurrencyName The name of the currency
 * @param Amount The amount to add
 * @return The new amount of the currency
 */
int UCurrencyComponent::Remove(const FName CurrencyName, const int Amount)
{
	return Add(CurrencyName, -Amount);
}

/**
 * @brief Load the data managed by this component
 */
void UCurrencyComponent::LoadData()
{	
	if (GameInstance == nullptr)
	{
		USK_LOG_ERROR("GameInstance is nullptr");
		return;
	}

	UUSKSaveGame* SaveGame = GameInstance->GetSaveData();
	if (SaveGame == nullptr)
	{
		USK_LOG_ERROR("SaveGame is nullptr");
		return;
	}

	TArray<FName> CurrencyKeys;
	Currencies.GetKeys(CurrencyKeys);
	for (FName Key : CurrencyKeys)
	{
		if (!Currencies[Key].AutoSave || !SaveGame->Currency.Contains(Key))
		{
			USK_LOG_INFO(*FString::Format(TEXT("Resetting {0} to initial value"), { Key.ToString() }));
			Currencies[Key].Amount = Currencies[Key].InitialAmount;
			continue;
		}

		USK_LOG_INFO(*FString::Format(TEXT("Loading saved value for {0}"), { Key.ToString() }));
		Currencies[Key].Amount = SaveGame->Currency[Key];
	}
}

/**
 * @brief Save the value of a currency
 * @param CurrencyName The name of the currency
 * @param Amount The current amount to save
 */
void UCurrencyComponent::SaveValue(const FName CurrencyName, const int Amount) const
{
	if (!Currencies[CurrencyName].AutoSave)
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

	if (SaveGame->Currency.Contains(CurrencyName))
	{
		SaveGame->Currency[CurrencyName] = Amount;	
	}
	else
	{
		SaveGame->Currency.Add(CurrencyName, Amount);
	}

	GameInstance->SaveData();
}
