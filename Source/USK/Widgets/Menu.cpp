// Created by Henry Jooste

#include "Menu.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Pawn.h"
#include "Components/PanelWidget.h"
#include "Components/ScrollBox.h"
#include "MenuItem.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "USK/Audio/AudioUtils.h"
#include "USK/Logger/Log.h"
#include "Runtime/Launch/Resources/Version.h"
#include "USK/Core/USKGameInstance.h"

/**
 * @brief Overridable native event for when the widget has been constructed
 */
void UMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	InitializeMenuItems();
	if (CurrentMenuItem != nullptr)
	{
		CurrentMenuItem->SetHighlightedState(true, false, false);
	}

	USK_LOG_TRACE("Adding binding to visibility changed event");
	OnNativeVisibilityChanged.AddUObject(this, &UMenu::OnMenuVisibilityChanged);

	UGameInstance* CurrentGameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	GameInstance = dynamic_cast<UUSKGameInstance*>(CurrentGameInstance);
	if (IsValid(GameInstance))
	{
		GameInstance->OnGamePaused.AddDynamic(this, &UMenu::OnGamePaused);
		GameInstance->OnGameUnpaused.AddDynamic(this, &UMenu::OnGameUnpaused);
	}
}

/**
 * @brief Overridable native event for when the widget has been destroyed
 */
void UMenu::NativeDestruct()
{
	Super::NativeDestruct();
	RemoveInputBindings();
}

/**
 * @brief Overridable native event for when the widget has been initialized
 */
void UMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (AddInputBindingOnLoad)
	{
		AddInputBindings();
	}
}

/**
 * @brief Navigate up or increase the value
 */
void UMenu::OnMenuUp()
{
	if (!IsInputAllowed())
	{
		return;
	}

	USK_LOG_TRACE("Navigating up");
	UpdateHighlightedItemBeforeNavigation(true);
	UpdateHighlightedItem(CurrentMenuItem == nullptr ? nullptr : CurrentMenuItem->MenuItemUp,
		CurrentMenuItem == nullptr ? EMenuNavigation::Disabled : CurrentMenuItem->VerticalNavigation,
		true, false);
}

/**
 * @brief Increase the value while holding the menu up key
 */
void UMenu::OnMenuUpHold()
{
	if (!IsInputAllowed() || CurrentMenuItem == nullptr ||
		CurrentMenuItem->ValueUpdateMethod != EMenuItemValueUpdateMethod::Hold ||
		CurrentMenuItem->VerticalNavigation != EMenuNavigation::IncreaseDecreaseValue)
	{
		return;
	}
	
	USK_LOG_TRACE("Increasing value (hold)");
	UpdateHighlightedItem(nullptr, EMenuNavigation::IncreaseDecreaseValue, true, true);
}

/**
 * @brief Navigate down or decrease the value
 */
void UMenu::OnMenuDown()
{
	if (!IsInputAllowed())
	{
		return;
	}
	
	USK_LOG_TRACE("Navigating down");
	UpdateHighlightedItemBeforeNavigation(true);
	UpdateHighlightedItem(CurrentMenuItem == nullptr ? nullptr : CurrentMenuItem->MenuItemDown,
		CurrentMenuItem == nullptr ? EMenuNavigation::Disabled : CurrentMenuItem->VerticalNavigation,
		false, false);
}

/**
 * @brief Decrease the value while holding the menu down key
 */
void UMenu::OnMenuDownHold()
{
	if (!IsInputAllowed() || CurrentMenuItem == nullptr ||
		CurrentMenuItem->ValueUpdateMethod != EMenuItemValueUpdateMethod::Hold ||
		CurrentMenuItem->VerticalNavigation != EMenuNavigation::IncreaseDecreaseValue)
	{
		return;
	}
	
	USK_LOG_TRACE("Decreasing value (hold)");
	UpdateHighlightedItem(nullptr, EMenuNavigation::IncreaseDecreaseValue, false, true);
}

/**
 * @brief Navigate left or decrease the value
 */
