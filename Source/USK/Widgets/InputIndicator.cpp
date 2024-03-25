// Created by Henry Jooste

#include "InputIndicator.h"

#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "USK/Logger/Log.h"

/**
 * @brief Overridable native event for when the widget has been constructed
 */
void UInputIndicator::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = dynamic_cast<UUSKGameInstance*>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance == nullptr)
	{
		USK_LOG_ERROR("Input indicators require the USKGameInstance");
		return;
	}

	GameInstance->OnInputDeviceUpdated.AddDynamic(this, &UInputIndicator::UpdateIcon);
	UpdateIcon();
}

/**
 * @brief Update the input action displayed by the widget
 * @param NewAction The new action
 * @param NewAmount The new amount of images to display
 */
void UInputIndicator::UpdateAction(UInputAction* NewAction, const int NewAmount)
{
	if (GameInstance == nullptr)
	{
		USK_LOG_ERROR("Input indicators require the USKGameInstance");
		return;
	}

	USK_LOG_TRACE("Updating input action");
	Action = NewAction;
	Amount = NewAmount;
	UpdateIcon();
}

/**
 * @brief Update the icon displayed in the widget
 */
void UInputIndicator::UpdateIcon()
{
	USK_LOG_INFO("Updating icon");
	Container->ClearChildren();

	TArray<UTexture2D*> InputIndicators = GameInstance->GetInputIndicatorIcon(Action, Amount);
	for (UTexture2D* InputIndicator : InputIndicators)
	{
		AddIconImage(InputIndicator);
	}
}

/**
 * @brief Add a new icon to the container
 * @param Icon The icon to add
 */
void UInputIndicator::AddIconImage(UTexture2D* Icon)
{
	USK_LOG_TRACE("Adding input indicator icon");
	UUserWidget* NewWidget = CreateWidget(this, InputIndicatorIconClass);
	UInputIndicatorIcon* InputIndicator = dynamic_cast<UInputIndicatorIcon*>(NewWidget);
	InputIndicator->UpdateIcon(Size, Icon);
	Container->AddChildToHorizontalBox(InputIndicator);
}