// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "USK/Data/TrackableDataComponent.h"
#include "CollectableItemIcon.generated.h"

/**
 * @brief A widget used to display the collection state of an item by showing/hiding an image
 */
UCLASS()
class USK_API UCollectableItemIcon : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * @brief The Icon displayed if the item is collected
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* Icon;

	/**
	 * @brief The required value before the item is considered collected
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	float RequiredValue;

	/**
	 * @brief Update the collected state (and visibility) of the icon
	 * @param IsCollected Is the item collected?
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void UpdateState(bool IsCollected) const;

	/**
	 * @brief Update the value of the item and adjust the collected state if necessary
	 * @param Value The current value of the item
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void UpdateValue(float Value) const;

	/**
	 * @brief Monitor the trackable data and automatically update the icon state whenever the value changes
	 * @param TrackableDataComponent A reference to the TrackableDataComponent
	 * @param DataName The name of the data item to monitor
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void MonitorTrackableValue(UTrackableDataComponent* TrackableDataComponent, FName DataName);

protected:
	/**
	 * @brief Overridable native event for when the widget has been constructed
	 */
	virtual void NativeConstruct() override;

private:
	/**
	 * @brief The name of the data item to monitor
	 */
	FName TrackableDataName;

	/**
	 * @brief Update the icon state after the trackable data is updated
	 * @param Name The name of the data item
	 * @param Value The current value of the data item
	 * @param ValuePercentage The percentage of the current value compared to the max value of the data item
	 */
	UFUNCTION()
	void OnTrackableValueChanged(FName Name, float Value, float ValuePercentage);
};