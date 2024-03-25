// Created by Henry Jooste

#pragma once

#include "TrackableDataComponent.h"
#include "StatsComponent.generated.h"

/**
 * @brief Actor Component responsible for tracking different character stats
 */
UCLASS(ClassGroup=("UltimateStarterKit"), DisplayName="Stats Component", meta=(BlueprintSpawnableComponent))
class USK_API UStatsComponent : public UTrackableDataComponent
{
	GENERATED_BODY()
};