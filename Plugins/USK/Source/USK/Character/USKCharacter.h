// Created by Henry Jooste

#pragma once

#include "ShadowDecal.h"
#include "InputActionValue.h"
#include "NiagaraCommon.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "USK/Weapons/Weapon.h"
#include "USKCharacter.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * @brief Base character class
 */
UCLASS()
class USK_API AUSKCharacter : public ACharacter
{
	GENERATED_BODY()

	/**
	 * @brief The camera used by the character
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character",
		meta=(AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/**
	 * @brief The timeline component used for smooth crouching
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character",
		meta=(AllowPrivateAccess = "true"))
	class UTimelineComponent* CrouchTimeline;

public:
	/**
	 * @brief Is the character double jumping?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Jump")
	bool IsDoubleJumping;

	/**
	 * @brief Create a new instance of the AUSKCharacter actor
	 */
	AUSKCharacter();

	/**
	 * @brief Get the camera used by the character
	 * @return The camera used by the character
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Character|Camera")
	UCameraComponent* GetCameraComponent() const;

	/**
	 * @brief Set the current weapon used by the character
	 * @param NewWeapon The new weapon
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Character|Weapons")
	void SetWeapon(AWeapon* NewWeapon);

	/**
	 * @brief Get the current weapon used by the character
	 * @return The current weapon used by the character
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Character|Weapons")
	AWeapon* GetWeapon() const;

	/**
	 * @brief Check if the character is crouching 
	 * @return A boolean value indicating if the character is crouching
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Character|Movement")
	bool IsCrouching() const;

	/**
	 * @brief Check if the character is busy ending the crouch
	 * @return A boolean value indicating if the character is busy ending the crouch
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Character|Movement")
	bool IsEndingCrouch() const;

	/**
	 * @brief Check if the character is stomping
	 * @return A boolean value indicating if the character is stomping
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Character|Movement")
	bool IsStomping() const;

	/**
	 * @brief Check if the character is starting to stomp
	 * @return A boolean value indicating if the character is starting to stomp
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Character|Movement")
	bool IsStompStarting() const;

protected:
	/**
	 * @brief The input mapping context used by the character
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Input")
	UInputMappingContext* InputMappingContext;

	/**
	 * @brief The move input action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Input")
	UInputAction* MoveAction;

	/**
	 * @brief The camera rotation input action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Input")
	UInputAction* LookAroundAction;

	/**
	 * @brief The jump input action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Input")
	UInputAction* JumpAction;

	/**
	 * @brief The fire weapon input action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Input")
	UInputAction* FireWeaponAction;

	/**
	 * @brief The crouch input action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Input")
	UInputAction* CrouchAction;

	/**
	 * @brief The shadow decal class used to draw a shadow below the character while in the air
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump|Effects")
	TSubclassOf<AShadowDecal> ShadowDecalClass;

	/**
	 * @brief An array of sound effects played when jumping
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump|Effects")
	TArray<USoundBase*> JumpSoundEffects;

	/**
	 * @brief The particle effects spawned when jumping
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump|Effects")
	UNiagaraSystem* JumpParticleFx;

	/**
	 * @brief The offset applied to the location of the jump particles when spawning
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump|Effects")
	FVector JumpParticleFxSpawnOffset;

	/**
	 * @brief An array of sound effects played when landing
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump|Effects")
	TArray<USoundBase*> LandedSoundEffects;

	/**
	 * @brief The particle effects spawned when landing
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump|Effects")
	UNiagaraSystem* LandParticleFx;

	/**
	 * @brief The offset applied to the location of the land particles when spawning
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump|Effects")
	FVector LandParticleFxSpawnOffset;

	/**
	 * @brief Does the character support variable jump height?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump")
	bool VariableJumpHeight = true;

	/**
	 * @brief The amount of time to hold the jump button to reach the max height
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump",
		meta = (EditCondition = "VariableJumpHeight"))
	float VariableJumpHeightMaxHoldTime = 0.3f;

	/**
	 * @brief The velocity applied to the character when jumping
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump")
	float JumpVelocity = 500.0f;

	/**
	 * @brief The amount of lateral movement control available to the character while in the air
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump")
	float AirControl = 1000.0f;

	/**
	 * @brief The amount of friction to apply to lateral air movement when falling
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump")
	float FallingFriction = 3.5f;

	/**
	 * @brief The amount of gravity applied to the character
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump")
	float Gravity = 2.0f;

	/**
	 * @brief Can the character perform a double jump?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump")
	bool CanDoubleJump = true;

	/**
	 * @brief Does the character support coyote time when trying to jump?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump")
	bool CanCoyoteJump = true;

	/**
	 * @brief The amount of coyote time for the character
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump",
		meta = (EditCondition = "CanCoyoteJump", EditConditionHides))
	float CoyoteJumpTime = 0.375f;

	/**
	 * @brief The velocity applied to the character when performing a coyote jump
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump",
		meta = (EditCondition = "CanCoyoteJump", EditConditionHides))
	float CoyoteJumpVelocity = 700.0f;

	/**
	 * @brief Can the character perform a high jump directly after landing from a stomp?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump",
    		meta = (EditCondition = "bCanStomp"))
    bool bCanStompJump = true;

	/**
	 * @brief The duration after the stomp that the character can perform the stomp jump
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump",
			meta = (EditCondition = "bCanStomp && bCanStompJump", EditConditionHides))
    float StompJumpDuration = 0.35f;

	/**
	 * @brief The velocity applied to the character when performing a stomp jump
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump",
			meta = (EditCondition = "bCanStomp && bCanStompJump", EditConditionHides))
	float StompJumpVelocity = 1250.0f;

	/**
	 * @brief Friction coefficient applied when braking
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement")
	float BrakingFriction = 10.0f;

	/**
	 * @brief The rate of change of velocity
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement")
	float MaxAcceleration = 2500.0f;

	/**
	 * @brief Can the character crouch?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement|Crouching")
	bool bCanCrouch = true;

	/**
	 * @brief The float curve used for smooth crouching 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement|Crouching",
	    meta=(EditCondition = "bCanCrouch", EditConditionHides))
	UCurveFloat* CrouchCurve;

	/**
	 * @brief Can the character perform a stomp?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement|Stomping")
	bool bCanStomp = true;

	/**
	 * @brief The minimum air time before the character can perform a stomp
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement|Stomping",
		meta=(EditCondition = "bCanStomp", EditConditionHides))
	float MinAirTimeBeforeStomping = 0.3f;

	/**
	 * @brief The velocity applied to the character after performing a stomp
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement|Stomping",
		meta=(EditCondition = "bCanStomp", EditConditionHides))
	float StompVelocity = -5000.0f;

	/**
	 * @brief The amount of time the character will be in zero gravity after performing a stomp
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement|Stomping",
    		meta=(EditCondition = "bCanStomp", EditConditionHides))
	float StompZeroGravityDuration = 0.5f;

	/**
	 * @brief The velocity applied to the character when landing after performing a stomp
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement|Stomping",
			meta=(EditCondition = "bCanStomp", EditConditionHides))
	float StompLandVelocity = 750.0f;

	/**
	 * @brief The camera shake applied when performing a stomp
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement|Stomping",
		meta=(EditCondition = "bCanStomp", EditConditionHides))
	TSubclassOf<UCameraShakeBase> StompCameraShake;

	/**
	 * @brief The default weapon the character will equip on spawn
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Weapons")
	TSubclassOf<AWeapon> DefaultWeaponClass;

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

	/**
	 * @brief Start firing the current weapon
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Character|Weapons")
	void StartFiringWeapon();

	/**
	 * @brief Stop firing the current weapon
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Character|Weapons")
	void StopFiringWeapon();

	/**
	 * @brief Start crouching
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Character|Movement")
	void StartCrouching();

	/**
	 * @brief Stop crouching
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Character|Movement")
	void StopCrouching();

	/**
	 * @brief Update the character mesh location while crouching
	 * @param SizeDifference The difference between the original capsule size and the crouched capsule size
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Character|Movement")
	virtual void UpdateCharacterMeshLocationWhileCrouching(float SizeDifference);

	/**
	 * @brief Start the stomping ability
	 */
	void StartStomping();

