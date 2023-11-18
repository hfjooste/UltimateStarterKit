﻿// Created by Henry Jooste

#pragma once

#include "CameraPerspective.h"
#include "ShadowDecal.h"
#include "InputActionValue.h"
#include "NiagaraCommon.h"
#include "Camera/CameraShakeBase.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "USK/Weapons/Weapon.h"
#include "USKCharacter.generated.h"

class UStatsComponent;
class UInteractTrigger;
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
	 * @brief Event used to notify other classes when the weapon is updated
	 * @param Weapon The current weapon used by the character
	 * @param Ammo The amount of ammo remaining
	 * @param ReloadAmmo The amount of ammo that can be used to reload the weapon
	 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCurrentWeaponUpdated, AWeapon*, Weapon, int, Ammo, int, ReloadAmmo);

	/**
	 * @brief The camera used by the character
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character",
		meta=(AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/**
	 * @brief The spring arm component responsible for controlling the distance of the camera
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character",
		meta=(AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	/**
	 * @brief The timeline component used for smooth crouching
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character",
		meta=(AllowPrivateAccess = "true"))
	class UTimelineComponent* CrouchTimeline;

	/**
	 * @brief The timeline component used for aiming
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character",
		meta=(AllowPrivateAccess = "true"))
	class UTimelineComponent* AimTimeline;

public:
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
	 * @brief The sprint input action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Input")
	UInputAction* SprintAction;

	/**
	 * @brief The fire weapon input action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Input")
	UInputAction* FireWeaponAction;

	/**
	 * @brief The aim down sights input action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Input")
	UInputAction* AimAction;

	/**
	 * @brief The equip next weapon input action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Input")
	UInputAction* EquipNextWeaponAction;

	/**
	 * @brief The equip previous weapon input action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Input")
	UInputAction* EquipPreviousWeaponAction;

	/**
	 * @brief The reload weapon input action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Input")
	UInputAction* ReloadWeaponAction;

	/**
	 * @brief The crouch input action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Input")
	UInputAction* CrouchAction;

    /**
     * @brief The lean input action
     */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Input")
	UInputAction* LeanAction;

	/**
	 * @brief The interact input action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Input")
	UInputAction* InteractAction;

	/**
	 * @brief The camera perspective used by the character
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Camera")
	ECameraPerspective CameraPerspective;

	/**
	 * @brief The name of the head socket used to attach the camera in the first person perspective
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Camera",
		meta=(EditCondition = "CameraPerspective==ECameraPerspective::FirstPerson", EditConditionHides))
	FName HeadSocketName;

	/**
	 * @brief The offset of the camera after attaching to the head
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Camera",
		meta=(EditCondition = "CameraPerspective==ECameraPerspective::FirstPerson", EditConditionHides))
	FVector CameraAttachOffset;

	/**
	 * @brief Length of the spring arm component
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Camera",
		meta=(EditCondition = "CameraPerspective==ECameraPerspective::ThirdPerson", EditConditionHides))
	float TargetArmLength = 350.0f;

	/**
	 * @brief The multiplier applied to the spring arm component when the character is moving
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Camera",
		meta=(EditCondition = "CameraPerspective==ECameraPerspective::ThirdPerson", EditConditionHides))
	float ArmLengthMultiplier = 0.4f;

	/**
	 * @brief The speed used when adjusting the camera distance
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Camera",
		meta=(EditCondition = "CameraPerspective==ECameraPerspective::ThirdPerson", EditConditionHides))
	float CameraAdjustmentSpeed = 3.0f;

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
	 * @brief Can the character perform a high jump while crouching?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump",
        meta = (EditCondition = "bCanCrouch"))
    bool bCanCrouchJump = true;

	/**
	 * @brief The velocity applied to the character when performing a crouch jump
	 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump",
            meta = (EditCondition = "bCanCrouch && bCanCrouchJump", EditConditionHides))
    float CrouchJumpVelocity = 1250.0f;

	/**
	 * @brief Is the character double jumping?
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate Starter Kit|Character|Jump",
		meta = (EditCondition = "CanDoubleJump", EditConditionHides))
	bool IsDoubleJumping;

	/**
	 * @brief Is the character allowed to perform a long jump?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump",
		meta = (EditCondition = "bCanSlide"))
	bool bCanLongJump = true;

	/**
	 * @brief The velocity applied to the character during a long jump
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Jump",
		meta = (EditCondition = "bCanLongJump && bCanSlide", EditConditionHides))
	FVector LongJumpVelocity = FVector(3250.0f, 3250.0f, 800.0f);

	/**
	 * @brief The default movement speed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement")
	float MovementSpeed = 600.0f;

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
	 * @brief Can the character sprint?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement|Sprinting")
	bool bCanSprint = true;

	/**
	 * @brief The movement speed while the character is sprinting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement|Sprinting",
		meta=(EditCondition = "bCanSprint", EditConditionHides))
	float SprintSpeed = 950.0f;

	/**
	 * @brief Does sprinting require stamina?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement|Sprinting",
		meta=(EditCondition = "bCanSprint", EditConditionHides))
	bool bSprintRequiresStamina;

	/**
	 * @brief The name of the stamina stat used for sprinting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement|Sprinting",
		meta=(EditCondition = "bCanSprint && bSprintRequiresStamina", EditConditionHides))
	FName SprintStaminaStatName;

	/**
	 * @brief The amount of stamina used per second while sprinting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement|Sprinting",
		meta=(EditCondition = "bCanSprint && bSprintRequiresStamina", EditConditionHides))
	float SprintStaminaUseRate = 20.0f;

	/**
	 * @brief Can the character crouch?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement|Crouching")
	bool bCanCrouch = true;

	/**
	 * @brief Should the crouch action be held down to crouch?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement|Crouching",
		meta=(EditCondition = "bCanCrouch", EditConditionHides))
	bool bHoldToCrouch = true;

	/**
	 * @brief The movement speed while the character is crouching
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Movement|Crouching",
		meta=(EditCondition = "bCanCrouch", EditConditionHides))
	float CrouchSpeed = 300.0f;

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
     * @brief Can the character lean? 
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Leaning")
    bool bCanLean = true;

    /**
     * @brief The speed used when leaning 
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Leaning",
            meta=(EditCondition = "bCanLean", EditConditionHides))
    float LeanSpeed = 5.0f;

    /**
     * @brief The offset applied to the camera when leaning 
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Leaning",
        meta=(EditCondition = "bCanLean", EditConditionHides))
    float LeanOffset = 50.0f;

    /**
     * @brief The rotation applied to the camera when leaning 
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Leaning",
        meta=(EditCondition = "bCanLean", EditConditionHides))
    float LeanRotation = 25.0f;

	/**
	 * @brief Can the character perform a slide?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Sliding")
	bool bCanSlide = true;

	/**
	 * @brief The movement speed while the character is sliding
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Sliding",
		meta=(EditCondition = "bCanSlide", EditConditionHides))
	float SlideSpeed = 2500.0f;

	/**
	 * @brief Does sliding require the character to sprint?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Sliding",
    		meta=(EditCondition = "bCanSlide && bCanSprint", EditConditionHides))
    bool bSlideRequiresSprinting;

	/**
	 * @brief The minimum movement speed before a slide is allowed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Sliding",
		meta=(EditCondition = "bCanSlide && !bSlideRequiresSprinting", EditConditionHides))
	float SlideMinSpeed = 400.0f;

	/**
	 * @brief The time the character is allowed to slide
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Sliding",
		meta=(EditCondition = "bCanSlide", EditConditionHides))
	float SlidingTime = 0.5f;

	/**
	 * @brief The cooldown after a slide before another slide can be performed
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Sliding",
		meta=(EditCondition = "bCanSlide", EditConditionHides))
	float SlidingCooldown = 0.5f;

	/**
	 * @brief The sound effect played when the character is sliding
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Sliding",
		meta=(EditCondition = "bCanSlide", EditConditionHides))
	TArray<USoundBase*> SlideSoundEffects;

	/**
	 * @brief The maximum amount of weapons that the character can carry
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Weapons")
	int MaxWeapons = 2;

	/**
	 * @brief The default weapon the character will equip on spawn
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Weapons")
	TSubclassOf<AWeapon> DefaultWeaponClass;

	/**
	 * @brief The float curve used for aiming 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Character|Weapons")
	UCurveFloat* AimCurve;

	/**
	 * @brief Event used to notify other classes when the weapon is updated
	 */
	UPROPERTY(BlueprintAssignable, Category = "Ultimate Starter Kit|Character|Weapons|Events")
	FCurrentWeaponUpdated OnCurrentWeaponUpdated;

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
	 * @brief Get the spring arm component of the character
	 * @return The spring arm component responsible for controlling the distance of the camera
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Character|Camera")
	USpringArmComponent* GetSpringArmComponent() const;

	/**
	 * @brief Get the current camera perspective
	 * @return The current camera perspective
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Character|Camera")
	ECameraPerspective GetCameraPerspective() const;

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
	 * @brief Check if the character has a weapon
	 * @return A boolean value indicating if the character has a weapon
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Character|Weapons")
	bool HasWeapon() const;

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

	/**
	 * @brief Get the current lean camera roll
	 * @return The current lean camera roll
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Character|Leaning")
	float GetLeanCameraRoll() const;

	/**
	 * @brief Check if the character is sliding
	 * @return A boolean value indicating if the character is sliding
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Character|Sliding")
	bool IsSliding() const;

	/**
	 * @brief Check if the character is busy ending the slide
	 * @return A boolean value indicating if the character is busy ending the slide
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Character|Sliding")
	bool IsEndingSlide() const;

	/**
	 * @brief Get the current interact trigger
	 * @return The current interact trigger
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ultimate Starter Kit|Character|Interact")
	UInteractTrigger* GetInteractTrigger() const;

	/**
	 * @brief Update the current interact trigger
	 * @param NewInteractTrigger The new interact trigger
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Character|Interact")
	void UpdateInteractTrigger(UInteractTrigger* NewInteractTrigger);

	/**
	 * @brief Called when the current weapon is updated
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Character|Weapons")
	void OnWeaponUpdated();

	/**
	 * @brief Called when a new weapon is equipped for the first time
	 * @param Weapon The new weapon that was equipped
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Character|Weapons")
	void OnNewWeaponEquipped(AWeapon* Weapon);

	/**
	 * @brief Check if the character is aiming
	 * @return A boolean value indicating if the character is aiming
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Character|Weapons")
	bool IsAiming() const;

protected:
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
	 * @brief Equip the next weapon in the list of available weapons
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Character|Weapons")
	void EquipNextWeapon();

	/**
	 * @brief Equip the previous weapon in the list of available weapons
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|Character|Weapons")
	void EquipPreviousWeapon();

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
	void UpdateCharacterMeshLocationWhileCrouching(float SizeDifference);

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
	 * @brief A reference to the current weapons
	 */
	UPROPERTY()
	TArray<AWeapon*> Weapons;

	/**
	 * @brief The current interact trigger that the character is overlapping
	 */
	UPROPERTY()
	UInteractTrigger* InteractTrigger;

	/**
	 * @brief A reference to the stats component
	 */
	UPROPERTY()
	UStatsComponent* StatsComponent;

	/**
	 * @brief The current arm length of the spring arm component
	 */
	float CurrentArmLength;

	/**
	 * @brief The default location of the character mesh
	 */
	FVector DefaultMeshLocation;
	
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
	 * @brief The default camera location
	 */
	FVector DefaultCameraLocation;

	/**
	 * @brief The target camera lean offset
	 */
	FVector TargetLeanCameraOffset;

	/**
	 * @brief The target camera lean roll
	 */
	float TargetLeanCameraRoll;

	/**
	 * @brief The current camera lean roll
	 */
	float CurrentLeanCameraRoll;

	/**
	 * @brief Is the character sprinting?
	 */
	bool bIsSprinting;

	/**
	 * @brief Is sprinting queued?
	 */
	bool bSprintQueued;

	/**
	 * @brief Is the character sliding?
	 */
	bool bIsSliding;

	/**
	 * @brief The amount of time remaining for the current slide
	 */
	float CurrentSlidingTime;

	/**
	 * @brief The amount of time remaining for the slide cooldown
	 */
	float CurrentSlidingCooldown;

	/**
	 * @brief The direction of the current slide
	 */
	FVector SlideDirection;

	/**
	 * @brief Should crouching be stopped after completing a slide?
	 */
	bool bStopCrouchingAfterSliding;

	/**
	 * @brief Is the character busy ending the slide?
	 */
	bool bIsEndingSlide;

	/**
	 * @brief The index of the equipped weapon
	 */
	int CurrentWeaponIndex = -1;

	/**
	 * @brief Is the character currently aiming?
	 */
	bool bIsAiming;

	/**
	 * @brief The default camera FOV while not aiming
	 */
	float DefaultCameraFov;

	/**
	 * @brief Event used to smoothly move the weapon while aiming
	 */
	FOnTimelineFloat AimTimelineUpdateEvent;

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
	 * @brief Reset the coyote jump values
	 */
	UFUNCTION()
	void ResetCoyoteJump();

	/**
	 * @brief Stop crouching
	 */
	void StopCrouchingInternal();

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

	/**
	 * @brief Start/Stop leaning
	 * @param Input The input action containing the input values
	 */
	UFUNCTION()
    void Lean(const FInputActionValue& Input);

	/**
	 * @brief Update the leaning of the character
	 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
	 */
	void UpdateLeaning(const float DeltaSeconds);

	/**
	 * @brief Try to start sprinting by checking the character states
	 */
	UFUNCTION()
	void Sprint();

	/**
	 * @brief Start sprinting
	 */
	UFUNCTION()
	void StartSprinting();

	/**
	 * @brief Stop sprinting
	 */
	UFUNCTION()
	void StopSprinting();

	/**
	 * @brief Update the stamina of the character while sprinting
	 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
	 */
	void UpdateStaminaWhileSprinting(const float DeltaSeconds);

	/**
	 * @brief Start sliding
	 */
	void StartSliding();

	/**
	 * @brief Stop sliding
	 */
	void StopSliding();

	/**
	 * @brief Update the character state while sliding
	 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
	 */
	void UpdateSliding(const float DeltaSeconds);

	/**
	 * @brief Update the current movement speed of the character
	 */
	void UpdateMovementSpeed() const;

	/**
	 * @brief Check if the character can perform a long jump
	 * @return A boolean value indicating if the character can perform a long jump
	 */
	bool CanLongJump() const;

	/**
	 * @brief Perform a long jump
	 */
	void PerformLongJump();

	/**
	 * @brief Interact with the current interact trigger
	 */
	void Interact();

	/**
	 * @brief Called when the current weapon's ammo is updated
	 * @param Weapon The current weapon used by the character
	 * @param Ammo The amount of ammo remaining
	 * @param ReloadAmmo The amount of ammo that can be used to reload the weapon
	 */
	UFUNCTION()
	void OnWeaponAmmoUpdated(AWeapon* Weapon, int Ammo, int ReloadAmmo);

	/**
	 * @brief Notify other classes that the weapon has been updated
	 */
	void NotifyWeaponUpdated();

	/**
	 * @brief Update the current weapon index
	 * @param EquipNextWeapon Should the next weapon be equipped?
	 */
	void UpdateWeaponIndex(const bool EquipNextWeapon);

	/**
	 * @brief Reload the current weapon
	 */
	UFUNCTION()
	void ReloadWeapon();

	/**
	 * @brief Start aiming with the current weapon
	 */
	UFUNCTION()
	void StartAiming();

	/**
	 * @brief Stop aiming with the current weapon
	 */
	UFUNCTION()
	void StopAiming();

	/**
	 * @brief Called after the aim timeline is updated
	 */
	UFUNCTION()
	void OnAimTimelineUpdated(float Value);
};