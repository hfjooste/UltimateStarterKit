// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "MenuItemValueUpdateMethod.h"
#include "MenuNavigation.h"
#include "Blueprint/UserWidget.h"
#include "MenuItem.generated.h"

/**
 * @brief A widget used to display a title, text and value in the form of a menu item
 */
UCLASS()
class USK_API UMenuItem : public UUserWidget
{
	GENERATED_BODY()

	/**
	 * @brief Event used to notify other classes that the menu item was selected
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMenuItemOnSelected);

	/**
	 * @brief Event used to notify other classes that the menu item was selected
	 * @param Value The new value of the menu item
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMenuItemOnValueChanged, int, Value);

public:
	/**
	 * @brief The TextBlock used to display the title of the menu item
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UTextBlock* Title;

	/**
	 * @brief The TextBlock used to display the text of the menu item while not highlighted
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UTextBlock* NormalText;

	/**
	 * @brief The TextBlock used to display the text of the menu item while highlighted
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UTextBlock* HighlightedText;

	/**
	 * @brief The TextBlock used to display the current value of the menu item
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UTextBlock* ValueText;

	/**
	 * @brief The TextBlock used to display the current value of the menu item while highlighted
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UTextBlock* HighlightedValueText;

	/**
	 * @brief The border displayed on the left of the menu item
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* BorderLeft;

	/**
	 * @brief The border displayed on the right of the menu item
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* BorderRight;

	/**
	 * @brief The background border display in the menu item
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* BorderBackground;

	/**
	 * @brief The button displayed on the left of the menu item
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* ButtonLeft;

	/**
	 * @brief The button displayed on the right of the menu item
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* ButtonRight;

	/**
	 * @brief The background button display in the menu item
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* ButtonBackground;

	/**
	 * @brief The animation played when the menu item is highlighted
	 */
	UPROPERTY(meta = (BindWidgetAnimOptional), Transient, EditAnywhere, BlueprintReadWrite,
		Category = "Ultimate Starter Kit|UI")
	class UWidgetAnimation* HighlightedAnimation;

