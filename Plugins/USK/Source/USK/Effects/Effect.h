// Created by Henry Jooste

#pragma once

#include "Effect.generated.h"

/**
 * @brief Temporary visual effect that can be spawned and automatically destroyed after a delay 
 */
UCLASS()
class USK_API AEffect : public AActor
{
    GENERATED_BODY()

public:
	/**
	 * @brief The delay (in seconds) before the effect is deactivated 
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Effect|Destruction")
	float DeactivateDelay = 0.0f;

	/**
	 * @brief The delay (in seconds) after the deactivate process and before the actor is destroyed  
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Effect|Destruction")
	float DestroyDelay = 1.0f;

	/**
	 * @brief Create a new instance of the AEffect actor
	 */
	AEffect();
	
protected:
	/**
	 * @brief Overridable native event for when play begins for this actor
	 */
	virtual void BeginPlay() override;

private:
	/**
	 * @brief Deactivate the effect
	 */
	void DeactivateEffect();

	/**
	 * @brief Destroy the actor
	 */
	void DestroyEffect();
};