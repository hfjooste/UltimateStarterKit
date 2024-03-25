// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "USK/Items/CollectableItem.h"
#include "AttractComponent.generated.h"

class UInteractWidget;

/**
 * @brief A component that can be used to attract the owning object to the player
 */
UCLASS(Blueprintable, ClassGroup=("UltimateStarterKit"), DisplayName="Attract Component",
	meta=(BlueprintSpawnableComponent))
class USK_API UAttractComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	/**
	 * @brief The speed at which the object is attracted to the player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ultimate Starter Kit|Attract Component")
	float AttractSpeed = 5.0f;

	/**
	 * @brief The distance at which the object is collected by the player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ultimate Starter Kit|Attract Component")
	float CollectDistance = 75.0f;

	/**
	 * @brief Create a new instance of UAttractComponent
	 */
	UAttractComponent();

protected:
	/**
	 * @brief Overridable native event for when play begins for this actor
	 */
	virtual void BeginPlay() override;
	
	/**
	 * @brief Function called every frame on this ActorComponent
	 * @param DeltaTime The time since the last tick
	 * @param TickType The kind of tick this is, for example, are we paused, or 'simulating' in the editor
	 * @param ThisTickFunction Internal tick function struct that caused this to run
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

private:
	/**
	 * @brief A reference to the player that is attracting the object
	 */
	UPROPERTY()
	APawn* Player = nullptr;

	/**
	 * @brief A reference to the owner item
	 */
	UPROPERTY()
	ACollectableItem* Item = nullptr;
	
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