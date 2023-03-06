// Created by Henry Jooste

#pragma once

#include "ShadowDecal.h"
#include "InputActionValue.h"
#include "NiagaraCommon.h"
#include "GameFramework/Character.h"
#include "PlatformerCharacter.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * @brief Base character that can be used for 3D platformer games
 */
UCLASS()
class USK_API APlatformerCharacter : public ACharacter
{
	GENERATED_BODY()

	/**
	 * @brief The spring arm component responsible for controlling the distance of the camera
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ultimate Starter Kit|Platformer Character",
		meta=(AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	/**
	 * @brief The camera used by the character
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ultimate Starter Kit|Platformer Character",
		meta=(AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

public:
	/**
	 * @brief Is the character double jumping?
	 */
	bool IsDoubleJumping;

	/**
	 * @brief Create a new instance of the APlatformerCharacter actor
	 */
	APlatformerCharacter();

	/**
	 * @brief Get the spring arm component of the character
	 * @return The spring arm component responsible for controlling the distance of the camera
	 */
	USpringArmComponent* GetSpringArmComponent() const { return SpringArmComponent; }

	/**
	 * @brief Get the camera used by the character
	 * @return The camera used by the character
	 */
	UCameraComponent* GetCameraComponent() const { return CameraComponent; }

protected:
	/**
	 * @brief The input mapping context used by the player
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Input")
	UInputMappingContext* InputMappingContext;

	/**
	 * @brief The move input action
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Input")
	UInputAction* MoveAction;

	/**
	 * @brief The camera rotation input action
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Input")
	UInputAction* LookAroundAction;

	/**
	 * @brief The jump input action
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Input")
	UInputAction* JumpAction;

	/**
	 * @brief The shadow decal class used to draw a shadow below the character while in the air
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Jump|Effects")
	TSubclassOf<AShadowDecal> ShadowDecalClass;

	/**
	 * @brief An array of sound effects played when jumping
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Jump|Effects")
	TArray<USoundBase*> JumpSoundEffects;

	/**
	 * @brief The particle effects spawned when jumping
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Platformer Character|Jump|Effects")
	UNiagaraSystem* JumpParticleFx;

	/**
	 * @brief The offset applied to the location of the jump particles when spawning
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Platformer Character|Jump|Effects")
	FVector JumpParticleFxSpawnOffset;

	/**
	 * @brief An array of sound effects played when landing
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Jump|Effects")
	TArray<USoundBase*> LandedSoundEffects;

	/**
	 * @brief The particle effects spawned when landing
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Platformer Character|Jump|Effects")
	UNiagaraSystem* LandParticleFx;

	/**
	 * @brief The offset applied to the location of the land particles when spawning
	 */
	UPROPERTY(EditAnywhere, Category = "Ultimate Starter Kit|Platformer Character|Jump|Effects")
	FVector LandParticleFxSpawnOffset;

	/**
	 * @brief Does the character support variable jump height?
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Jump")
	bool VariableJumpHeight = true;

	/**
	 * @brief The amount of time to hold the jump button to reach the max height
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Jump",
		meta = (EditCondition = "VariableJumpHeight"))
	float VariableJumpHeightMaxHoldTime = 0.3f;

	/**
	 * @brief The velocity applied to the character when jumping
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Jump")
	float JumpVelocity = 500.0f;

	/**
	 * @brief The amount of lateral movement control available to the character while in the air
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Jump")
	float AirControl = 1000.0f;

	/**
	 * @brief The amount of friction to apply to lateral air movement when falling
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Jump")
	float FallingFriction = 3.5f;

	/**
	 * @brief The amount of gravity applied to the character
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Jump")
	float Gravity = 2.0f;

	/**
	 * @brief Can the character perform a double jump?
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Jump")
	bool CanDoubleJump = true;

	/**
	 * @brief Does the character support coyote time when trying to jump?
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Jump")
	bool CanCoyoteJump = true;

	/**
	 * @brief The amount of coyote time for the character
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Jump",
		meta = (EditCondition = "CanCoyoteJump"))
	float CoyoteJumpTime = 0.375f;

	/**
	 * @brief The velocity applied to the character when performing a coyote jump
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Jump",
		meta = (EditCondition = "CanCoyoteJump"))
	float CoyoteJumpVelocity = 700.0f;

	/**
	 * @brief Friction coefficient applied when braking
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Movement")
	float BrakingFriction = 10.0f;

	/**
	 * @brief The rate of change of velocity
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Movement")
	float MaxAcceleration = 2500.0f;

	/**
	 * @brief Length of the spring arm component
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Camera")
	float TargetArmLength = 350.0f;

	/**
	 * @brief The multiplier applied to the spring arm component when the character is moving
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Camera")
	float ArmLengthMultiplier = 0.4f;

	/**
	 * @brief The speed used when adjusting the camera distance
	 */
	UPROPERTY(EditAnywhere, Category="Ultimate Starter Kit|Platformer Character|Camera")
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

	/**
	 * @brief Tell client that the Pawn is begin restarted
	 */
	virtual void PawnClientRestart() override;

	/**
	 * @brief Allows a Pawn to set up custom input bindings
	 * @param PlayerInputComponent The component that enables an Actor to bind various forms of input events
	 */
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/**
	 * @brief Called upon landing when falling, to perform actions based on the Hit result
	 * @param Hit Result describing the landing that resulted in a valid landing spot
	 */
	virtual void Landed(const FHitResult& Hit) override;

	/**
	 * @brief Called from CharacterMovementComponent to notify the character that the movement mode has changed
	 * @param PrevMovementMode Movement mode before the change
	 * @param PreviousCustomMode Custom mode before the change (applicable if PrevMovementMode is Custom)
	 */
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;

	/**
	 * @brief Make the character jump on the next update
	 */
	virtual void Jump() override;

private:
	/**
	 * @brief The current arm length of the spring arm component
	 */
	float CurrentArmLength;

	/**
	 * @brief Can the character perform a coyote jump?
	 */
	bool CanPerformCoyoteJump;

	/**
	 * @brief Was a coyote jump performed?
	 */
	bool CoyoteJumpPerformed;

	/**
	 * @brief Move the character
	 * @param Input The input action containing the input values
	 */
	void MoveCharacter(const FInputActionValue& Input);

	/**
	 * @brief Rotate the camera
	 * @param Input The input action containing the input values
	 */
	void RotateCamera(const FInputActionValue& Input);

	/**
	 * @brief Adjust the camera position
	 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
	 */
	void AdjustCameraPosition(const float DeltaSeconds);

	/**
	 * @brief Perform a coyote jump
	 */
	void PerformCoyoteJump();

	/**
	 * @brief Reset the coyote jump values
	 */
	UFUNCTION()
	void ResetCoyoteJump();
};
