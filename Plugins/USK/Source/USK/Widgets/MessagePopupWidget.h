// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "MessagePopupData.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MessagePopupWidget.generated.h"

class UMenuItem;
class UMenu;

/**
 * @brief The widget used to display a message popup
 */
UCLASS()
class USK_API UMessagePopupWidget : public UUserWidget
{
	GENERATED_BODY()

	/**
	 * @brief Event used to notify other classes that the popup was shown
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMessagePopupShown);
	
	/**
	 * @brief Event used to notify other classes that the popup was hidden
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMessagePopupHidden);

	/**
	 * @brief Event used to notify other classes that the positive button was selected
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMessagePopupPositiveButtonSelected);

	/**
	 * @brief Event used to notify other classes that the negative button was selected
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMessagePopupNegativeButtonSelected);

	/**
	 * @brief Event used to notify other classes that the neutral button was selected
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMessagePopupNeutralButtonSelected);
	
public:
	/**
	 * @brief The animation used to show the popup
	 */
	UPROPERTY(meta = (BindWidgetAnimOptional), Transient, EditAnywhere, BlueprintReadWrite,
			Category = "Ultimate Starter Kit|UI")
	UWidgetAnimation* ShowAnimation;

	/**
	 * @brief The animation used to hide the popup
	 */
	UPROPERTY(meta = (BindWidgetAnimOptional), Transient, EditAnywhere, BlueprintReadWrite,
			Category = "Ultimate Starter Kit|UI")
	UWidgetAnimation* HideAnimation;

	/**
	 * @brief The text block used to display the title
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	UTextBlock* TitleText;

	/**
	 * @brief The text block used to display the message
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	UTextBlock* MessageText;

	/**
	 * @brief The menu used to display the buttons
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	UMenu* ButtonMenu;

	/**
	 * @brief The button menu item class used when creating the buttons
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	TSubclassOf<UMenuItem> ButtonMenuItemClass;

	/**
	 * @brief Event used to notify other classes that the popup was shown
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|UI|Events")
	FMessagePopupShown OnShown;

	/**
	 * @brief Event used to notify other classes that the popup was hidden
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|UI|Events")
	FMessagePopupHidden OnHidden;

	/**
	 * @brief Event used to notify other classes that the positive button was selected
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|UI|Events")
	FMessagePopupPositiveButtonSelected OnPositiveButtonSelected;

	/**
	 * @brief Event used to notify other classes that the negative button was selected
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|UI|Events")
	FMessagePopupNegativeButtonSelected OnNegativeButtonSelected;

	/**
	 * @brief Event used to notify other classes that the neutral button was selected
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|UI|Events")
	FMessagePopupNeutralButtonSelected OnNeutralButtonSelected;

	/**
	 * @brief Show the message popup
	 * @param Data The data used to display the popup
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void Show(FMessagePopupData Data);

	/**
	 * @brief Hide the message popup
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void Hide();

private:
	/**
	 * @brief A reference to the positive button
	 */
	UPROPERTY()
	UMenuItem* PositiveButton;

	/**
	 * @brief A reference to the negative button
	 */
	UPROPERTY()
	UMenuItem* NegativeButton;

	/**
	 * @brief A reference to the neutral button
	 */
	UPROPERTY()
	UMenuItem* NeutralButton;

	/**
	 * @brief Remove the popup widget
	 */
	void RemoveWidget();

	/**
	 * @brief Create a button menu item
	 * @param ButtonText The text displayed on the button
	 * @return A reference to the new button menu item
	 */
	UMenuItem* CreateButton(const FText& ButtonText) const;

	/**
	 * @brief Update the navigation of all the buttons
	 */
	void UpdateButtonNavigation();

	/**
	 * @brief Called when the positive button is clicked
	 */
	UFUNCTION()
	void OnPositiveButtonClicked();

	/**
	 * @brief Called when the negative button is clicked
	 */
	UFUNCTION()
	void OnNegativeButtonClicked();

	/**
	 * @brief Called when the neutral button is clicked
	 */
	UFUNCTION()
	void OnNeutralButtonClicked();
};
