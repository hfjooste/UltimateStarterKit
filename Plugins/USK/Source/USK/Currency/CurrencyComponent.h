// Created by Henry Jooste

#pragma once

#include "Currency.h"
#include "Components/ActorComponent.h"
#include "USK/Core/USKBaseComponent.h"
#include "CurrencyComponent.generated.h"

/**
 * @brief Actor component responsible for managing currency
 */
UCLASS(ClassGroup=("UltimateStarterKit"), DisplayName="Currency Component", meta=(BlueprintSpawnableComponent))
class USK_API UCurrencyComponent : public UUSKBaseComponent
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief A map of all currencies managed by this component
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, FCurrency> Currencies;

	/**
	 * @brief Get the amount of a currency
	 * @param CurrencyName The name of the currency
	 * @return The current amount of the currency
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Currency")
    int GetAmount(FName CurrencyName);

	/**
	 * @brief Add an amount to a currency
	 * @param CurrencyName The name of the currency
	 * @param Amount The amount to add
	 * @return The new amount of the currency
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Currency")
    int Add(FName CurrencyName, int Amount);

	/**
	 * @brief Remove an amount from a currency
	 * @param CurrencyName The name of the currency
	 * @param Amount The amount to remove
	 * @return The new amount of the currency
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Currency")
    int Remove(FName CurrencyName, int Amount);

protected:
	/**
	 * @brief Load the data managed by this component
	 */
	virtual void LoadData() override;
	
private:
	/**
	 * @brief Save the value of a currency
	 * @param CurrencyName The name of the currency
	 * @param Amount The current amount to save
	 */
	void SaveValue(const FName CurrencyName, const int Amount) const;
};