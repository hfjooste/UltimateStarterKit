// Created by Henry Jooste

#pragma once

#include "Components/ActorComponent.h"
#include "USK/Data/SaveManager.h"
#include "CurrencyManagerComponent.generated.h"

/**
 * @brief Actor component responsible for tracking a specific currency
 */
UCLASS()
class USK_API UCurrencyManagerComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief A reference to the save manager used to automatically save currency values
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Save Data")
	ASaveManager* SaveManager;
	
	/**
	 * @brief The unique ID associated with the currency being managed
	 */
	FString ID;

	/**
	 * @brief Get the current amount of currency
	 * @return The amount of currency
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Currency Manager")
	int GetAmount() const;

	/**
	 * @brief Add to the currency
	 * @param Amount The amount to add
	 * @return The new amount of currency
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Currency Manager")
	int Add(int Amount);

	/**
	 * @brief Remove from the currency
	 * @param Amount The amount to remove
	 * @return The new amount of currency
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Currency Manager")
	int Remove(int Amount);

	/**
	 * @brief Check if there is enough currency
	 * @param RequiredAmount The required amount of currency
	 * @return A boolean value indicating if there is enough currency
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Currency Manager")
	bool HaveEnough(int RequiredAmount) const;

	/**
	 * @brief Load the saved currency value using the save manager
	 */
	void LoadSavedCurrency();

private:
	/**
	 * @brief The amount of currency
	 */
	int Currency = 0;

	/**
	 * @brief Save the currency value using the save manager
	 */
	void SaveCurrency();
};