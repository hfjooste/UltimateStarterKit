// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Blueprint/UserWidget.h"
#include "MenuNavigation.h"
#include "Menu.generated.h"

class UMenuItem;

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
	 * @brief Navigate up
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void OnMenuUp();

	/**
	 * @brief Navigate down
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void OnMenuDown();

	/**
	 * @brief Navigate left
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void OnMenuLeft();

	/**
	 * @brief Navigate right
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void OnMenuRight();

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
	 * @brief A reference to the current menu item
	 */
	UPROPERTY()
	UMenuItem* CurrentMenuItem;

	/**
	 * @brief Has the action bindings been initialized?
	 */
	bool bIsActionBindingsInitialized;

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
	 * @brief Initialize the action input bindings for the menu
	 * @param PlayerController A reference to the current player controller
	 */
	void InitializeActionBindings(const APlayerController* PlayerController);

	/**
	 * @brief Initialize the default item in the menu
	 */
	void InitializeDefaultItem();

	/**
	 * @brief Update the highlighted item
	 * @param NewItem The new item that should be highlighted
	 * @param MenuNavigation The type of navigation used
	 * @param IncreaseValue Should the value of the menu item be increased?
	 */
	void UpdateHighlightedItem(UMenuItem* NewItem, EMenuNavigation MenuNavigation, bool IncreaseValue);
};