// Created by Henry Jooste

#include "MenuItem.h"

#include "Menu.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/Slider.h"
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

	if (ValueSlider != nullptr)
	{
		ValueSlider->SetVisibility(CanValueChange() && ShowValueSlider
			? ESlateVisibility::Visible
			: ESlateVisibility::Collapsed);
	}

	if (IncreaseValueButton != nullptr)
	{
		IncreaseValueButton->SetVisibility(CanValueChange() && ShowValueButtons
			? ESlateVisibility::Visible
			: ESlateVisibility::Collapsed);
	}

	if (DecreaseValueButton != nullptr)
	{
		DecreaseValueButton->SetVisibility(CanValueChange() && ShowValueButtons
			? ESlateVisibility::Visible
			: ESlateVisibility::Collapsed);
	}
}

/**
 * @brief Overridable native event for when the widget has been constructed
 */
void UMenuItem::NativeConstruct()
{
	Super::NativeConstruct();

	USK_LOG_TRACE("Setting default value");
	UpdateValue(DefaultValue);

	if (SelectButton != nullptr)
	{
		SelectButton->SetVisibility(AllowSelection ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
		SelectButton->IsFocusable = false;
		SelectButton->OnClicked.AddDynamic(this, &UMenuItem::OnSelectButtonClicked);
	}

	if (ValueSlider != nullptr)
	{
		ValueSlider->SetVisibility(CanValueChange() && ShowValueSlider
			? ESlateVisibility::Visible
			: ESlateVisibility::Collapsed);
		ValueSlider->IsFocusable = false;
		ValueSlider->SetMinValue(MinValue);
		ValueSlider->SetMaxValue(MaxValue);
		ValueSlider->SetValue(GetValue());
		ValueSlider->OnValueChanged.AddDynamic(this, &UMenuItem::OnSliderValueChanged);
	}

	if (IncreaseValueButton != nullptr)
	{
		IncreaseValueButton->SetVisibility(CanValueChange() && ShowValueButtons
			? ESlateVisibility::Visible
			: ESlateVisibility::Collapsed);
		IncreaseValueButton->IsFocusable = false;
		IncreaseValueButton->OnClicked.AddDynamic(this, &UMenuItem::OnIncreaseValueButtonClicked);
	}

	if (DecreaseValueButton != nullptr)
	{
		DecreaseValueButton->SetVisibility(CanValueChange() && ShowValueButtons
			? ESlateVisibility::Visible
			: ESlateVisibility::Collapsed);
		DecreaseValueButton->IsFocusable = false;
		DecreaseValueButton->OnClicked.AddDynamic(this, &UMenuItem::OnDecreaseValueButtonClicked);
	}
	
	if (!HideOnConsoles || !UPlatformUtils::IsConsole())
	{
		return;
	}

	USK_LOG_INFO("Hiding menu item on console");
	SetVisibility(ESlateVisibility::Collapsed);
}

/**
 * @brief Overridable native event for when the cursor has entered the widget
 * @param InGeometry The Geometry of the widget receiving the event
 * @param InMouseEvent Information about the input event
 */
void UMenuItem::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	if (Menu != nullptr)
	{
		Menu->RequestHighlight(this);
	}
}

/**
 * @brief Overridable native event for when the cursor has left the widget
 * @param InMouseEvent Information about the input event
 */
void UMenuItem::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	if (Menu != nullptr)
	{
		Menu->RemoveHighlight(this);
	}
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
 * @param PlayHighlightedAnimation Should the highlighted animation be played?
 * @param PlayHighlightedSound Should the highlighted sound effect be played?
 */
void UMenuItem::SetHighlightedState(const bool IsHighlighted,
	const bool PlayHighlightedAnimation, const bool PlayHighlightedSound)
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
	
	if (IsHighlighted && HighlightedAnimation != nullptr && PlayHighlightedAnimation)
	{
		USK_LOG_TRACE("Playing highlighted animation");
		PlayAnimation(HighlightedAnimation);
	}

	if (IsHighlighted && PlayHighlightedSound)
	{
		USK_LOG_TRACE("Playing highlighted sound effect");
		UAudioUtils::PlaySound2D(GetWorld(), HighlightedSFX);
	}

	if (IsHighlighted)
	{
		USK_LOG_TRACE("Broadcasting OnHighlighted event");
		OnHighlighted.Broadcast();
	}
	else
	{
		USK_LOG_TRACE("Broadcasting OnHighlightRemoved event");
		OnHighlightRemoved.Broadcast();
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

	if (ValueSlider != nullptr)
	{
		ValueSlider->SetVisibility(CanValueChange() && ShowValueSlider
			? ESlateVisibility::Visible
			: ESlateVisibility::Collapsed);
		ValueSlider->SetValue(GetValue());
	}

	USK_LOG_TRACE("Menu item value updated. Notifying other classes");
	OnValueChanged.Broadcast(CurrentValue);
}

/**
 * @brief Update the value text of the menu item 
 */
void UMenuItem::UpdateValueText() const
{
	if (!CanValueChange())
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

/**
 * @brief Can the value of the menu item be changed?
 * @return A boolean value indicating if the value of the menu item can be changed
 */
bool UMenuItem::CanValueChange() const
{
	return HorizontalNavigation == EMenuNavigation::IncreaseDecreaseValue ||
		VerticalNavigation == EMenuNavigation::IncreaseDecreaseValue;
}

/**
 * @brief Called after the value of the slider is manually changed
 * @param Value The new value of the slider
 */
void UMenuItem::OnSliderValueChanged(const float Value)
{
	USK_LOG_TRACE(*FString::Format(TEXT("Value slider updated ({0})"), { FString::SanitizeFloat(Value) }));

	CurrentValue = 0;
	UpdateValue(Value);
}

/**
 * @brief Called after the select button is clicked
 */
void UMenuItem::OnSelectButtonClicked()
{
	if (Menu != nullptr)
	{
		Menu->OnMenuSelected();
		return;
	}

	OnSelected.Broadcast();
}

/**
 * @brief Called after the increase value button is clicked
 */
void UMenuItem::OnIncreaseValueButtonClicked()
{
	UpdateValue(IncrementSinglePress);
}

/**
 * @brief Called after the decrease value button is clicked
 */
void UMenuItem::OnDecreaseValueButtonClicked()
{
	UpdateValue(-IncrementSinglePress);
}