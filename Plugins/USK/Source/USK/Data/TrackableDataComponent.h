// Created by Henry Jooste

#pragma once

#include "TrackableData.h"
#include "USK/Core/USKGameInstance.h"
#include "TrackableDataComponent.generated.h"

/**
 * @brief Actor component that tracks data
 */
UCLASS()
class USK_API UTrackableDataComponent : public UActorComponent
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FValueZeroDelegate, FName, Name);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FValueUpdatedDelegate, FName, Name, float, Value, float, ValuePercentage);

public:
	/**
	 * @brief The map of data to track
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Trackable Data")
	TMap<FName, FTrackableData> Data;

	/**
	 * @brief Event that is broadcasted every time the data value reaches 0
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Trackable Data|Events")
	FValueZeroDelegate OnValueZero;

	/**
	 * @brief Event that is broadcasted every time the data value is updated
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Trackable Data|Events")
	FValueUpdatedDelegate OnValueUpdated;

	/**
	 * @brief Create a new instance of UTrackableDataComponent
	 */
	UTrackableDataComponent();

	/**
	 * @brief Get the amount of the data
	 * @param Name The name of the data item
	 * @return The current amount of the data item
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Trackable Data")
	virtual float GetValue(const FName Name);

	/**
	 * @brief Get the value of the data as a percentage of to the max value
	 * @param Name The name of the data item
	 * @return The value of the data as a percentage of to the max value
	 */
	UFUNCTION(BlueprintPure, Category = "Ultimate Starter Kit|Trackable Data")
	virtual float GetValuePercentage(const FName Name);

	/**
	 * @brief Add an amount to the data
	 * @param Name The name of the data item
	 * @param Amount The amount to add
	 * @return The new amount of the data item
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Trackable Data")
	virtual float Add(const FName Name, const float Amount);

	/**
	 * @brief Remove an amount from the data
	 * @param Name The name of the data item
	 * @param Amount The amount to remove
	 * @return The new amount of the data item
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Trackable Data")
	virtual float Remove(const FName Name, const float Amount);

protected:
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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

private:
	/**
	 * @brief A reference to the current UUSKGameInstance
	 */
	UPROPERTY()
	UUSKGameInstance* GameInstance;
	
	/**
	 * @brief Load the data managed by this component
	 */
	void LoadData();

	/**
	 * @brief Save the value of the data
	 * @param Name The name of the data item
	 * @param Amount The current amount to save
	 */
	void SaveValue(const FName Name, const int Amount);
};
