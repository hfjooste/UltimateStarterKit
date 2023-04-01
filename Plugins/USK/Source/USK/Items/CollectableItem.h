// Created by Henry Jooste

#pragma once

#include "AllowedCollector.h"
#include "NiagaraCommon.h"
#include "CollectableItem.generated.h"

UCLASS()
/**
 * @brief An item that can be collected by an actor 
 */
class USK_API ACollectableItem : public AActor
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Should the item be destroyed after it has been collected
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Item")
	bool DestroyOnCollected = true;

	/**
	 * @brief The type of actor that can collect the item
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Item")
	EAllowedCollector AllowedCollector = EAllowedCollector::PossessedPawn;

	/**
	 * @brief The array of actor types that can collect the item
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Item",
		meta=(EditCondition = "AllowedCollector == EAllowedCollector::Custom", EditConditionHides))
	TArray<TSubclassOf<AActor>> AllowedCollectorTypes;

	/**
	 * @brief An array of sound effects played when collecting the item
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Item|Effects")
	TArray<USoundBase*> CollectedSoundEffects;
	
	/**
	 * @brief The particle effects spawned when collecting the item
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Item|Effects")
	UNiagaraSystem* CollectedParticleFx;

	/**
	 * @brief The offset applied to the location of the collected particles when spawning
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Item|Effects")
	FVector CollectedParticleFxSpawnOffset;

	/**
	 * @brief Collect the item
	 * @param Collector A pointer to the actor that collected the item
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Item")
	void CollectItem(AActor* Collector);

	/**
	 * @brief Called after the item is collected
	 * @param Collector A pointer to the actor that collected the item
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ultimate Starter Kit|Item")
	void OnItemCollected(AActor* Collector);

protected:
	/**
	 * @brief Event when this actor overlaps another actor
	 * @param OtherActor The other actor that caused the overlap event
	 */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	/**
	 * @brief Should the item be collected?
	 * @param OtherActor The other actor that caused the overlap event
	 * @return A boolean value indicating if the item should be collected
	 */
	bool ShouldBeCollected(const AActor* OtherActor);
};