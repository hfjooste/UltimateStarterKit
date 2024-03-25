// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "InteractTrigger.generated.h"

class UInteractWidget;

/**
 * @brief A trigger that can be used to interact with an object
 */
UCLASS(Blueprintable, ClassGroup=("UltimateStarterKit"), DisplayName="Interact Trigger",
	meta=(BlueprintSpawnableComponent))
class USK_API UInteractTrigger : public UBoxComponent
{
	GENERATED_BODY()

public:
	/**
	 * @brief Is this a paid item that should be bought using currency?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Interact Trigger|Requirements")
	bool bRequireCurrency;

	/**
	 * @brief The currency requirements before the object can be interacted with
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Interact Trigger|Requirements",
		meta=(EditCondition = "bRequireCurrency", EditConditionHides))
	TMap<FName, int> CurrencyRequirements;
	
	/**
	 * @brief The class of the interact widget
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Interact Trigger|Widget")
	TSubclassOf<UInteractWidget> InteractWidgetClass;

	/**
	 * @brief The text displayed before the input indicator
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Interact Trigger|Widget")
	FText BeforeText;

	/**
	 * @brief The text displayed after the input indicator
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Interact Trigger|Widget")
	FText AfterText;
	
	/**
	 * @brief Check if the actor can interact with the object
	 * @param Actor The actor trying to interact with the object
	 * @return A boolean value indicating if the actor can interact with the object
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintNativeEvent, Category = "Ultimate Starter Kit|Interact Trigger")
	bool CanInteract(AActor* Actor);

	/**
	 * @brief Called when the actor interacts with the object
	 * @param Actor The actor that interacted with the object
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Interact Trigger")
	void OnInteracted(AActor* Actor);

	/**
	 * @brief Show the interact widget
	 */
	void ShowWidget();

	/**
	 * @brief Hide the interact widget
	 */
	void HideWidget();
	
protected:
	/**
	 * @brief Overridable native event for when play begins for this actor
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Called when the actor interacts with the object
	 * @param Actor The actor that interacted with the object
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ultimate Starter Kit|Interact Trigger",
		meta=(DisplayName = "OnInteracted"))
	void ReceiveOnInteracted(AActor* Actor);

private:
	/**
	 * @brief The current interact widget
	 */
	UPROPERTY()
	UInteractWidget* InteractWidget;
	
	/**
	 * @brief Event when this component overlaps another actor
	 * @param OverlappedComponent The component that triggered the event
	 * @param OtherActor The other actor that caused the overlap event
	 * @param OtherComp The other component that caused the overlap event
	 * @param OtherBodyIndex The index of the other body that caused the overlap event
	 * @param bFromSweep A boolean value indicating if the overlap event was caused by a sweep 
	 * @param SweepResult The result of the sweep that caused the overlap event
	 */
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/**
	 * @brief Event when this component stops overlapping another actor
	 * @param OverlappedComponent The component that triggered the event
	 * @param OtherActor The other actor that caused the overlap event
	 * @param OtherComp The other component that caused the overlap event
	 * @param OtherBodyIndex The index of the other body that caused the overlap event
	 */
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
