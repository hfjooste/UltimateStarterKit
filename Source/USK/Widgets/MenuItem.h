// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "MenuItemValueUpdateMethod.h"
#include "MenuNavigation.h"
#include "Blueprint/UserWidget.h"
#include "USK/Core/InputDevice.h"
#include "USK/Settings/SettingsItemType.h"
#include "MenuItem.generated.h"

class UMenu;

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
	 * @brief Event used to notify other classes that a specific menu item in the container was selected
	 * @param Index The index of the menu item that was selected
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMenuItemOnSelectedInContainer, int, Index);

	/**
	 * @brief Event used to notify other classes that the menu item was highlighted
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMenuItemOnHighlighted);

	/**
	 * @brief Event used to notify other classes that the menu item's highlighted state was removed
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMenuItemOnHighlightRemoved);

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
	 * @brief The button used to select the menu item
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UButton* SelectButton;

	/**
	 * @brief The slider used to display and update the current value of the menu item
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class USlider* ValueSlider;

	/**
	 * @brief The button used to increase the value of the menu item
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UButton* IncreaseValueButton;

	/**
	 * @brief The button used to decrease the value of the menu item
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UButton* DecreaseValueButton;

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
	 * @brief The background button display in the menu item
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* InputIndicator;

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
	 * @brief The type of setting item managed by this menu item (changing this will overwrite other settings)
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Settings")
	ESettingsItemType SettingsItemType = ESettingsItemType::None;

	/**
	 * @brief Should the settings managed by this menu item automatically be saved when the value is changed?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Settings",
		meta=(EditCondition = "SettingsItemType != ESettingsItemType::None && SettingsItemType != ESettingsItemType::ControlsRemap",
			EditConditionHides))
	bool AutoSaveSettingsOnValueChanged = true;

	/**
	 * @brief Should the settings managed by this menu item automatically be saved when the highlight state is removed?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Settings",
		meta=(EditCondition = "SettingsItemType != ESettingsItemType::None && SettingsItemType != ESettingsItemType::ControlsRemap",
			EditConditionHides))		
	bool AutoSaveSettingsOnHighlightRemoved = true;

	/**
	 * @brief Should the settings managed by this menu item automatically be saved when the menu item is selected?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Settings",
		meta=(EditCondition = "SettingsItemType != ESettingsItemType::None && SettingsItemType != ESettingsItemType::ControlsRemap",
			EditConditionHides))
	bool AutoSaveSettingsOnSelected = true;

	/**
	 * @brief The input device associated with the action to rebind
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Settings",
		meta=(EditCondition = "SettingsItemType == ESettingsItemType::ControlsRemap", EditConditionHides))
	EInputDevice InputDevice = EInputDevice::Unknown;
	
	/**
	 * @brief The input mapping context containing the action to rebind
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Settings",
		meta=(EditCondition = "SettingsItemType == ESettingsItemType::ControlsRemap", EditConditionHides))
	class UInputMappingContext* InputMappingContext;

	/**
	 * @brief The input action to rebind
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Settings",
		meta=(EditCondition = "SettingsItemType == ESettingsItemType::ControlsRemap", EditConditionHides))
	class UInputAction* InputAction;

	/**
	 * @brief The player mappable name for the action to rebind
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Settings",
		meta=(EditCondition = "SettingsItemType == ESettingsItemType::ControlsRemap", EditConditionHides))
	FName MappableName;
	
	/**
	 * @brief Should the value slider be shown for this menu item?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Navigation|Value")
	bool ShowValueSlider = false;

	/**
	 * @brief Should the increase/decrease value buttons be shown for this menu item?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Navigation|Value")
	bool ShowValueButtons = false;

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
	 * @brief Can the menu item be selected?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI|Navigation")
	bool AllowSelection = true;
	
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
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|UI|Events")
	FMenuItemOnSelected OnSelected;

	/**
	 * @brief Event used to notify other classes that a specific menu item in the container was selected
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|UI|Events")
	FMenuItemOnSelectedInContainer OnSelectedInContainer;

	/**
	 * @brief Event used to notify other classes that the menu item was highlighted
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|UI|Events")
	FMenuItemOnHighlighted OnHighlighted;

	/**
	 * @brief Event used to notify other classes that the menu item's highlighted state was removed
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|UI|Events")
	FMenuItemOnHighlightRemoved OnHighlightRemoved;

	/**
	 * @brief Event used to notify other classes that the menu item's value was updated
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|UI|Events")
	FMenuItemOnValueChanged OnValueChanged;

	/**
	 * @brief A reference to the menu that contains this menu item
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ultimate Starter Kit|UI")
	UMenu* Menu;

	/**
	 * @brief Set the text displayed in the menu item
	 * @param Text The new text displayed in the menu item
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void SetText(const FText& Text) const;

	/**
	 * @brief Set the title displayed in the menu item
	 * @param Text The new title displayed in the menu item
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void SetTitle(const FText& Text) const;

	/**
	 * @brief Set the highlighted state of the menu item
	 * @param IsHighlighted Is the menu item highlighted?
	 * @param PlayHighlightedAnimation Should the highlighted animation be played?
	 * @param PlayHighlightedSound Should the highlighted sound effect be played?
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void SetHighlightedState(bool IsHighlighted, const bool PlayHighlightedAnimation, const bool PlayHighlightedSound);

	/**
	 * @brief Check if the menu item is highlighted
	 * @return A boolean value indicating if the menu item is highlighted
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|UI")
	bool IsHighlighted() const;

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

	/**
	 * @brief Select the menu item
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void SelectItem();

	/**
	 * @brief Save the settings managed by this menu item
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void SaveSettings();

	/**
	 * @brief Apply the settings managed by this menu item
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void ApplySettings();

	/**
	 * @brief Get the key used by the specified input action
	 * @return The key used by the specified input action
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	FKey GetInputActionKey() const;

	/**
	 * @brief Called when trying to go back in the menu
	 * @return A boolean value indicating if the back event was handled
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	bool OnMenuBack();

	/**
	 * @brief Called after any key is pressed by the player (used to remap controls)
	 * @param Key The key pressed by the player
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void AnyKeyPressed(const FKey Key);

	/**
	 * @brief Apply the key binding for the input action
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void ApplyKeyBinding();

	/**
	 * @brief Is the menu item waiting for a key press?
	 * @return A boolean value indicating if the menu item is waiting for a key press
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	bool IsWaitingForKeyPress();

protected:
	/**
	 * @brief Overridable native event for when the widget has been constructed in the editor
	 */
	virtual void NativePreConstruct() override;

	/**
	 * @brief Overridable native event for when the widget has been constructed
	 */
	virtual void NativeConstruct() override;

	/**
	 * @brief Overridable native event for when the cursor has entered the widget
	 * @param InGeometry The Geometry of the widget receiving the event
	 * @param InMouseEvent Information about the input event
	 */
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	/**
	 * @brief Overridable native event for when the cursor has left the widget
	 * @param InMouseEvent Information about the input event
	 */
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
private:
	/**
	 * @brief The current value of the menu item
	 */
	float CurrentValue;

	/**
	 * @brief The text displayed in the menu item while waiting for a key press
	 */
	FText ControlsWaitingForKeyPressText;

	/**
	 * @brief The current key used by the input action
	 */
	FKey CurrentKey = EKeys::Invalid;

	/**
	 * @brief The key that should be applied to the input action
	 */
	FKey QueuedKey = EKeys::Invalid;

	/**
	 * @brief The delay before the key binding is applied
	 */
	float ApplyKeyBindingDelay = 0.05f;

	/**
	 * @brief Is the menu item waiting for a key press?
	 */
	bool WaitingForKeyPress;

	/**
	 * @brief Is the menu item highlighted?
	 */
	bool bIsHighlighted;

	/**
	 * @brief Update the value text of the menu item 
	 */
	void UpdateValueText() const;

	/**
	 * @brief Can the value of the menu item be changed?
	 * @return A boolean value indicating if the value of the menu item can be changed
	 */
	bool CanValueChange() const;

	/**
	 * @brief Called after the value of the slider is manually changed
	 * @param Value The new value of the slider
	 */
	UFUNCTION()
	void OnSliderValueChanged(float Value);

	/**
	 * @brief Called after the select button is clicked
	 */
	UFUNCTION()
	void OnSelectButtonClicked();

	/**
	 * @brief Called after the increase value button is clicked
	 */
	UFUNCTION()
	void OnIncreaseValueButtonClicked();

	/**
	 * @brief Called after the decrease value button is clicked
	 */
	UFUNCTION()
	void OnDecreaseValueButtonClicked();

	/**
	 * @brief Automatically save the settings managed by this menu item
	 * @param SaveFlag The flag used to enable/disable auto saving
	 */
	void AutoSaveSettings(bool SaveFlag) const;
	
	/**
	 * @brief Update the input indicator icon
	 */
	void UpdateInputIndicator();
};