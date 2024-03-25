// Created by Henry Jooste

#include "CreditsWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "USK/Logger/Log.h"

/**
 * @brief Overridable native event for when the widget has been constructed
 */
void UCreditsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	Text->SetText(FText::GetEmpty());	
	if (Title != nullptr)
	{
		Title->SetText(FText::GetEmpty());
	}
	
	if (AutoStart)
	{
		Start();
	}
}

/**
 * @brief Start showing the credits
 */
void UCreditsWidget::Start()
{
	if (Credits.Num() <= 0)
	{
		USK_LOG_ERROR("Unable to show credits. No entries specified");
		return;
	}

	FLatentActionInfo LatentAction;
	LatentAction.Linkage = 0;
	LatentAction.CallbackTarget = this;
	LatentAction.UUID = GetUniqueID();
	LatentAction.ExecutionFunction = "ShowNextEntry";
	UKismetSystemLibrary::Delay(GetWorld(), StartDelay, LatentAction);
}

/**
 * @brief Show the next credits entry
 */
void UCreditsWidget::ShowNextEntry()
{
	EntryIndex++;
	if (EntryIndex >= Credits.Num())
	{
		USK_LOG_INFO("Credits finished");
		if (RemoveOnCompletion)
		{
			RemoveFromParent();
		}

		OnCreditsFinished.Broadcast();
		return;
	}

	UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Container);
	if (CanvasPanelSlot == nullptr)
	{
		USK_LOG_ERROR("Unable to show credits. CanvasPanelSlot is nullptr");
		return;
	}

	OnCreditsNextEntryStarted.Broadcast(EntryIndex);
	const FCreditsEntry CurrentEntry = Credits[EntryIndex]; 
	Text->SetText(CurrentEntry.Text);
	
	if (Title != nullptr)
	{
		Title->SetText(CurrentEntry.Title);
	}

	CanvasPanelSlot->SetAutoSize(true);
	CanvasPanelSlot->SetAnchors(FAnchors(GetHorizontalAnchor(CurrentEntry.HorizontalAlignment),
		GetVerticalAnchor(CurrentEntry.VerticalAlignment)));
	CanvasPanelSlot->SetAlignment(FVector2D(GetHorizontalAnchor(CurrentEntry.HorizontalAlignment),
		GetVerticalAnchor(CurrentEntry.VerticalAlignment)));
	CanvasPanelSlot->SetPosition(FVector2D::ZeroVector);

	if (ShowAnimation != nullptr)
	{
		PlayAnimation(ShowAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
	}

	FLatentActionInfo LatentAction;
	LatentAction.Linkage = 0;
	LatentAction.CallbackTarget = this;
	LatentAction.UUID = GetUniqueID();
	LatentAction.ExecutionFunction = "FinishCurrentEntry";
	UKismetSystemLibrary::Delay(GetWorld(), CurrentEntry.Duration, LatentAction);
}

/**
 * @brief Finish showing the current credits entry
 */
void UCreditsWidget::FinishCurrentEntry()
{
	if (HideAnimation != nullptr)
	{
		PlayAnimation(HideAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
	}

	FLatentActionInfo LatentAction;
	LatentAction.Linkage = 0;
	LatentAction.CallbackTarget = this;
	LatentAction.UUID = GetUniqueID();
	LatentAction.ExecutionFunction = "ShowNextEntry";
	UKismetSystemLibrary::Delay(GetWorld(), DelayBetweenEntries, LatentAction);
}

/**
 * @brief Get the horizontal anchor for the given alignment
 * @param HorizontalAlignment The horizontal alignment
 * @return The horizontal anchor for the given alignment
 */
float UCreditsWidget::GetHorizontalAnchor(const EHorizontalAlignment HorizontalAlignment)
{
	if (HorizontalAlignment == HAlign_Center || HorizontalAlignment == HAlign_Fill)
	{
		return 0.5f;
	}

	return HorizontalAlignment == HAlign_Left ? 0.0f : 1.0f;
}

/**
 * @brief Get the vertical anchor for the given alignment
 * @param VerticalAlignment The vertical alignment
 * @return The vertical anchor for the given alignment
 */
float UCreditsWidget::GetVerticalAnchor(EVerticalAlignment VerticalAlignment)
{
	if (VerticalAlignment == VAlign_Center || VerticalAlignment == VAlign_Fill)
	{
		return 0.5f;
	}

	return VerticalAlignment == VAlign_Top ? 0.0f : 1.0f;
}