	/**
	 * @brief Stop the stomping ability
	 */
	void StopStomping();

	/**
	 * @brief Apply the stomp velocity to the character
	 */
	void ApplyStompVelocity();

private:
	/**
	 * @brief A reference to the current weapon
	 */
	UPROPERTY()
	AWeapon* Weapon;
	
	/**
	 * @brief Can the character perform a coyote jump?
	 */
	bool CanPerformCoyoteJump;

	/**
	 * @brief Was a coyote jump performed?
	 */
	bool CoyoteJumpPerformed;

	/**
	 * @brief Is the character crouching?
	 */
	bool bIsCrouching;

	/**
	 * @brief Is the character busy ending the crouch?
	 */
	bool bIsEndingCrouch;

	/**
	 * @brief Is the character stomping?
	 */
	bool bIsStomping;

	/**
	 * @brief Is the character allowed to perform a stomp jump?
	 */
	bool bIsStompJumpAllowed;

	/**
	 * @brief The default movement speed of the character
	 */
	float DefaultMovementSpeed;

	/**
	 * @brief The default capsule size of the character
	 */
	float DefaultCapsuleSize;

	/**
	 * @brief Event used to smoothly adjust the capsule size during crouching
	 */
	FOnTimelineFloat CrouchTimelineUpdateEvent;

	/**
	 * @brief The current amount of time the character is in the air
	 */
	float AirTime;

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
	 * @brief Reset the coyote jump values
	 */
	UFUNCTION()
	void ResetCoyoteJump();

	/**
	 * @brief Called after the crouch timeline is updated
	 */
	UFUNCTION()
	void OnCrouchTimelineUpdated(float Value);

	/**
	 * @brief Perform a stomp after the zero gravity duration has elapsed
	 */
	UFUNCTION()
	void StompAfterZeroGravity();

	/**
	 * @brief Reset the stomping values
	 */
	UFUNCTION()
	void ResetStomping();

	/**
	 * @brief Reset the stomp jump values
	 */
	UFUNCTION()
	void ResetStompJump();
};