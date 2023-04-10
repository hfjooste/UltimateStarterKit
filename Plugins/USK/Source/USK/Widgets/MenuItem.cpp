// Created by Henry Jooste

#include "MenuItem.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "USK/Audio/AudioUtils.h"
#include "USK/Logger/Log.h"
#include "USK/Utils/PlatformUtils.h"

/**
 * @brief Overridable native event for when the widget has been constructed in the editor
 */
void UMenuItem::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetText(MenuItemText);
	if (Title != nullptr)
	{
		Title->SetText(TitleText);
		Title->SetVisibility(TitleText.IsEmpty() ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);	
	}
}

/**
 * @brief Overridable native event for when the widget has been constructed
 */
void UMenuItem::NativeConstruct()
{
	Super::NativeConstruct();

	USK_LOG_TRACE("Setting default value");
	CurrentValue = FMath::Clamp(DefaultValue, MinValue, MaxValue);
	UpdateValueText();
	
	if (!HideOnConsoles || !UPlatformUtils::IsConsole())
	{
		return;
	}

	USK_LOG_INFO("Hiding menu item on console");
	SetVisibility(ESlateVisibility::Collapsed);
}

/**
 * @brief Set the text display in the menu item
 * @param Text The new text displayed in the menu item
 */
void UMenuItem::SetText(const FText& Text) const
{
	USK_LOG_INFO("Setting menu item text");
	if (NormalText != nullptr)
	{
		USK_LOG_TRACE("Setting normal text");
		NormalText->SetText(Text);	
	}
	
	if (HighlightedText != nullptr)
	{
		USK_LOG_TRACE("Setting highlighted text");
		HighlightedText->SetText(Text);
	}
}

/**
 * @brief Set the highlighted state of the menu item
 * @param IsHighlighted Is the menu item highlighted?
 * @param PlayHighlightedSound Should the highlighted sound effect be played?
 */
void UMenuItem::SetHighlightedState(const bool IsHighlighted, const bool PlayHighlightedSound)
{
	USK_LOG_TRACE("Setting highlighted state");
	const FLinearColor BorderColor = IsHighlighted ? BorderHighlightedColor : BorderNormalColor;
	const FLinearColor BackgroundColor = IsHighlighted ? BackgroundHighlightedColor : BackgroundNormalColor;

	if (NormalText != nullptr)
	{
		NormalText->SetVisibility(IsHighlighted ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);	
	}
	
	if (HighlightedText != nullptr)
	{
		USK_LOG_TRACE("Updating highlighted text");
		HighlightedText->SetVisibility(IsHighlighted ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);	
	}

	if (ValueText != nullptr)
	{
		USK_LOG_TRACE("Updating value text");
		ValueText->SetVisibility(IsHighlighted ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
	}

	if (HighlightedValueText != nullptr)
	{
		USK_LOG_TRACE("Updating highlighted value text");
		HighlightedValueText->SetVisibility(IsHighlighted ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}

	if (BorderLeft != nullptr)
	{
		USK_LOG_TRACE("Updating left border");
		BorderLeft->SetBrushFromTexture(IsHighlighted ? BorderLeftHighlightedImage : BorderLeftNormalImage);
		BorderLeft->SetColorAndOpacity(BorderColor);
	}
	
	if (BorderRight != nullptr)
	{
		USK_LOG_TRACE("Updating right border");
		BorderRight->SetBrushFromTexture(IsHighlighted ? BorderRightHighlightedImage : BorderRightNormalImage);
		BorderRight->SetColorAndOpacity(BorderColor);
	}

	if (BorderBackground != nullptr)
	{
		USK_LOG_TRACE("Updating border background");
		BorderBackground->SetBrushFromTexture(IsHighlighted ? BorderHighlightedImage : BorderNormalImage);
		BorderBackground->SetColorAndOpacity(BorderColor);
	}

	if (ButtonLeft != nullptr)
	{
		USK_LOG_TRACE("Updating left button");
		ButtonLeft->SetBrushFromTexture(IsHighlighted ? BackgroundLeftHighlightedImage : BackgroundLeftNormalImage);
		ButtonLeft->SetColorAndOpacity(BackgroundColor);
	}

	if (ButtonRight != nullptr)
	{
		USK_LOG_TRACE("Updating right button");
		ButtonRight->SetBrushFromTexture(IsHighlighted ? BackgroundRightHighlightedImage : BackgroundRightNormalImage);
		ButtonRight->SetColorAndOpacity(BackgroundColor);
	}
	
	if (ButtonBackground != nullptr)
	{
		USK_LOG_TRACE("Updating button background");
		ButtonBackground->SetBrushFromTexture(IsHighlighted ? BackgroundHighlightedImage : BackgroundNormalImage);
		ButtonBackground->SetColorAndOpacity(BackgroundColor);
	}
	
	if (IsHighlighted && HighlightedAnimation != nullptr)
	{
		USK_LOG_TRACE("Playing highlighted animation");
		PlayAnimation(HighlightedAnimation);
	}

	if (IsHighlighted && PlayHighlightedSound)
	{
		USK_LOG_TRACE("Playing highlighted sound effect");
		UAudioUtils::PlaySound2D(GetWorld(), HighlightedSFX);
	}
}

/**
 * @brief Get the current value of the menu item
 * @return The current value of the menu item
 */
int UMenuItem::GetValue() const
{
	return FMath::RoundToInt(CurrentValue);
}

/**
 * @brief Update the value of the menu item
 * @param Increment The amount added to the current value of the menu item 
 */
void UMenuItem::UpdateValue(const float Increment)
{
	USK_LOG_TRACE("Updating menu item value");
	CurrentValue = FMath::Clamp(CurrentValue + Increment,
		static_cast<float>(MinValue), static_cast<float>(MaxValue));
	UpdateValueText();

	USK_LOG_TRACE("Menu item value updated. Notifying other classes");
	OnValueChanged.Broadcast(CurrentValue);	
}

/**
 * @brief Update the value text of the menu item 
 */
void UMenuItem::UpdateValueText() const
{
	if (HorizontalNavigation != EMenuNavigation::IncreaseDecreaseValue &&
		VerticalNavigation != EMenuNavigation::IncreaseDecreaseValue)
	{
		if (ValueText != nullptr)
		{
			ValueText->SetText(FText::GetEmpty());
		}

		if (HighlightedValueText != nullptr)
		{
			HighlightedValueText->SetText(FText::GetEmpty());
		}
		
		return;
	}
	
	const FText Text = ValueMapping.Contains(GetValue())
		? ValueMapping[CurrentValue]
		: FText::FromString(FString::FromInt(GetValue()));

	if (ValueText != nullptr)
	{
		ValueText->SetText(Text);
	}

	if (HighlightedValueText != nullptr)
	{
		HighlightedValueText->SetText(Text);
	}
}