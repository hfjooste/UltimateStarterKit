// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreditsEntry.h"
#include "CreditsWidget.generated.h"

/**
 * @brief Widget used to display multiple animated credits entries using different alignment options and durations 
 */
UCLASS()
class USK_API UCreditsWidget : public UUserWidget
{
	GENERATED_BODY()

	/**
	 * @brief Event used to notify other classes when the credits are finished
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCreditsFinishedDelegate);

	/**
	 * @brief Event used to notify other classes every time a next entry is started
	 * @param Name The index of the entry that was started
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCreditsNextEntryStarted, int, Index);
	
public:
	/**
	 * @brief The animation played each time a new entry is shown
	 */
	UPROPERTY(meta = (BindWidgetAnimOptional), Transient, EditAnywhere, BlueprintReadWrite,
		Category = "Ultimate Starter Kit|UI")
	class UWidgetAnimation* ShowAnimation;

	/**
	 * @brief The animation played at the end of each entry
	 */
	UPROPERTY(meta = (BindWidgetAnimOptional), Transient, EditAnywhere, BlueprintReadWrite,
		Category = "Ultimate Starter Kit|UI")
	class UWidgetAnimation* HideAnimation;

	/**
	 * @brief The root container of the widget
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UPanelWidget* Root;

	/**
	 * @brief The container used to display the credits entries
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UPanelWidget* Container;

	/**
	 * @brief The text block used to display the title of the credits entry
	 */
	UPROPERTY(meta = (BindWidgetOptional), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UTextBlock* Title;

	/**
	 * @brief The text block used to display the text of the credits entry
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UTextBlock* Text;

	/**
	 * @brief Event used to notify other classes when the credits are finished
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|UI|Events")
	FCreditsFinishedDelegate OnCreditsFinished;

	/**
	 * @brief Event used to notify other classes every time a next entry is started
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|UI|Events")
	FCreditsNextEntryStarted OnCreditsNextEntryStarted;

	/**
	 * @brief Should the credits automatically be started when the widget is constructed?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	bool AutoStart = true;

	/**
	 * @brief Should the widget automatically be removed from the viewport when the credits are finished?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	bool RemoveOnCompletion = true;

	/**
	 * @brief The delay in seconds before the first credits entry is shown after starting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	float StartDelay = 1.0f;

	/**
	 * @brief The delay in seconds between the previous hide animation and the next show animation
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	float DelayBetweenEntries = 3.0f;

	/**
	 * @brief The array of credits entries to be displayed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	TArray<FCreditsEntry> Credits;

	/**
	 * @brief Start showing the credits
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void Start();

protected:
	/**
	 * @brief Overridable native event for when the widget has been constructed
	 */
	virtual void NativeConstruct() override;

private:
	/**
	 * @brief The index of the current credits entry
	 */
	int EntryIndex = -1;

	/**
	 * @brief Show the next credits entry
	 */
	UFUNCTION()
	void ShowNextEntry();

	/**
	 * @brief Finish showing the current credits entry
	 */
	UFUNCTION()
	void FinishCurrentEntry();

	/**
	 * @brief Get the horizontal anchor for the given alignment
	 * @param HorizontalAlignment The horizontal alignment
	 * @return The horizontal anchor for the given alignment
	 */
	float GetHorizontalAnchor(EHorizontalAlignment HorizontalAlignment);

	/**
	 * @brief Get the vertical anchor for the given alignment
	 * @param VerticalAlignment The vertical alignment
	 * @return The vertical anchor for the given alignment
	 */
	float GetVerticalAnchor(EVerticalAlignment VerticalAlignment);
};
