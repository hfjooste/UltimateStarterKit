// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USKPostProcessActor.generated.h"

class UUSKGameInstance;

/**
 * @brief Actor responsible for post processing
 */
UCLASS()
class USK_API AUSKPostProcessActor : public AActor
{
	GENERATED_BODY()

	/**
	 * @brief The component responsible for the post processing
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Post Processing",
		meta=(AllowPrivateAccess = "true"))
	class UPostProcessComponent* PostProcessComponent;
	
public:
	/**
	 * @brief Constructor for the post process actor
	 */
	AUSKPostProcessActor();

	/**
	 * @brief Apply the motion blur setting
	 * @param MotionBlurAmount The amount of motion blur to apply
	 */
	UFUNCTION(BlueprintCallable)
	void ApplyMotionBlurSettings(float MotionBlurAmount) const;

protected:
	/**
	 * @brief Overridable native event for when play begins for this actor
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Overridable native event for when the actor is being destroyed
	 */
	virtual void BeginDestroy() override;

private:
	/**
	 * @brief A reference to the game instance
	 */
	UPROPERTY()
	UUSKGameInstance* GameInstance;
};
