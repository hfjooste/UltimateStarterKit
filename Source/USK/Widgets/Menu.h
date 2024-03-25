// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Blueprint/UserWidget.h"
#include "MenuNavigation.h"
#include "Menu.generated.h"

class UUSKGameInstance;
class UMenuItem;
class UInputAction;
class UInputMappingContext;

/**
 * @brief A widget used to display menu items and handle navigation between the items
 */
UCLASS()
class USK_API UMenu : public UUserWidget
{
	GENERATED_BODY()

	/**
	 * @brief Event used to handle the back/close action of the menu
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMenuOnBack);
	
public:
	/**
	 * @brief Scroll container used for large menus with many items
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UScrollBox* ScrollContainer;

	/**
	 * @brief The container used to display the menu items
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UPanelWidget* Container;

	/**
	 * @brief Should the input binding automatically be added as soon as the widget is loaded?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|General")
	bool AddInputBindingOnLoad;

	/**
	 * @brief Should the game automatically be paused/resumed based on the visibility of the menu?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|General")
	bool PauseGameWhileVisible;

	/**
	 * @brief Should the menu be disabled while the game is paused?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|General")
	bool DisableWhilePaused;

	/**
	 * @brief The sound effect played when a menu item is selected
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Menu Items")
	USoundBase* SelectedSFX;

	/**
	 * @brief The sound effect played when trying to go back to a previous menu or closing the menu through the back button
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Menu Items")
	USoundBase* BackSFX;

	/**
	 * @brief The input mapping context used to navigate the menu
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|UI|Input")
	UInputMappingContext* InputMappingContext;

	/**
	 * @brief The input action used to navigate up
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|UI|Input")
	UInputAction* MenuUpInputAction;

	/**
	 * @brief The input action used to navigate down
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|UI|Input")
	UInputAction* MenuDownInputAction;

	/**
	 * @brief The input action used to navigate left
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|UI|Input")
	UInputAction* MenuLeftInputAction;

	/**
	 * @brief The input action used to navigate right
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|UI|Input")
    UInputAction* MenuRightInputAction;

	/**
	 * @brief The input action used to select a menu item
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|UI|Input")
	UInputAction* MenuSelectInputAction;

	/**
	 * @brief The input action used to go back to a previous menu or close the menu
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|UI|Input")
	UInputAction* MenuBackInputAction;

	/**
	 * @brief Event used to handle the back/close action of the menu
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Save Data|Events")
	FMenuOnBack OnBackEvent;

	/**
	 * @brief Navigate up or increase the value
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void OnMenuUp();

	/**
	 * @brief Increase the value while holding the menu up key
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void OnMenuUpHold();

	/**
	 * @brief Navigate down or decrease the value
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void OnMenuDown();

	/**
	 * @brief Decrease the value while holding the menu down key
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void OnMenuDownHold();

	/**
	 * @brief Navigate left or decrease the value
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void OnMenuLeft();

	/**
	 * @brief Decrease the value while holding the menu left key
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void OnMenuLeftHold();

	/**
	 * @brief Navigate right or increase the value
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void OnMenuRight();

	/**
	 * @brief Increase the value while holding the menu right key
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void OnMenuRightHold();

	/**
	 * @brief Select the current menu item
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void OnMenuSelected();

	/**
	 * @brief Go back to a previous menu or close the menu
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void OnMenuBack();

	/**
	 * @brief Request to highlight a specific menu item
	 * @param MenuItem The menu item to highlight
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void RequestHighlight(UMenuItem* MenuItem);

	/**
	 * @brief Request to remove the highlighted state from a specific menu item
	 * @param MenuItem The menu item to remove the highlighted state from
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void RemoveHighlight(UMenuItem* MenuItem);

	/**
	 * @brief Add a menu item to the container
	 * @param MenuItem The menu item to add
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void AddMenuItem(UMenuItem* MenuItem);

protected:
	/**
	 * @brief Overridable native event for when the widget has been constructed
	 */
	virtual void NativeConstruct() override;

	/**
	 * @brief Overridable native event for when the widget has been destroyed
	 */
	virtual void NativeDestruct() override;

	/**
	 * @brief Overridable native event for when the widget has been initialized
	 */
	virtual void NativeOnInitialized() override;
	
private:
	/**
	 * @brief A reference to the game instance
	 */
	UPROPERTY()
	UUSKGameInstance* GameInstance;
	
	/**
	 * @brief A reference to the current menu item
	 */
	UPROPERTY()
	UMenuItem* CurrentMenuItem;

	/**
	 * @brief A reference to the highlighted menu item before the highlight state was removed
	 */
	UPROPERTY()
	UMenuItem* HighlightedMenuItemBeforeRemoval;

	/**
	 * @brief Has the action bindings been initialized?
	 */
	bool bIsActionBindingsInitialized;

	/**
	 * @brief The delay before the menu is enabled after the game is unpaused
	 */
	float EnableAfterUnpausedDelay = 0.05f;

	/**
	 * @brief Called when the visibility of the menu is changed
	 * @param NewVisibility The new visibility of the menu
	 */
	UFUNCTION()
	void OnMenuVisibilityChanged(ESlateVisibility NewVisibility);

	/**
	 * @brief Add the input bindings for the menu
	 */
	void AddInputBindings();

	/**
	 * @brief Remove the input bindings for the menu
	 */
	void RemoveInputBindings() const;

	/**
	 * @brief Is input allowed for the menu?
	 * @return A boolean value indicating if input is allowed
	 */
	bool IsInputAllowed() const;

	/**
	 * @brief Initialize the action input bindings for the menu
	 * @param PlayerController A reference to the current player controller
	 */
	void InitializeActionBindings(const APlayerController* PlayerController);

	/**
	 * @brief Initialize the menu items and highlight the default item
	 */
	void InitializeMenuItems();

	/**
	 * @brief Update the highlighted item
	 * @param NewItem The new item that should be highlighted
	 * @param MenuNavigation The type of navigation used
	 * @param IncreaseValue Should the value of the menu item be increased?
	 * @param IsHolding Is the key being held down?
	 */
	void UpdateHighlightedItem(UMenuItem* NewItem, EMenuNavigation MenuNavigation, bool IncreaseValue, bool IsHolding);

	/**
	 * @brief Update the highlighted menu item before the navigation event
	 * @param IsVerticalNavigation Is this called because of a vertical navigation event?
	 */
	void UpdateHighlightedItemBeforeNavigation(bool IsVerticalNavigation);

	/**
	 * @brief Called after any key is pressed by the player (used to remap controls)
	 * @param Key The key pressed by the player
	 */
	UFUNCTION()
	void AnyKeyPressed(const FKey Key);

	/**
	 * @brief Should the input binding be updated?
	 * @return A boolean value indicating if the input binding should be updated
	 */
	bool ShouldUpdateInputBinding() const;

	/**
	 * @brief Called after the game is paused
	 */
	UFUNCTION()
	void OnGamePaused();

	/**
	 * @brief Called after the game is unpaused
	 */
	UFUNCTION()
	void OnGameUnpaused();

	/**
	 * @brief Enable the menu again after the game is unpaused
	 */
	UFUNCTION()
	void EnableMenuAfterUnpaused();
};