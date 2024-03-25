// Created by Henry Jooste

#include "DialogueWidget.h"

#include "DialogueEntry.h"
#include "DialogueTransition.h"
#include "Components/Image.h"
#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "USK/Logger/Log.h"
#include "USK/Widgets/Menu.h"
#include "USK/Widgets/MenuItem.h"

/**
 * @brief Event called every frame, if ticking is enabled
 * @param MyGeometry Represents the position, size, and absolute position of a widget
 * @param InDeltaTime Game time elapsed during last frame modified by the time dilation 
 */
void UDialogueWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (!IsValid(DialogueTitle) || !IsValid(DialogueText))
	{
		USK_LOG_ERROR("Dialogue widget doesn't contain the required widgets");
		return;
	}

	if (CurrentText.IsEmpty())
	{
		DialogueTitle->SetText(FText::GetEmpty());
		DialogueText->SetText(FText::GetEmpty());
		
		if (IsValid(ParticipantPortrait))
		{
			ParticipantPortrait->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (IsValid(ParticipantPortraitBorder))
		{
			ParticipantPortraitBorder->SetVisibility(ESlateVisibility::Collapsed);
		}
		
		UpdateTransitionIndicatorVisibility(ESlateVisibility::Collapsed);		
		return;
	}

	if (TextIndex >= CurrentText.ToString().Len())
	{
		bAddEndTag = false;
		UpdateTransitionIndicatorVisibility(ESlateVisibility::Visible);
		return;
	}

	TextIndex = FMath::Min(TextIndex + (InDeltaTime * UpdateSpeed),
		static_cast<float>(CurrentText.ToString().Len()));
	ProcessRichTextTag();

	FString NewTextString = CurrentText.ToString().Left(TextIndex);
	if (bAddEndTag)
	{
		NewTextString += "</>";
	}
	
	DialogueText->SetText(FText::FromString(NewTextString));
	UpdateTransitionIndicatorVisibility(ESlateVisibility::Collapsed);
}

/**
 * @brief Update the current entry and refresh the UI
 * @param Entry The new dialogue entry
 */
void UDialogueWidget::UpdateEntry(const UDialogueEntry* Entry)
{
	if (!IsValid(DialogueTitle) || !IsValid(DialogueText))
	{
		USK_LOG_ERROR("Dialogue widget doesn't contain the required widgets");
		return;
	}

	if (!IsValid(Entry))
	{
		USK_LOG_ERROR("Trying to update dialogue widget with invalid entry");
		return;
	}

	const FText Title = IsValid(Entry->Owner) ? Entry->Owner->Name : FText::GetEmpty();
	const FLinearColor Color = IsValid(Entry->Owner) ? Entry->Owner->Color : FLinearColor::Transparent;
	
	TextIndex = 0;
	CurrentText = Entry->Text;
	UpdateSpeed = FMath::Max(Entry->Speed, 0.001f);
	CurrentTransitionType = Entry->Transition;
	
	DialogueTitle->SetColorAndOpacity(Color);
	DialogueTitle->SetText(Title);
	DialogueText->SetText(FText::GetEmpty());

	CurrentRichTextStyle = Entry->bOverrideRichTextStyle ? Entry->RichTextStyle : RichTextStyle;
	DialogueText->SetTextStyleSet(CurrentRichTextStyle);

	UTexture2D* Image = Entry->bOverridePortraitImage
		? Entry->CustomPortraitImage
		: (IsValid(Entry->Owner) ? Entry->Owner->PortraitImage : nullptr);
	
	if (IsValid(ParticipantPortrait))
	{		
		ParticipantPortrait->SetBrushFromTexture(Image);
		ParticipantPortrait->SetVisibility(Image != nullptr
			? ESlateVisibility::SelfHitTestInvisible
			: ESlateVisibility::Collapsed);
	}

	if (IsValid(ParticipantPortraitBorder))
	{
		const FSlateColor BorderColor = Entry->bOverridePortraitImage
			? Entry->CustomPortraitBorderColor
			: (IsValid(Entry->Owner) && Entry->Owner->bCustomPortraitImageBorderColor
				? Entry->Owner->PortraitImageBorderColor
				: FSlateColor(Color));
		ParticipantPortraitBorder->SetBrushTintColor(BorderColor);
		ParticipantPortraitBorder->SetVisibility(Image != nullptr
			? ESlateVisibility::SelfHitTestInvisible
			: ESlateVisibility::Collapsed);
	}
	
	InitializeMenuItems(Entry);
}

/**
 * @brief Skip the current entry
 * @return A boolean value indicating if the entry was skipped
 */
bool UDialogueWidget::SkipEntry()
{
	if (CurrentText.IsEmpty() || TextIndex >= CurrentText.ToString().Len())
	{
		return false;
	}

	TextIndex = CurrentText.ToString().Len();
	DialogueText->SetText(CurrentText);
	UpdateTransitionIndicatorVisibility(ESlateVisibility::Visible);	
	return true;
}

/**
 * @brief Initialize the choice menu items for the dialogue entry
 * @param Entry The dialogue entry containing the choice data
 */
