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
 * @brief Update the visibility of the widget
 * @param IsVisible Is the widget visible?
 */
void UFpsCounter::UpdateVisibility(bool IsVisible)
{
	const bool WasHidden = GetVisibility() == ESlateVisibility::Collapsed ||
		GetVisibility() == ESlateVisibility::Hidden; 
	USK_LOG_INFO(*FString::Format(TEXT("Updating visibility to {0}"), { IsVisible }));
	SetVisibility(IsVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);

	if (WasHidden && IsVisible)
	{
		UpdateFramerateAfterDelay();
	}
}

/**
 * @brief Overridable native event for when the widget has been constructed
 */
void UFpsCounter::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeVisibility();
	UpdateFramerateAfterDelay();
}

/**
 * @brief Initialize the visibility of the widget by checking the settings
 */
void UFpsCounter::InitializeVisibility()
{
	const USettingsData* Settings = USettingsUtils::LoadSettings();
	if (Settings->GraphicsFpsIndicatorModified)
	{
		UpdateVisibility(Settings->GraphicsFpsIndicator);
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

	UpdateVisibility(GameInstance->SettingsConfig->GraphicsFpsIndicatorDefault);
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