void UMenu::OnMenuLeft()
{
	if (!IsInputAllowed())
	{
		return;
	}
	
	USK_LOG_TRACE("Navigating left");
	UpdateHighlightedItemBeforeNavigation(false);
	UpdateHighlightedItem(CurrentMenuItem == nullptr ? nullptr : CurrentMenuItem->MenuItemLeft,
		CurrentMenuItem == nullptr ? EMenuNavigation::Disabled : CurrentMenuItem->HorizontalNavigation,
		false, false);
}

/**
 * @brief Decrease the value while holding the menu left key
 */
void UMenu::OnMenuLeftHold()
{
	if (!IsInputAllowed() || CurrentMenuItem == nullptr ||
		CurrentMenuItem->ValueUpdateMethod != EMenuItemValueUpdateMethod::Hold ||
		CurrentMenuItem->HorizontalNavigation != EMenuNavigation::IncreaseDecreaseValue)
	{
		return;
	}
	
	USK_LOG_TRACE("Decreasing value (hold)");
	UpdateHighlightedItem(nullptr, EMenuNavigation::IncreaseDecreaseValue, false, true);
}

/**
 * @brief Navigate right or increase the value
 */
void UMenu::OnMenuRight()
{
	if (!IsInputAllowed())
	{
		return;
	}
	
	USK_LOG_TRACE("Navigating right");
	UpdateHighlightedItemBeforeNavigation(false);
	UpdateHighlightedItem(CurrentMenuItem == nullptr ? nullptr : CurrentMenuItem->MenuItemRight,
		CurrentMenuItem == nullptr ? EMenuNavigation::Disabled : CurrentMenuItem->HorizontalNavigation,
		true, false);
}

/**
 * @brief Increase the value while holding the menu right key
 */
void UMenu::OnMenuRightHold()
{
	if (!IsInputAllowed() || CurrentMenuItem == nullptr ||
		CurrentMenuItem->ValueUpdateMethod != EMenuItemValueUpdateMethod::Hold ||
		CurrentMenuItem->HorizontalNavigation != EMenuNavigation::IncreaseDecreaseValue)
	{
		return;
	}
	
	USK_LOG_TRACE("Increasing value (hold)");
	UpdateHighlightedItem(nullptr, EMenuNavigation::IncreaseDecreaseValue, true, true);
}

/**
 * @brief Select the current menu item
 */
void UMenu::OnMenuSelected()
{
	if (!IsInputAllowed())
	{
		return;
	}
	
	USK_LOG_TRACE("Selecting menu item");
	bool ValidSettingsItemType = true;

#if ENGINE_MAJOR_VERSION >= 5
	ValidSettingsItemType = CurrentMenuItem != nullptr &&
		CurrentMenuItem->SettingsItemType != ESettingsItemType::ControlsRemap;
#endif
	
	if (CurrentMenuItem != nullptr && (CurrentMenuItem->AllowSelection || ValidSettingsItemType))
	{
		UAudioUtils::PlaySound2D(GetWorld(), SelectedSFX);
		CurrentMenuItem->SelectItem();
	}
}

/**
 * @brief Go back to a previous menu or close the menu
 */
void UMenu::OnMenuBack()
{
	if (!IsInputAllowed())
	{
		return;
	}

	if (CurrentMenuItem != nullptr && CurrentMenuItem->OnMenuBack())
	{
		return;
	}
	
	USK_LOG_TRACE("Going back");
	UAudioUtils::PlaySound2D(GetWorld(), BackSFX);
	OnBackEvent.Broadcast();
}

/**
 * @brief Request to highlight a specific menu item
 * @param MenuItem The menu item to highlight
 */
void UMenu::RequestHighlight(UMenuItem* MenuItem)
{
	if (CurrentMenuItem == MenuItem)
	{
		USK_LOG_TRACE("Menu item already highlighted");
		return;
	}

	USK_LOG_TRACE("Handling highlight request");
	UpdateHighlightedItem(MenuItem, EMenuNavigation::HighlightItem, false, false);
}

/**
 * @brief Request to remove the highlighted state from a specific menu item
 * @param MenuItem The menu item to remove the highlighted state from
 */
