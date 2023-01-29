// Created by Henry Jooste

#pragma once

#include "Components/ActorComponent.h"
#include "USK/Data/SaveManager.h"
#include "StatsComponent.generated.h"

/**
 * @brief Actor component responsible for managing a character stat
 */
UCLASS(ClassGroup=("UltimateStarterKit"), DisplayName="Stat Component", meta=(BlueprintSpawnableComponent))
class USK_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FValueZeroEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FValueUpdatedEvent, float, Value, float, ValuePercentage);

public:
	/**
	 * @brief A reference to the save manager used to automatically save the value
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Save Data")
	ASaveManager* SaveManager;

	/**
	 * @brief The unique ID associated with the stat being managed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Save Data")
	FString ID;
	
	/**
	 * @brief Create a new instance of the stats component
	 */
	UStatsComponent();
	
	/**
	 * @brief Get the current stat value
	 * @return The current stat value
	 */
	UFUNCTION(BlueprintPure, Category = "Ultimate Starter Kit|Stats")
	float GetValue() const;

	/**
	 * @brief Get the current stat value as a percentage of the max value
	 * @return The current stat value as a percentage of the max value
	 */
	UFUNCTION(BlueprintPure, Category = "Ultimate Starter Kit|Stats")
	float GetValuePercentage() const;
	
	/**
	 * @brief Update the current stat value
	 * @param Amount The amount to add to the stat value
	 * @return The new stat value
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Stats")
	float UpdateValue(float Amount);

	/**
	 * @brief Load the saved value for the stat using the save manager
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Stats")
	void LoadValue();

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
	 * @brief The initial value of the stat 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats");
	float InitialValue = 100.0f;
	
	/**
	 * @brief The maximum value of the stat 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats");
	float MaxValue = 100.0f;

	/**
	 * @brief The amount of value that is regenerated every second
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats");
	float Regenerate;

	/**
	 * @brief The delay before the value is regenerated
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats");
	float RegenerateDelay;
	
	/**
	 * @brief Begins Play for the component
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Function called every frame on this ActorComponent
	 * @param DeltaTime The time since the last tick
	 * @param TickType The kind of tick this is, for example, are we paused, or 'simulating' in the editor
	 * @param ThisTickFunction Internal tick function struct that caused this to run
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:	
	/**
	 * @brief The current stat value
	 */
	float Value;

	/**
	 * @brief The current delay before regenerating the value
	 */
	float CurrentRegenerateDelay;

	/**
	 * @brief Save the stat value using the save manager
	 */
	void SaveValue();
};