	/**
	 * @brief Should the menu item be focused by default?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|General")
	bool FocusByDefault;

	/**
	 * @brief Should the menu item be hidden on consoles?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|General")
	bool HideOnConsoles;

	/**
	 * @brief The title text displayed in the menu item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|General")
	FText TitleText;

	/**
	 * @brief The text displayed in the menu item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|General")
	FText MenuItemText;

	/**
	 * @brief The sound effect played when the menu item is highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|General")
	USoundBase* HighlightedSFX;

	/**
	 * @brief The color of the border when not highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Border")
	FLinearColor BorderNormalColor;

	/**
	 * @brief The color of the border when highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Border")
	FLinearColor BorderHighlightedColor;

	/**
	 * @brief The image of the border when not highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Border")
	UTexture2D* BorderNormalImage;

	/**
	 * @brief The image of the border when highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Border")
	UTexture2D* BorderHighlightedImage;

	/**
	 * @brief The image of the left border when not highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Border")
	UTexture2D* BorderLeftNormalImage;

	/**
	 * @brief The image of the left border when highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Border")
	UTexture2D* BorderLeftHighlightedImage;

	/**
	 * @brief The image of the right border when not highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Border")
	UTexture2D* BorderRightNormalImage;

	/**
	 * @brief The image of the right border when highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Border")
	UTexture2D* BorderRightHighlightedImage;

	/**
	 * @brief The color of the button when not highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Background")
	FLinearColor BackgroundNormalColor;

	/**
	 * @brief The color of the button when highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Background")
	FLinearColor BackgroundHighlightedColor;

	/**
	 * @brief The image of the button when not highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Background")
	UTexture2D* BackgroundNormalImage;

	/**
	 * @brief The image of the button when highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Background")
	UTexture2D* BackgroundHighlightedImage;

	/**
	 * @brief The image of the left button when not highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Background")
	UTexture2D* BackgroundLeftNormalImage;

	/**
	 * @brief The image of the left button when highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Background")
	UTexture2D* BackgroundLeftHighlightedImage;

	/**
	 * @brief The image of the right button when not highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Background")
	UTexture2D* BackgroundRightNormalImage;

	/**
	 * @brief The image of the right button when highlighted
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Background")
	UTexture2D* BackgroundRightHighlightedImage;

	/**
	 * @brief The method used to update the value of the menu item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Navigation|Value")
	EMenuItemValueUpdateMethod ValueUpdateMethod = EMenuItemValueUpdateMethod::SinglePress;

	/**
	 * @brief The increment used when updating the value when the key is pressed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Navigation|Value",
		meta=(EditCondition = "ValueUpdateMethod ==  EMenuItemValueUpdateMethod::SinglePress", EditConditionHides))
	float IncrementSinglePress = 1.0f;

	/**
	 * @brief The increment used when updating the value when the key is held down
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Navigation|Value",
		meta=(EditCondition = "ValueUpdateMethod ==  EMenuItemValueUpdateMethod::Hold", EditConditionHides))
	float IncrementHold = 0.15f;

	/**
	 * @brief A mapping of possible values to text
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Navigation|Value")
	TMap<int, FText> ValueMapping;

	/**
	 * @brief The default value of the menu item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Navigation|Value")
	int DefaultValue = 100;

	/**
	 * @brief The minimum value of the menu item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Navigation|Value")
	int MinValue = 0;

	/**
	 * @brief The maximum value of the menu item
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Navigation|Value")
	int MaxValue = 100;

	/**
	 * @brief The type of navigation used by the menu item when pressing the up or down key
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Navigation")
	EMenuNavigation VerticalNavigation = EMenuNavigation::HighlightItem;

	/**
	 * @brief The menu item highlighted when the up key is pressed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Navigation",
		meta=(EditCondition = "VerticalNavigation == EMenuNavigation::HighlightItem", EditConditionHides))
	UMenuItem* MenuItemUp;

	/**
	 * @brief The menu item highlighted when the down key is pressed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Navigation",
    		meta=(EditCondition = "VerticalNavigation == EMenuNavigation::HighlightItem", EditConditionHides))
    UMenuItem* MenuItemDown;

	/**
	 * @brief The type of navigation used by the menu item when pressing the left or right key
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Navigation")
	EMenuNavigation HorizontalNavigation = EMenuNavigation::HighlightItem;

	/**
	 * @brief The menu item highlighted when the left key is pressed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Navigation",
		meta=(EditCondition = "HorizontalNavigation == EMenuNavigation::HighlightItem", EditConditionHides))
	UMenuItem* MenuItemLeft;

	/**
	 * @brief The menu item highlighted when the right key is pressed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Navigation",
			meta=(EditCondition = "HorizontalNavigation == EMenuNavigation::HighlightItem", EditConditionHides))
	UMenuItem* MenuItemRight;

	/**
	 * @brief Event used to notify other classes that the menu item was selected
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Save Data|Events")
	FMenuItemOnSelected OnSelectedEvent;

	/**
	 * @brief Event used to notify other classes that the menu item's value was updated
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Save Data|Events")
	FMenuItemOnValueChanged OnValueChanged;

	/**
	 * @brief Set the text display in the menu item
	 * @param Text The new text displayed in the menu item
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void SetText(const FText& Text) const;

	/**
	 * @brief Set the highlighted state of the menu item
	 * @param IsHighlighted Is the menu item highlighted?
	 * @param PlayHighlightedSound Should the highlighted sound effect be played?
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void SetHighlightedState(bool IsHighlighted, const bool PlayHighlightedSound);

	/**
	 * @brief Get the current value of the menu item
	 * @return The current value of the menu item
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	int GetValue() const;

	/**
	 * @brief Update the value of the menu item
	 * @param Increment The amount added to the current value of the menu item 
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void UpdateValue(float Increment);

protected:
	/**
	 * @brief Overridable native event for when the widget has been constructed in the editor
	 */
	virtual void NativePreConstruct() override;

	/**
	 * @brief Overridable native event for when the widget has been constructed
	 */
	virtual void NativeConstruct() override;

private:
	/**
	 * @brief The current value of the menu item
	 */
	float CurrentValue;

	/**
	 * @brief Update the value text of the menu item 
	 */
	void UpdateValueText() const;
};