// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldTextWordWidget.h"
#include "WorldTextLetterWidget.h"
#include "WorldText.generated.h"

class UWorldTextLetterWidget;
class UWorldTextWordWidget;

/**
 * @brief Actor used to display text in the world
 */
UCLASS()
class USK_API AWorldText : public AActor
{
	GENERATED_BODY()

	/**
	 * @brief The container for the text widget and trigger
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Narrative",
		meta=(AllowPrivateAccess = "true"))
	class USceneComponent* Container;

	/**
	 * @brief The trigger used to activate the text
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Narrative",
		meta=(AllowPrivateAccess = "true"))
	class UBoxComponent* TriggerComponent;

	/**
	 * @brief The text widget responsible for displaying the text
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Narrative",
		meta=(AllowPrivateAccess = "true"))
	class UWidgetComponent* TextWidgetComponent;
	
public:
	/**
	 * @brief The class used to create the word widget
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Narrative")
	TSubclassOf<UWorldTextWordWidget> WordWidgetClass;

	/**
	 * @brief The class used to create the letter widget
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Narrative")
	TSubclassOf<UWorldTextLetterWidget> LetterWidgetClass;

	/**
	 * @brief Is the trigger disabled?
	 */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Ultimate Starter Kit|Narrative")
	bool bIsDisabled;

	/**
	 * @brief The text that should be displayed
	 */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Ultimate Starter Kit|Narrative")
	FText Text;

	/**
	 * @brief The sound to play when activating the text
	 */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Ultimate Starter Kit|Narrative")
	USoundBase* Sound;

	/**
	 * @brief Should the audio be played at the actor's location?
	 */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Ultimate Starter Kit|Narrative",
		meta=(EditCondition = "Sound != nullptr", EditConditionHides))
	bool bPlaySoundAtActor;

	/**
	 * @brief An array of world text actors to activate when this text actor is destroyed
	 */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Ultimate Starter Kit|Narrative")
	TArray<AWorldText*> ActivateOnDestroy;

	/**
	 * @brief An array of world text actors to enable when this text actor is destroyed
	 */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Ultimate Starter Kit|Narrative")
	TArray<AWorldText*> EnableOnDestroy;

	/**
	 * @brief Constructor for the world text actor
	 */
	AWorldText();

	/**
	 * @brief Activate the text
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Narrative")
	void Activate();

protected:
	/**
	 * @brief Overridable native event for when play begins for this actor
	 */
	virtual void BeginPlay() override;
	
	/**
	 * @brief Event when this actor overlaps another actor
	 * @param OtherActor The other actor that caused the overlap event
	 */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	/**
	 * @brief Can the actor trigger the text?
	 * @param Actor The actor to check
	 * @return A boolean value indicating if the actor can trigger the text
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintNativeEvent, Category = "Ultimate Starter Kit|Narrative")
	bool CanActorTriggerText(const AActor* Actor) const;

private:
	/**
	 * @brief Called after the world text widget is destroyed
	 */
	UFUNCTION()
	void OnDestroyed();
};
