// Created by Henry Jooste

#include "FpsCounter.h"

#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "USK/Core/USKGameInstance.h"
#include "USK/Logger/Log.h"
#include "USK/Settings/SettingsUtils.h"

/**
 * @brief Overridable native event for when the widget has been constructed
 */
void UFpsCounter::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateVisibility(false);
	LoadSettings();
}

/**
 * @brief Update the visibility of the widget
 * @param IsVisible Is the widget visible?
 */
void UFpsCounter::UpdateVisibility(bool IsVisible)
{
	const bool WasHidden = GetVisibility() == ESlateVisibility::Collapsed ||
		GetVisibility() == ESlateVisibility::Hidden; 
	USK_LOG_INFO(*FString::Format(TEXT("Updating visibility to {0}"), { IsVisible }));
	SetVisibility(IsVisible ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);

	if (WasHidden && IsVisible)
	{
		UpdateFramerateAfterDelay();
	}
}

/**
 * @brief Load and apply the FPS counter settings
 */
void UFpsCounter::LoadSettings()
{
	const USettingsData* Settings = USettingsUtils::LoadSettings();
	if (!IsValid(Settings))
	{
		return;
	}

	if (Settings->GraphicsFpsIndicatorTypeModified)
	{
		UpdateWidgetType(Settings->GraphicsFpsIndicatorType);
		return;
	}
	
	UGameInstance* CurrentGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	const UUSKGameInstance* GameInstance = dynamic_cast<UUSKGameInstance*>(CurrentGameInstance);
	if (GameInstance == nullptr)
	{
		USK_LOG_ERROR("Unable to initialize visibility. GameInstance is not UUSKGameInstance");	
		return;
	}

	if (GameInstance->SettingsConfig == nullptr)
	{
		USK_LOG_ERROR("Unable to initialize visibility. SettingsConfig is nullptr");
		return;
	}

	UpdateWidgetType(GameInstance->SettingsConfig->GraphicsFpsIndicatorTypeDefault);
}

/**
 * @brief Update the framerate after a delay
 */
void UFpsCounter::UpdateFramerateAfterDelay()
{
	if (GetVisibility() == ESlateVisibility::Collapsed || GetVisibility() == ESlateVisibility::Hidden)
	{
		return;
	}

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
	UKismetSystemLibrary::RetriggerableDelay(GetWorld(),
		UpdateDelay * UGameplayStatics::GetGlobalTimeDilation(GetWorld()), LatentAction);
}

/**
 * @brief Update the framerate
 */
void UFpsCounter::UpdateFramerate()
{
	const float DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	const float TimeDilation = UGameplayStatics::GetGlobalTimeDilation(GetWorld());
	const float Framerate = FMath::RoundToInt(1.0f / DeltaSeconds * TimeDilation);
	if (Framerate <= 0)
	{
		return;
	}

	FpsValues.Add(Framerate);
	if (FpsValues.Num() > MeasureTime / UpdateDelay)
	{
		FpsValues.RemoveAt(0);
		MinFps = INT_MAX;
		MaxFps = INT_MIN;
	}

	int TotalFps = 0;
	for (const int FpsValue : FpsValues)
	{
		TotalFps += FpsValue;
		MinFps = FMath::Min(MinFps, FpsValue);
		MaxFps = FMath::Max(MaxFps, FpsValue);
	}	
	
	const int AverageFps = FMath::RoundToInt(static_cast<double>(TotalFps) / FpsValues.Num());
	UpdateFramerateText(FramerateSimpleText, Framerate);
	UpdateFramerateText(FramerateText, Framerate);
	UpdateFramerateText(MinText, MinFps);
	UpdateFramerateText(MaxText, MaxFps);
	UpdateFramerateText(AverageText, AverageFps);
	UpdateFramerateAfterDelay();
}

/**
 * @brief Update the framerate text
 * @param TextBlock The text block to update
 * @param Value The framerate value to display
 */
void UFpsCounter::UpdateFramerateText(UTextBlock* TextBlock, const int Value) const
{
	TextBlock->SetText(FText::FromString(FString::FromInt(Value)));

	if (Value >= HighFramerate)
	{
		TextBlock->SetColorAndOpacity(HighColor);
		return;
	}

	if (Value >= MediumFramerate)
	{
		TextBlock->SetColorAndOpacity(MediumColor);
		return;
	}

	TextBlock->SetColorAndOpacity(LowColor);
}

/**
 * @brief Update the framerate widget type
 * @param Type The type of framerate widget to display
 */
void UFpsCounter::UpdateWidgetType(const ESettingsFpsCounterType Type)
{	
	SimpleViewContainer->SetVisibility(Type == ESettingsFpsCounterType::Simple
		? ESlateVisibility::HitTestInvisible
		: ESlateVisibility::Collapsed);
	DetailedViewContainer->SetVisibility(Type == ESettingsFpsCounterType::Detailed
		? ESlateVisibility::HitTestInvisible
		: ESlateVisibility::Collapsed);
	UpdateVisibility(Type != ESettingsFpsCounterType::Disabled);	
}