void UDialogueWidget::InitializeMenuItems(const UDialogueEntry* Entry)
{
	for (UMenuItem* ChoiceMenuItem : ChoiceMenuItems)
	{
		ChoiceMenuItem->OnSelectedInContainer.RemoveAll(this);
		ChoiceMenuItem->HorizontalNavigation = EMenuNavigation::Disabled;
		ChoiceMenuItem->VerticalNavigation = EMenuNavigation::Disabled;
		ChoiceMenuItem->AllowSelection = false;
		ChoiceMenuItem->RemoveFromParent();
	}

	ChoiceMenuItems.Empty();
	
	if (Entry->Transition == EDialogueTransitionType::Choice && !Entry->IsLeafNode())
	{
		if (!IsValid(ChoiceMenuItemClass))
		{
			USK_LOG_ERROR("Choice Menu Item Class is not valid");
			return;
		}
		
		for (const TTuple<UDialogueEntry*, UDialogueTransition*> Item : Entry->Edges)
		{
			UMenuItem* NewMenuItem = CreateWidget<UMenuItem>(GetWorld(), ChoiceMenuItemClass);
			if (!IsValid(NewMenuItem))
			{
				USK_LOG_ERROR("Failed to create choice menu item widget");
				return;
			}

			NewMenuItem->MenuItemText = Item.Value->Text;
			NewMenuItem->SetText(NewMenuItem->MenuItemText);
			ChoiceMenuItems.Add(NewMenuItem);
		}

		for (int Index = 0; Index < ChoiceMenuItems.Num(); Index++)
		{
			UMenuItem* ChoiceMenuItem = ChoiceMenuItems[Index];
			ChoiceMenuItem->HorizontalNavigation = EMenuNavigation::Disabled;
			ChoiceMenuItem->VerticalNavigation = EMenuNavigation::HighlightItem;
			ChoiceMenuItem->MenuItemLeft = nullptr;
			ChoiceMenuItem->MenuItemRight = nullptr;
			ChoiceMenuItem->MenuItemUp = Index == 0 ? ChoiceMenuItems[ChoiceMenuItems.Num() - 1] : ChoiceMenuItems[Index - 1];
			ChoiceMenuItem->MenuItemDown = Index == ChoiceMenuItems.Num() - 1 ? ChoiceMenuItems[0] : ChoiceMenuItems[Index + 1];
			ChoiceMenuItem->OnSelectedInContainer.AddDynamic(this, &UDialogueWidget::NotifyChoiceSelected);
			ChoiceMenu->AddMenuItem(ChoiceMenuItem);
		}

		ChoiceMenuItems[0]->SetHighlightedState(true, false, false);
	}
}

/**
 * @brief Notify other classes that a choice was selected
 * @param Index The index of the choice that was selected
 */
void UDialogueWidget::NotifyChoiceSelected(int Index)
{
	OnChoiceSelected.Broadcast(Index);
}

/**
 * @brief Update the visibility of the transition widget
 * @param NewVisibility The new visibility of the widget
 */
void UDialogueWidget::UpdateTransitionIndicatorVisibility(ESlateVisibility NewVisibility)
{
	switch (CurrentTransitionType)
	{
	case EDialogueTransitionType::Auto:
		if (IsValid(ChoiceMenu))
		{
			ChoiceMenu->SetVisibility(ESlateVisibility::Collapsed);
		}
		if (IsValid(SkipEntryImage))
		{
			SkipEntryImage->SetVisibility(NewVisibility);
		}
		break;
	case EDialogueTransitionType::Choice:
		if (IsValid(ChoiceMenu))
		{
			if (ChoiceMenu->GetVisibility() != NewVisibility && NewVisibility == ESlateVisibility::Visible)
			{
				ChoiceMenu->RequestHighlight(ChoiceMenuItems[0]);	
			}			
			ChoiceMenu->SetVisibility(NewVisibility);
		}
		if (IsValid(SkipEntryImage))
		{
			SkipEntryImage->SetVisibility(ESlateVisibility::Collapsed);
		}
		break;
	default:
		USK_LOG_ERROR("Invalid dialogue transition type");
		break;
	}
}

/**
 * @brief Process the rich text tags in the current text
 */
void UDialogueWidget::ProcessRichTextTag()
{
	const FString CurrentString = CurrentText.ToString();
	const int TextIndexInt = FMath::RoundToInt(TextIndex);
	
	if (TextIndexInt >= CurrentString.Len() || CurrentString[TextIndexInt] != '<')
	{
		return;
	}

	const int EndTagIndex = CurrentText.ToString().Find(">",
		ESearchCase::IgnoreCase, ESearchDir::FromStart, TextIndexInt);
    if (EndTagIndex <= TextIndexInt || !IsValid(CurrentRichTextStyle))
    {
    	return;						
    }

	const FString Tag = CurrentText.ToString().Mid(TextIndexInt + 1, EndTagIndex - TextIndexInt - 1);
	if (Tag == "/")
	{
		bAddEndTag = false;
		TextIndex = EndTagIndex + 1;
		return;
	}

	const FRichTextStyleRow* RichTextStyleRow = CurrentRichTextStyle->FindRow<FRichTextStyleRow>(
		FName(Tag), TEXT(""), true);
	if (RichTextStyleRow == nullptr)
	{
		return;
	}

	bAddEndTag = true;
	TextIndex = EndTagIndex + 1;
}