void UMenu::RemoveHighlight(UMenuItem* MenuItem)
{
	if (CurrentMenuItem != MenuItem)
	{
		USK_LOG_TRACE("Menu item not highlighted");
		return;
	}

	USK_LOG_TRACE("Removing highlight from menu item");
	HighlightedMenuItemBeforeRemoval = CurrentMenuItem;
	UpdateHighlightedItem(nullptr, EMenuNavigation::HighlightItem, false, false);
}

/**
 * @brief Add a menu item to the container
 * @param MenuItem The menu item to add
 */
void UMenu::AddMenuItem(UMenuItem* MenuItem)
{
	if (!IsValid(Container))
	{
		USK_LOG_ERROR("Failed to add menu item. Container is not valid");
		return;
	}

	if (!IsValid(MenuItem))
	{
		USK_LOG_ERROR("Failed to add menu item. Menu item is not valid");
		return;
	}

	Container->AddChild(MenuItem);
	MenuItem->Menu = this;
	MenuItem->SetHighlightedState(true, false, false);
	MenuItem->SetHighlightedState(false, false, false);
}

/**
 * @brief Called when the visibility of the menu is changed
 * @param NewVisibility The new visibility of the menu
 */
void UMenu::OnMenuVisibilityChanged(ESlateVisibility NewVisibility)
{
	USK_LOG_TRACE("Visibility changed");
	if (NewVisibility == ESlateVisibility::Visible)
	{
		AddInputBindings();
		return;
	}

	RemoveInputBindings();
}

/**
 * @brief Add the input bindings for the menu
 */
void UMenu::AddInputBindings()
{	
	if (PauseGameWhileVisible)
	{
		USK_LOG_INFO("Pausing game");
		if (IsValid(GameInstance))
		{
			GameInstance->PauseGame();
		}
		else
		{
			UGameplayStatics::SetGamePaused(GetWorld(), true);
		}		
	}
	
	if (InputMappingContext == nullptr)
	{
		USK_LOG_WARNING("Unable to add input binding. Input mapping context is nullptr");
		return;
	}

	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr)
	{
		USK_LOG_ERROR("Unable to add input binding. Player controller is nullptr");
		return;
	}
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (Subsystem == nullptr)
	{
		USK_LOG_ERROR("Unable to add input binding. Enhanced input subsystem not found");
		return;
	}

	USK_LOG_TRACE("Adding menu input mapping context");
	Subsystem->RemoveMappingContext(InputMappingContext);
	Subsystem->AddMappingContext(InputMappingContext, 0);
	
	InitializeActionBindings(PlayerController);
	PlayerController->InputComponent->BindKey(EKeys::AnyKey, IE_Pressed, this, &UMenu::AnyKeyPressed);
}

/**
 * @brief Remove the input bindings for the menu
 */
void UMenu::RemoveInputBindings() const
{	
	if (PauseGameWhileVisible)
	{
		USK_LOG_INFO("Resuming game");
		if (IsValid(GameInstance))
		{
			GameInstance->UnpauseGame();
		}
		else
		{
			UGameplayStatics::SetGamePaused(GetWorld(), false);
		}		
	}
	
	if (InputMappingContext == nullptr)
	{
		USK_LOG_WARNING("Unable to remove input binding. Input mapping context is nullptr");
		return;
	}
	
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr)
	{
		USK_LOG_ERROR("Unable to remove input binding. Player controller is nullptr");
		return;
	}

	if (!ShouldUpdateInputBinding())
	{
		USK_LOG_INFO("Not updating input binding. Another menu was found");
		return;
	}
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (Subsystem == nullptr)
	{
		USK_LOG_ERROR("Unable to remove input binding. Enhanced input subsystem not found");
		return;
	}

	USK_LOG_TRACE("Removing menu input mapping context");
	Subsystem->RemoveMappingContext(InputMappingContext);
}

/**
 * @brief Is input allowed for the menu?
 * @return A boolean value indicating if input is allowed
 */
