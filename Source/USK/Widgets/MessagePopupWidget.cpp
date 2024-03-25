// Created by Henry Jooste

#include "MessagePopupWidget.h"

#include "Menu.h"
#include "MenuItem.h"
#include "Animation/WidgetAnimation.h"
#include "Components/PanelWidget.h"
#include "TimerManager.h"
#include "USK/Logger/Log.h"

/**
 * @brief Show the message popup
 * @param Data The data used to display the popup
 */
void UMessagePopupWidget::Show(const FMessagePopupData Data)
{
	TitleText->SetText(Data.Title);
	TitleText->SetVisibility(Data.Title.IsEmpty() ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
	MessageText->SetText(Data.Message);

	if (Data.bShowPositiveButton)
	{
		PositiveButton = CreateButton(Data.PositiveButtonText);
	}

	if (Data.bShowNegativeButton)
	{
		NegativeButton = CreateButton(Data.NegativeButtonText);
	}

	if (Data.bShowNeutralButton)
	{
		NeutralButton = CreateButton(Data.NeutralButtonText);
	}

	UpdateButtonNavigation();
	AddToViewport();
	
	if (IsValid(ShowAnimation))
	{
		PlayAnimation(ShowAnimation);
	}

	OnShown.Broadcast();
	USK_LOG_TRACE("Message popup shown");
}

/**
 * @brief Hide the message popup
 */
void UMessagePopupWidget::Hide()
{
	OnHidden.Broadcast();
	if (!IsValid(HideAnimation))
	{
		RemoveWidget();
		return;
	}

	PlayAnimation(HideAnimation);

	FTimerHandle HideWidgetTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(HideWidgetTimerHandle, [this]
	{
		RemoveWidget();
	}, HideAnimation->GetEndTime(), false);
}

/**
 * @brief Remove the popup widget
 */
void UMessagePopupWidget::RemoveWidget()
{
	if (IsValid(PositiveButton))
	{
		PositiveButton->OnSelected.RemoveAll(this);
		PositiveButton->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (IsValid(NegativeButton))
	{
		NegativeButton->OnSelected.RemoveAll(this);
		NegativeButton->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (IsValid(NeutralButton))
	{
		NeutralButton->OnSelected.RemoveAll(this);
		NeutralButton->SetVisibility(ESlateVisibility::Collapsed);
	}

	ButtonMenu->Container->ClearChildren();
	ButtonMenu->SetVisibility(ESlateVisibility::Collapsed);
	RemoveFromParent();
	USK_LOG_TRACE("Message popup removed");
}

/**
 * @brief Create a button menu item
 * @param ButtonText The text displayed on the button
 * @return A reference to the new button menu item
 */
UMenuItem* UMessagePopupWidget::CreateButton(const FText& ButtonText) const
{
	UMenuItem* MenuItem = CreateWidget<UMenuItem>(GetWorld(), ButtonMenuItemClass);
	if (!IsValid(MenuItem))
	{
		return nullptr;
	}

	MenuItem->HorizontalNavigation = EMenuNavigation::HighlightItem;
	MenuItem->VerticalNavigation = EMenuNavigation::Disabled;
	MenuItem->MenuItemText = ButtonText;
	MenuItem->SetText(ButtonText);
	ButtonMenu->AddMenuItem(MenuItem);
	return MenuItem;
}

/**
 * @brief Update the navigation of all the buttons
 */
void UMessagePopupWidget::UpdateButtonNavigation()
{
	if (IsValid(PositiveButton))
	{
		PositiveButton->MenuItemLeft = nullptr;
		PositiveButton->MenuItemRight = IsValid(NegativeButton) ? NegativeButton : NeutralButton;
		PositiveButton->OnSelected.AddDynamic(this, &UMessagePopupWidget::OnPositiveButtonClicked);
	}

	if (IsValid(NegativeButton))
	{
		NegativeButton->MenuItemLeft = PositiveButton;
		NegativeButton->MenuItemRight = NeutralButton;
		NegativeButton->OnSelected.AddDynamic(this, &UMessagePopupWidget::OnNegativeButtonClicked);
	}

	if (IsValid(NeutralButton))
	{
		NeutralButton->MenuItemLeft = IsValid(NegativeButton) ? NegativeButton : PositiveButton;
		NeutralButton->MenuItemRight = nullptr;
		NeutralButton->OnSelected.AddDynamic(this, &UMessagePopupWidget::OnNeutralButtonClicked);
	}
}

/**
 * @brief Called when the positive button is clicked
 */
void UMessagePopupWidget::OnPositiveButtonClicked()
{
	USK_LOG_TRACE("Message popup positive button selected");
	OnPositiveButtonSelected.Broadcast();
	Hide();
}

/**
 * @brief Called when the negative button is clicked
 */
void UMessagePopupWidget::OnNegativeButtonClicked()
{
	USK_LOG_TRACE("Message popup negative button selected");
	OnNegativeButtonSelected.Broadcast();
	Hide();
}

/**
 * @brief Called when the neutral button is clicked
 */
void UMessagePopupWidget::OnNeutralButtonClicked()
{
	USK_LOG_TRACE("Message popup neutral button selected");
	OnNeutralButtonSelected.Broadcast();
	Hide();
}