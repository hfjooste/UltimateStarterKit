// Created by Henry Jooste

#include "CollectableItemIcon.h"

#include "Components/Image.h"
#include "USK/Data/TrackableDataComponent.h"
#include "USK/Logger/Log.h"

/**
 * @brief Overridable native event for when the widget has been constructed
 */
void UCollectableItemIcon::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateState(false);
}

/**
 * @brief Update the collected state (and visibility) of the icon
 * @param IsCollected Is the item collected?
 */
void UCollectableItemIcon::UpdateState(const bool IsCollected) const
{
	Icon->SetVisibility(IsCollected ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

/**
 * @brief Update the value of the item and adjust the collected state if necessary
 * @param Value The current value of the item
 */
void UCollectableItemIcon::UpdateValue(const float Value) const
{
	UpdateState(Value >= RequiredValue);
}

/**
 * @brief Monitor the trackable data and automatically update the icon state whenever the value changes
 * @param TrackableDataComponent A reference to the TrackableDataComponent
 * @param DataName The name of the data item to monitor
 */
void UCollectableItemIcon::MonitorTrackableValue(UTrackableDataComponent* TrackableDataComponent, FName DataName)
{
	if (TrackableDataComponent == nullptr)
	{
		USK_LOG_ERROR("Unable to monitor trackable value. TrackableDataComponent is nullptr");
		return;
	}

	TrackableDataName = DataName;
	TrackableDataComponent->OnValueUpdated.AddDynamic(this, &UCollectableItemIcon::OnTrackableValueChanged);
	UpdateValue(TrackableDataComponent->GetValue(DataName));
}

/**
 * @brief Update the icon state after the trackable data is updated
 * @param Name The name of the data item
 * @param Value The current value of the data item
 * @param ValuePercentage The percentage of the current value compared to the max value of the data item
 */
void UCollectableItemIcon::OnTrackableValueChanged(const FName Name, const float Value, const float ValuePercentage)
{
	if (Name != TrackableDataName)
	{
		return;
	}

	USK_LOG_INFO("Trackable data updated. Updating icon state");
	UpdateValue(Value);
}