bool UMenu::IsInputAllowed() const
{
	return GetVisibility() != ESlateVisibility::Collapsed &&
		GetVisibility() != ESlateVisibility::Hidden &&
		!HasAnyFlags(RF_BeginDestroyed) && GetIsEnabled();
}

/**
 * @brief Initialize the action input bindings for the menu
 * @param PlayerController A reference to the current player controller
 */
void UMenu::InitializeActionBindings(const APlayerController* PlayerController)
{
	if (bIsActionBindingsInitialized)
	{
		USK_LOG_TRACE("Action bindings already initialized");
		return;
	}

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerController->GetPawn()->InputComponent);
	if (EnhancedInput == nullptr)
	{
		USK_LOG_ERROR("Unable to add input binding. Enhanced input component not found");
		return;
	}

	USK_LOG_TRACE("Adding input action bindings");
	EnhancedInput->BindAction(MenuUpInputAction, ETriggerEvent::Started, this, &UMenu::OnMenuUp);
	EnhancedInput->BindAction(MenuUpInputAction, ETriggerEvent::Started, this, &UMenu::OnMenuUpHold);
	EnhancedInput->BindAction(MenuDownInputAction, ETriggerEvent::Started, this, &UMenu::OnMenuDown);
	EnhancedInput->BindAction(MenuDownInputAction, ETriggerEvent::Started, this, &UMenu::OnMenuDownHold);
	EnhancedInput->BindAction(MenuLeftInputAction, ETriggerEvent::Started, this, &UMenu::OnMenuLeft);
	EnhancedInput->BindAction(MenuLeftInputAction, ETriggerEvent::Triggered, this, &UMenu::OnMenuLeftHold);
	EnhancedInput->BindAction(MenuRightInputAction, ETriggerEvent::Started, this, &UMenu::OnMenuRight);
	EnhancedInput->BindAction(MenuRightInputAction, ETriggerEvent::Triggered, this, &UMenu::OnMenuRightHold);
	EnhancedInput->BindAction(MenuSelectInputAction, ETriggerEvent::Started, this, &UMenu::OnMenuSelected);
	EnhancedInput->BindAction(MenuBackInputAction, ETriggerEvent::Started, this, &UMenu::OnMenuBack);
	bIsActionBindingsInitialized = true;
}

/**
 * @brief Initialize the menu items and highlight the default item
 */
void UMenu::InitializeMenuItems()
{
	USK_LOG_TRACE("Initializing default menu item");
	TArray<UWidget*> Children;
	WidgetTree->GetAllWidgets(Children);
	UMenuItem* FallbackMenuItem = nullptr;

	for (UWidget* Widget : Children)
	{
		if (!Widget->IsA(UMenuItem::StaticClass()))
		{
			continue;
		}
		
		UMenuItem* MenuItem = dynamic_cast<UMenuItem*>(Widget);
		if (MenuItem == nullptr)
		{
			continue;
		}

		MenuItem->Menu = this;
		if (CurrentMenuItem != nullptr)
		{
			continue;
		}
		
		if (FallbackMenuItem == nullptr)
		{
			FallbackMenuItem = MenuItem;
		}
		
		if (!MenuItem->FocusByDefault)
		{
			continue;
		}

		CurrentMenuItem = MenuItem;
	}

	if (CurrentMenuItem == nullptr)
	{
		USK_LOG_WARNING("No default menu item found");
		CurrentMenuItem = FallbackMenuItem;
	}
}

/**
 * @brief Update the highlighted item
 * @param NewItem The new item that should be highlighted
 * @param MenuNavigation The type of navigation used
 * @param IncreaseValue Should the value of the menu item be increased?
 * @param IsHolding Is the key being held down?
 */
