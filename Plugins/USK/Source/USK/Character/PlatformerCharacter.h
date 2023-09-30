// Created by Henry Jooste

#pragma once

#include "USKCharacter.h"
#include "PlatformerCharacter.generated.h"

/**
 * @brief Base character that can be used for 3D platformer games
 */
UCLASS()
class USK_API APlatformerCharacter : public AUSKCharacter
{
	GENERATED_BODY()
	
	/**
	 * @brief The spring arm component responsible for controlling the distance of the camera
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character",
		meta=(AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

public:
	/**
	 * @brief Create a new instance of the APlatformerCharacter actor
	 */
	APlatformerCharacter();
	
	/**
	 * @brief Get the spring arm component of the character
	 * @return The spring arm component responsible for controlling the distance of the camera
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Character|Camera")
	USpringArmComponent* GetSpringArmComponent() const;

protected:
	/**
	 * @brief Length of the spring arm component
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Character|Camera")
	float TargetArmLength = 350.0f;

	/**
	 * @brief The multiplier applied to the spring arm component when the character is moving
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Character|Camera")
	float ArmLengthMultiplier = 0.4f;

	/**
	 * @brief The speed used when adjusting the camera distance
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Character|Camera")
	float CameraAdjustmentSpeed = 3.0f;

	/**
	 * @brief Overridable native event for when play begins for this actor
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Event called every frame, if ticking is enabled
	 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
	 */
	virtual void Tick(float DeltaSeconds) override;

private:
	/**
	 * @brief The current arm length of the spring arm component
	 */
	float CurrentArmLength;

	/**
	 * @brief Adjust the camera position
	 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
	 */
	void AdjustCameraPosition(const float DeltaSeconds);
};
