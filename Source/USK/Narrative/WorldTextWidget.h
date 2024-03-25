// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WrapBox.h"
#include "WorldTextWidget.generated.h"

class UWorldTextLetterWidget;
class UWorldTextWordWidget;

/**
 * @brief The widget used to display text in the world
 */
UCLASS()
class USK_API UWorldTextWidget : public UUserWidget
{
	GENERATED_BODY()

	/**
	 * @brief Event used to notify other classes when the text is destroyed
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWorldTextDestroyed);
	
public:
	/**
	 * @brief The container for all the word widgets
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Narrative")
	UWrapBox* Container;

	/**
	 * @brief Event used to notify other classes when the text is destroyed
	 */
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Ultimate Starter Kit|Narrative")
	FWorldTextDestroyed OnDestroyed;

	/**
	 * @brief The delay before destroying the text widget after typing has finished
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Narrative")
	float DestroyTextDelay = 2.0f;

	/**
	 * @brief The delay before destroying the actor after the text widget has been destroyed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Narrative")
	float DestroyActorDelay = 1.0f;

	/**
	 * @brief Initialize the widget
	 * @param WordClass The world word widget class
	 * @param LetterClass The world letter widget class
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Narrative")
	void InitializeWidget(TSubclassOf<UWorldTextWordWidget> WordClass, TSubclassOf<UWorldTextLetterWidget> LetterClass);

	/**
	 * @brief Show the text in the widget
	 * @param Text The text to display
	 * @param Sound The sound to play when displaying the text
	 * @param PlaySoundAtActor The actor to play the sound at
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Narrative")
	void Show(const FText& Text, USoundBase* Sound, AActor* PlaySoundAtActor);

	/**
	 * @brief Destroy the text widget
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Narrative")
	void Destroy() const;

	/**
	 * @brief Get the world word widget class
	 * @return The world word widget class
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Narrative")
	TSubclassOf<UWorldTextWordWidget> GetWordWidgetClass() const;

	/**
	 * @brief Get the world letter widget class
	 * @return The world letter widget class
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Narrative")
	TSubclassOf<UWorldTextLetterWidget> GetLetterWidgetClass() const;

private:
	/**
	 * @brief The world word widget class
	 */
	TSubclassOf<UWorldTextWordWidget> WordWidgetClass;

	/**
	 * @brief The world letter widget class
	 */
	TSubclassOf<UWorldTextLetterWidget> LetterWidgetClass;

	/**
	 * @brief Update the text displayed in the widget
	 * @param Text The text to display
	 */
	void UpdateText(const FText& Text);

	/**
	 * @brief Destroy the text widget after a delay
	 */
	void DestroyAfterDelay() const;
};
