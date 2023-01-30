// Created by Henry Jooste

#pragma once

#include "Stat.h"
#include "USK/Core/USKBaseComponent.h"
#include "StatsComponent.generated.h"

/**
 * @brief Actor component responsible for managing a character stat
 */
UCLASS(ClassGroup=("UltimateStarterKit"), DisplayName="Stat Component", meta=(BlueprintSpawnableComponent))
class USK_API UStatsComponent : public UUSKBaseComponent
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FValueZeroEvent, FName, Name);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FValueUpdatedEvent, FName, Name, float, Value, float, ValuePercentage);

public:
	/**
	 * @brief A map of all stats managed by this component
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FStat> Stats;

	/**
	 * @brief Create a new UStatsComponent instance
	 */
	UStatsComponent();

	/**
	 * @brief Get the value of a stat
	 * @param StatName The name of the stat
	 * @return The current value of the stat
	 */
	UFUNCTION(BlueprintPure, Category = "Ultimate Starter Kit|Stats")
	float GetValue(FName StatName) const;

	/**
	 * @brief Get the value of a stat as a percentage of to the max value
	 * @param StatName The name of the stat
	 * @return The value of a stat as a percentage of to the max value
	 */
	UFUNCTION(BlueprintPure, Category = "Ultimate Starter Kit|Stats")
	float GetValuePercentage(FName StatName) const;

	/**
	 * @brief Add a value to the stat
	 * @param StatName The name of the stat
	 * @param Amount The amount to add
	 * @return The new value of the stat
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Stats")
	float Add(FName StatName, float Amount);

	/**
	 * @brief Remove a value from the stat
	 * @param StatName The name of the stat
	 * @param Amount The amount to remove
	 * @return The new value of the stat
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Stats")
	float Remove(FName StatName, float Amount);

	/**
	 * @brief Event that is broadcasted every time the stat value is updated
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Stats|Events")
	FValueUpdatedEvent OnValueUpdated;

	/**
	 * @brief Event that is broadcasted every time the stat value reaches 0
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Stats|Events")
	FValueZeroEvent OnValueZero;

protected:
	/**
	 * @brief Function called every frame on this ActorComponent
	 * @param DeltaTime The time since the last tick
	 * @param TickType The kind of tick this is, for example, are we paused, or 'simulating' in the editor
	 * @param ThisTickFunction Internal tick function struct that caused this to run
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @brief Load the data managed by this component
	 */
	virtual void LoadData() override;
	
private:
	/**
	 * @brief Save the value of a stat
	 * @param StatName The name of the stat
	 * @param Value The current value to save
	 */
	void SaveValue(const FName StatName, const float Value) const;
};