void UMenu::UpdateHighlightedItem(UMenuItem* NewItem, const EMenuNavigation MenuNavigation, const bool IncreaseValue,
	const bool IsHolding)
{
	switch (MenuNavigation)
	{
	case EMenuNavigation::Disabled:
		break;
	case EMenuNavigation::HighlightItem:
		if (!IsValid(NewItem) || !NewItem->IsVisible())
		{
			break;
		}

		if (CurrentMenuItem != nullptr)
		{
			if (CurrentMenuItem->IsWaitingForKeyPress())
			{
				break;
			}
			
			CurrentMenuItem->SetHighlightedState(false, false, false);
		}
		
		CurrentMenuItem = NewItem;
		if (NewItem != nullptr)
		{
			NewItem->SetHighlightedState(true, true, true);
			if (ScrollContainer != nullptr)
			{
				ScrollContainer->ScrollWidgetIntoView(CurrentMenuItem);
			}
		}
		break;
	case EMenuNavigation::IncreaseDecreaseValue:
		if (CurrentMenuItem != nullptr &&
			(CurrentMenuItem->ValueUpdateMethod != EMenuItemValueUpdateMethod::Hold ||
			(CurrentMenuItem->ValueUpdateMethod == EMenuItemValueUpdateMethod::Hold && IsHolding)))
		{
			const float Value = IsHolding ? CurrentMenuItem->IncrementHold : CurrentMenuItem->IncrementSinglePress;
			CurrentMenuItem->UpdateValue(IncreaseValue ? Value : -Value);
		}
		break;
	}
}

/**
 * @brief Update the highlighted menu item before the navigation event
 * @param IsVerticalNavigation Is this called because of a vertical navigation event?
 */
void UMenu::UpdateHighlightedItemBeforeNavigation(const bool IsVerticalNavigation)
{
	if (CurrentMenuItem != nullptr || HighlightedMenuItemBeforeRemoval == nullptr)
	{
		return;
	}

	const EMenuNavigation ItemNavigation = IsVerticalNavigation
		? HighlightedMenuItemBeforeRemoval->VerticalNavigation
		: HighlightedMenuItemBeforeRemoval->HorizontalNavigation;
	if (ItemNavigation != EMenuNavigation::HighlightItem)
	{
		return;
	}

	CurrentMenuItem = HighlightedMenuItemBeforeRemoval;
	CurrentMenuItem->SetHighlightedState(true, false, false);
	HighlightedMenuItemBeforeRemoval = nullptr;
}

/**
 * @brief Called after any key is pressed by the player (used to remap controls)
 * @param Key The key pressed by the player
 */
void UMenu::AnyKeyPressed(const FKey Key)
{
	if (CurrentMenuItem != nullptr)
	{
		CurrentMenuItem->AnyKeyPressed(Key);
	}
}

/**
 * @brief Should the input binding be updated?
 * @return A boolean value indicating if the input binding should be updated
 */
bool UMenu::ShouldUpdateInputBinding() const
{
	TArray<UUserWidget*> Widgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), Widgets, StaticClass(), false);

	for (UUserWidget* Widget : Widgets)
	{
		const UMenu* Menu = dynamic_cast<UMenu*>(Widget);
		if (IsValid(Menu) && Menu != this && Menu->IsVisible() && !Menu->HasAnyFlags(RF_BeginDestroyed))
		{
			return false;
		}		
	}

	return true;
}

/**
 * @brief Called after the game is paused
 */
void UMenu::OnGamePaused()
{
	if (DisableWhilePaused)
	{
		USK_LOG_INFO("Disabling menu while game is paused");
		SetIsEnabled(false);
	}
}

/**
 * @brief Called after the game is unpaused
 */
void UMenu::OnGameUnpaused()
{
	if (DisableWhilePaused)
	{
		FLatentActionInfo LatentAction;
		LatentAction.Linkage = 0;
		LatentAction.CallbackTarget = this;
		LatentAction.UUID = GetUniqueID();
		LatentAction.ExecutionFunction = "EnableMenuAfterUnpaused";
		UKismetSystemLibrary::RetriggerableDelay(GetWorld(), EnableAfterUnpausedDelay, LatentAction);
	}
}

/**
 * @brief Enable the menu again after the game is unpaused
 */
void UMenu::EnableMenuAfterUnpaused()
{
	USK_LOG_INFO("Enabling menu after game is unpaused");
	SetIsEnabled(true);
}