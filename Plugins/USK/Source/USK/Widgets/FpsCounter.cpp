// Created by Henry Jooste

#include "FpsCounter.h"

#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

/**
 * @brief Overridable native event for when the widget has been constructed
 */
void UFpsCounter::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateFramerateAfterDelay();
}

/**
 * @brief Update the framerate after a delay
 */
void UFpsCounter::UpdateFramerateAfterDelay()
{
	if (UpdateDelay <= 0.0f)
	{
		UpdateDelay = 0.0001f;
		return;
	}
	
	FLatentActionInfo LatentAction;
	LatentAction.Linkage = 0;
	LatentAction.CallbackTarget = this;
	LatentAction.UUID = GetUniqueID();
	LatentAction.ExecutionFunction = "UpdateFramerate";
	UKismetSystemLibrary::RetriggerableDelay(GetWorld(), UpdateDelay, LatentAction);
}

/**
 * @brief Update the framerate
 */
void UFpsCounter::UpdateFramerate()
{
	const float DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	const float Framerate = FMath::RoundToInt(1.0f / DeltaSeconds);
	FramerateText->SetText(FText::FromString(FString::FromInt(Framerate)));

	if (Framerate >= HighFramerate)
	{
		FramerateText->SetColorAndOpacity(HighColor);
	}
	else if (Framerate >= MediumFramerate)
	{
		FramerateText->SetColorAndOpacity(MediumColor);
	}
	else
	{
		FramerateText->SetColorAndOpacity(LowColor);	
	}

	UpdateFramerateAfterDelay();
}
