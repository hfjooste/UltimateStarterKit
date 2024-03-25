// Created by Henry Jooste

#pragma once

#include "TrackableDataComponent.h"
#include "CurrencyComponent.generated.h"

/**
 * @brief Actor component responsible for tracking different currencies
 */
UCLASS(ClassGroup=("UltimateStarterKit"), DisplayName="Currency Component", meta=(BlueprintSpawnableComponent))
class USK_API UCurrencyComponent : public UTrackableDataComponent
{
	GENERATED_BODY()
};