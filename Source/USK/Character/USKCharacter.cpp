// Created by Henry Jooste

#include "USKCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "NiagaraFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Curves/CurveFloat.h"
#include "USK/Audio/AudioUtils.h"
#include "USK/Components/InteractTrigger.h"
#include "USK/Data/StatsComponent.h"
#include "USK/Logger/Log.h"
#include "USK/Weapons/WeaponUtils.h"

/**
 * @brief Create a new instance of the AUSKCharacter actor
 */
AUSKCharacter::AUSKCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CrouchTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Crouch Timeline"));
	ProneTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Prone Timeline"));
	AimTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Aim Timeline"));
	LookAtCenterTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Look At Center Timeline"));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	SpringArmComponent->SetupAttachment(GetCapsuleComponent(), "head");
	SpringArmComponent->bUsePawnControlRotation = true;
	
	GetCameraComponent()->SetupAttachment(GetMesh());
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

/**
 * @brief Overridable native event for when play begins for this actor
 */
void AUSKCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	USK_LOG_TRACE("Initializing references");
	PlayerController = dynamic_cast<APlayerController*>(GetController());
	
	USK_LOG_TRACE("Initializing character movement");
	GetCharacterMovement()->JumpZVelocity = JumpVelocity;
	GetCharacterMovement()->AirControl = AirControl;
	GetCharacterMovement()->FallingLateralFriction = FallingFriction;
	GetCharacterMovement()->GravityScale = Gravity;
	GetCharacterMovement()->BrakingFriction = BrakingFriction;
	GetCharacterMovement()->MaxAcceleration = MaxAcceleration;

	InitializeCameraPerspective();

	USK_LOG_TRACE("Initializing character jumping");
	JumpMaxCount = 1;
	JumpMaxHoldTime = VariableJumpHeight ? VariableJumpHeightMaxHoldTime : 0.0f;

	if (ShadowDecalClass != nullptr)
	{
		USK_LOG_TRACE("Adding shadow decal");
		AActor* ShadowDecalActor = GetWorld()->SpawnActor(ShadowDecalClass);
		dynamic_cast<AShadowDecal*>(ShadowDecalActor)->Initialize(this);
	}

	if (IsValid(DefaultWeaponClass))
	{
		USK_LOG_TRACE("Equiping default weapon");
		UWeaponUtils::EquipWeapon(this, DefaultWeaponClass);
	}

	DefaultCapsuleHalfHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	DefaultCapsuleRadius = GetCapsuleComponent()->GetUnscaledCapsuleRadius();
	if (IsValid(CrouchCurve))
	{
		CrouchTimelineUpdateEvent.BindUFunction(this, FName("OnCrouchTimelineUpdated"));
		CrouchTimeline->AddInterpFloat(CrouchCurve, CrouchTimelineUpdateEvent);
		CrouchTimeline->SetLooping(false);
	}

	if (IsValid(ProneCurve))
	{
		ProneTimelineUpdateEvent.BindUFunction(this, FName("OnProneTimelineUpdated"));
		ProneTimeline->AddInterpFloat(ProneCurve, ProneTimelineUpdateEvent);
		ProneTimeline->SetLooping(false);
	}

	if (IsValid(AimCurve))
	{
		AimTimelineUpdateEvent.BindUFunction(this, FName("OnAimTimelineUpdated"));
		AimTimeline->AddInterpFloat(AimCurve, AimTimelineUpdateEvent);
		AimTimeline->SetLooping(false);
	}

	if (IsValid(LookAtCenterCurve))
	{
		LookAtCenterTimelineUpdateEvent.BindUFunction(this, FName("OnLookAtCenterTimelineUpdated"));
		LookAtCenterTimeline->AddInterpFloat(LookAtCenterCurve, LookAtCenterTimelineUpdateEvent);
		LookAtCenterTimeline->SetLooping(false);
	}

	DefaultMeshLocation = GetMesh()->GetRelativeLocation();
	DefaultCameraFov = GetCameraComponent()->FieldOfView;
	StatsComponent = dynamic_cast<UStatsComponent*>(GetComponentByClass(UStatsComponent::StaticClass()));	
	NotifyWeaponUpdated();
}

/**
 * @brief Event called every frame, if ticking is enabled
 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
 */
void AUSKCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AirTime = GetCharacterMovement()->IsFalling() ? AirTime + DeltaSeconds : 0.0f;
	UpdateCamera(DeltaSeconds);
    UpdateLeaning(DeltaSeconds);
	UpdateSliding(DeltaSeconds);
	UpdateProning();
	UpdateMovement(DeltaSeconds);
	UpdateStaminaWhileSprinting(DeltaSeconds);
	UpdateLookAtCenterActorRotation();
	CalculateWeaponSway(DeltaSeconds);
}

/**
 * @brief Tell client that the Pawn is begin restarted
 */
void AUSKCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	USK_LOG_TRACE("Adding input mapping context");
	const APlayerController* InputPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(InputPlayerController->GetLocalPlayer());
	Subsystem->RemoveMappingContext(InputMappingContext);
	Subsystem->AddMappingContext(InputMappingContext, 0);
}

/**
 * @brief Allows a Pawn to set up custom input bindings
 * @param PlayerInputComponent The component that enables an Actor to bind various forms of input events
 */
void AUSKCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	USK_LOG_TRACE("Setting up input bindings");

	UEnhancedInputComponent* EnhancedInput = dynamic_cast<UEnhancedInputComponent*>(PlayerInputComponent);
	EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUSKCharacter::MoveCharacter);
	EnhancedInput->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &AUSKCharacter::RotateCamera);
	EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &AUSKCharacter::Jump);
	EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &AUSKCharacter::StopJumping);
	EnhancedInput->BindAction(SprintAction, ETriggerEvent::Started, this, &AUSKCharacter::Sprint);
	EnhancedInput->BindAction(SprintAction, ETriggerEvent::Completed, this, &AUSKCharacter::StopSprinting);
	EnhancedInput->BindAction(FireWeaponAction, ETriggerEvent::Started, this, &AUSKCharacter::StartFiringWeapon);
	EnhancedInput->BindAction(FireWeaponAction, ETriggerEvent::Completed, this, &AUSKCharacter::StopFiringWeapon);
	EnhancedInput->BindAction(AimAction, ETriggerEvent::Started, this, &AUSKCharacter::StartAiming);
	EnhancedInput->BindAction(AimAction, ETriggerEvent::Completed, this, &AUSKCharacter::StopAiming);
	EnhancedInput->BindAction(SwitchCameraPerspectiveAction, ETriggerEvent::Started, this, &AUSKCharacter::SwitchCameraPerspective);
	EnhancedInput->BindAction(EquipNextWeaponAction, ETriggerEvent::Started, this, &AUSKCharacter::EquipNextWeapon);
	EnhancedInput->BindAction(EquipPreviousWeaponAction, ETriggerEvent::Started, this, &AUSKCharacter::EquipPreviousWeapon);
	EnhancedInput->BindAction(ReloadWeaponAction, ETriggerEvent::Started, this, &AUSKCharacter::ReloadWeapon);
	EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Started, this, &AUSKCharacter::StartCrouching);
	EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AUSKCharacter::StopCrouching);
	EnhancedInput->BindAction(ProneAction, ETriggerEvent::Started, this, &AUSKCharacter::StartProning);
	EnhancedInput->BindAction(ProneAction, ETriggerEvent::Completed, this, &AUSKCharacter::StopProning);
    EnhancedInput->BindAction(LeanAction, ETriggerEvent::Triggered, this, &AUSKCharacter::Lean);
    EnhancedInput->BindAction(LeanAction, ETriggerEvent::Completed, this, &AUSKCharacter::Lean);
	EnhancedInput->BindAction(InteractAction, ETriggerEvent::Started, this, &AUSKCharacter::Interact);
}

/**
 * @brief Called upon landing when falling, to perform actions based on the Hit result
 * @param Hit Result describing the landing that resulted in a valid landing spot
 */
void AUSKCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	USK_LOG_TRACE("Character Landed");
	JumpMaxCount = 1;
	CoyoteJumpPerformed = false;
	UAudioUtils::PlayRandomSound(this, LandedSoundEffects);

	if (LandParticleFx != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), LandParticleFx,
			Hit.Location + LandParticleFxSpawnOffset);
	}

	StopStomping();
	if (bIsProning)
	{
		ProneTimeline->Play();
		return;
	}
	
	if (bIsCrouching)
	{
		CrouchTimeline->Play();
	}
}

/**
 * @brief Called from CharacterMovementComponent to notify the character that the movement mode has changed
 * @param PrevMovementMode Movement mode before the change
 * @param PreviousCustomMode Custom mode before the change (applicable if PrevMovementMode is Custom)
 */
void AUSKCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);
	USK_LOG_TRACE("Movement mode changed");
	
	if (GetCharacterMovement()->MovementMode != MOVE_Falling)
	{
		return;
	}

	CanPerformCoyoteJump = true;

	USK_LOG_TRACE("Starting latent reset coyote jump action");
	FLatentActionInfo LatentAction;
	LatentAction.Linkage = 0;
	LatentAction.CallbackTarget = this;
	LatentAction.UUID = GetUniqueID();
	LatentAction.ExecutionFunction = "ResetCoyoteJump";
	UKismetSystemLibrary::RetriggerableDelay(GetWorld(), CoyoteJumpTime, LatentAction);
}

/**
 * @brief Get the camera used by the character
 * @return The camera used by the character
 */
UCameraComponent* AUSKCharacter::GetCameraComponent() const
{
	return CameraComponent;
}

/**
 * @brief Get the spring arm component of the character
 * @return The spring arm component responsible for controlling the distance of the camera
 */
USpringArmComponent* AUSKCharacter::GetSpringArmComponent() const
{
	return SpringArmComponent;
}

/**
 * @brief Get the current camera perspective
 * @return The current camera perspective
 */
ECameraPerspective AUSKCharacter::GetCameraPerspective() const
{
	return CameraPerspective;
}

/**
 * @brief Update the current camera perspective
 * @param NewCameraPerspective The new camera perspective
 */
void AUSKCharacter::UpdateCameraPerspective(const ECameraPerspective NewCameraPerspective)
{
	if (CameraPerspective == NewCameraPerspective)
	{
		return;
	}
	
	CameraPerspective = NewCameraPerspective;
	InitializeCameraPerspective();
}

/**
 * @brief Switch the current camera perspective
 */
void AUSKCharacter::SwitchCameraPerspective()
{
	if (!bCanSwitchCameraPerspectives)
	{
		return;
	}
	
	UpdateCameraPerspective(GetCameraPerspective() == ECameraPerspective::FirstPerson
		? ECameraPerspective::ThirdPerson
		: ECameraPerspective::FirstPerson);
}

/**
 * @brief Set the current weapon used by the character
 * @param NewWeapon The new weapon
 */
void AUSKCharacter::SetWeapon(AWeapon* NewWeapon)
{
	if (Weapons.Num() >= MaxWeapons)
	{
		Weapons[CurrentWeaponIndex] = NewWeapon;
		return;
	}

	Weapons.Add(NewWeapon);
	CurrentWeaponIndex = Weapons.Num() - 1;
}

/**
 * @brief Get the current weapon used by the character
 * @return The current weapon used by the character
 */
AWeapon* AUSKCharacter::GetWeapon() const
{
	return HasWeapon() ? Weapons[CurrentWeaponIndex] : nullptr;
}

/**
 * @brief Check if the character has a weapon
 * @return A boolean value indicating if the character has a weapon
 */
bool AUSKCharacter::HasWeapon() const
{
	return Weapons.Num() > 0 && Weapons.Num() > CurrentWeaponIndex;
}

/**
 * @brief Check if the character is crouching 
 * @return A boolean value indicating if the character is crouching
 */
bool AUSKCharacter::IsCrouching() const
{
	return bIsCrouching;
}

/**
 * @brief Check if the character is proning 
 * @return A boolean value indicating if the character is proning
 */
bool AUSKCharacter::IsProning() const
{
	return bIsProning;
}

/**
 * @brief Check if the character is busy ending the crouch
 * @return A boolean value indicating if the character is busy ending the crouch
 */
bool AUSKCharacter::IsEndingCrouch() const
{
	return bIsEndingCrouch;
}

/**
 * @brief Check if the character is busy ending the prone
 * @return A boolean value indicating if the character is busy ending the prone
 */
bool AUSKCharacter::IsEndingProne() const
{
	return bIsEndingProne;
}

/**
 * @brief Check if the character is stomping
 * @return A boolean value indicating if the character is stomping
 */
bool AUSKCharacter::IsStomping() const
{
	return bIsStomping;
}

/**
 * Check if the character is starting to stomp
 * @return A boolean value indicating if the character is starting to stomp
 */
bool AUSKCharacter::IsStompStarting() const
{
	return bIsStomping && FMath::IsNearlyZero(GetCharacterMovement()->GravityScale);
}

/**
 * @brief Get the current lean camera roll
 * @return The current lean camera roll
 */
float AUSKCharacter::GetLeanCameraRoll() const
{
	return CurrentLeanCameraRoll;
}

/**
 * @brief Get the look at center rotation
 * @return The look at center rotation
 */
float AUSKCharacter::GetLookAtCenterRotation() const
{
	if (!ShouldLookAtCenter())
	{
		return 0.0f;
	}
	
	if (!IsValid(PlayerController))
	{
		USK_LOG_WARNING("PlayerController is not valid");
		return 0.0f;
	}

	const FRotator ActorRotation = GetActorRotation();
	const FRotator CameraRotation = PlayerController->PlayerCameraManager->GetCameraRotation();	
	return UKismetMathLibrary::NormalizedDeltaRotator(CameraRotation, ActorRotation).Yaw;
}

/**
 * @brief Check if the character is sliding
 * @return A boolean value indicating if the character is sliding
 */
bool AUSKCharacter::IsSliding() const
{
	return bIsSliding;
}

/**
 * @brief Check if the character is busy ending the slide
 * @return A boolean value indicating if the character is busy ending the slide
 */
bool AUSKCharacter::IsEndingSlide() const
{
	return bIsEndingSlide;
}

/**
 * @brief Get the current interact trigger
 * @return The current interact trigger
 */
UInteractTrigger* AUSKCharacter::GetInteractTrigger() const
{
	return InteractTrigger;
}

/**
 * @brief Update the current interact trigger
 * @param NewInteractTrigger The new interact trigger
 */
void AUSKCharacter::UpdateInteractTrigger(UInteractTrigger* NewInteractTrigger)
{
	if (InteractTrigger == NewInteractTrigger)
	{
		return;
	}
	
	if (IsValid(InteractTrigger))
	{
		InteractTrigger->HideWidget();
	}
	
	InteractTrigger = NewInteractTrigger;
	if (IsValid(InteractTrigger))
	{
		InteractTrigger->ShowWidget();
	}
}

/**
 * @brief Called when the current weapon is updated
 */
void AUSKCharacter::OnWeaponUpdated()
{
	if (Weapons.Num() == 0)
	{
		NotifyWeaponUpdated();
		return;
	}

	AWeapon* Weapon = Weapons[CurrentWeaponIndex];
	if (!IsValid(Weapon))
	{
		NotifyWeaponUpdated();
		return;
	}
	
	NotifyWeaponUpdated();
}

/**
 * @brief Called when a new weapon is equipped for the first time
 * @param Weapon The new weapon that was equipped
 */
void AUSKCharacter::OnNewWeaponEquipped(AWeapon* Weapon)
{
	Weapon->OnWeaponAmmoUpdated.AddDynamic(this, &AUSKCharacter::OnWeaponAmmoUpdated);
	OnCrosshairUpdated.Broadcast(GetCrosshair());
}

/**
 * @brief Check if the character is aiming
 * @return A boolean value indicating if the character is aiming
 */
bool AUSKCharacter::IsAiming() const
{
	return bIsAiming;
}

/**
 * @brief Get the crosshair configuration
 * @return The crosshair configuration
 */
UCrosshairConfig* AUSKCharacter::GetCrosshair() const
{
	const AWeapon* Weapon = GetWeapon();
	return IsValid(Weapon) ? Weapon->Crosshair : DefaultCrosshair;
}

/**
 * @brief Get the current weapon sway rotation
 * @return The current weapon sway rotation
 */
FRotator AUSKCharacter::GetWeaponSway() const
{
	return WeaponSway;
}

/**
 * @brief Make the character jump on the next update
 */
void AUSKCharacter::Jump()
{
	if (bIsStompJumpAllowed)
	{
		Super::Jump();
		LaunchCharacter(FVector(0.0f, 0.0f, StompJumpVelocity), false, true);
		ResetStompJump();
		return;
	}

	if (CanLongJump())
	{
		PerformLongJump();
		return;
	}

	if (bCanCrouchJump && bIsCrouching && !bIsProning)
	{
		StopCrouching();
		Super::Jump();
		LaunchCharacter(FVector(0.0f, 0.0f, CrouchJumpVelocity), false, true);
		return;
	}
	
	if ((!CanJump() && !CanPerformCoyoteJump) || bIsStomping)
	{
		USK_LOG_TRACE("Can't jump");
		return;
	}

	bool WasRegularJump = false;
	if (CanJump())
	{
		WasRegularJump = true;
		Super::Jump();
	}
	else
	{		
		LaunchCharacter(FVector(0.0f, 0.0f, CoyoteJumpVelocity), false, true);
		CoyoteJumpPerformed = true;
		CanPerformCoyoteJump = false;
		USK_LOG_TRACE("Coyote jump performed");
	}

	JumpMaxCount = CanDoubleJump ? 2 : 1;
	IsDoubleJumping = WasRegularJump && (CoyoteJumpPerformed || JumpCurrentCount > 0);
	UAudioUtils::PlayRandomSound(this, JumpSoundEffects);

	if (JumpParticleFx != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), JumpParticleFx,
			GetActorLocation() + JumpParticleFxSpawnOffset);
	}
}

/**
 * @brief Start firing the current weapon
 */
void AUSKCharacter::StartFiringWeapon()
{
	if (Weapons.Num() > 0 && Weapons.Num() > CurrentWeaponIndex && IsValid(Weapons[CurrentWeaponIndex]))
	{
		Weapons[CurrentWeaponIndex]->StartFiring();
	}
}

/**
 * @brief Stop firing the current weapon
 */
void AUSKCharacter::StopFiringWeapon()
{
	if (Weapons.Num() > 0 && Weapons.Num() > CurrentWeaponIndex && IsValid(Weapons[CurrentWeaponIndex]))
	{
		Weapons[CurrentWeaponIndex]->StopFiring();
	}
}

/**
 * @brief Equip the next weapon in the list of available weapons
 */
void AUSKCharacter::EquipNextWeapon()
{
	UpdateWeaponIndex(true);
}

/**
 * @brief Equip the previous weapon in the list of available weapons
 */
void AUSKCharacter::EquipPreviousWeapon()
{
	UpdateWeaponIndex(false);
}

/**
 * @brief Start crouching
 */
void AUSKCharacter::StartCrouching()
{
	if (bIsProning)
	{
		return;
	}
	
	if (bCanStomp && GetCharacterMovement()->IsFalling() && AirTime >= MinAirTimeBeforeStomping)
	{
		StartStomping();
		if (!bHoldToCrouch)
		{
			return;
		}
	}

	if (!bCanCrouch)
	{
		return;
	}

	if (!bHoldToCrouch && bIsCrouching)
	{
		StopCrouchingInternal();
		return;
	}
	
	bIsCrouching = true;
	bIsEndingCrouch = false;
	if (!GetCharacterMovement()->IsFalling())
	{
		CrouchTimeline->Play();
	}

	const bool SlideAllowed = (bSlideRequiresSprinting && bIsSprinting) || (!bSlideRequiresSprinting &&
		UKismetMathLibrary::VSizeXY(GetMovementComponent()->Velocity) >= SlideMinSpeed);
	if (SlideAllowed && !bIsSliding && CurrentSlidingCooldown <= 0.0f && !GetCharacterMovement()->IsFalling())
	{
		StartSliding();
	}
}

/**
 * @brief Stop crouching
 */
void AUSKCharacter::StopCrouching()
{
	if (!bCanCrouch || !bHoldToCrouch || bIsProning)
	{
		return;
	}

	StopCrouchingInternal();
}

/**
 * @brief Start proning
 */
void AUSKCharacter::StartProning()
{
	if (!bCanProne || !bProneAllowed || bIsCrouching)
	{
		return;
	}

	if (!bHoldToProne && bIsProning)
	{
		if (!bCanStandFromProne)
        {
        	bForceStandFromProne = true;
        	return;
        }
		
		StopProningInternal();
		return;
	}
	
	bIsProning = true;
	bIsEndingProne = false;
	bForceStandFromProne = false;
	if (!GetCharacterMovement()->IsFalling())
	{
		ProneTimeline->Play();
	}
}

/**
 * @brief Stop proning
 */
void AUSKCharacter::StopProning()
{
	if (!bIsProning || !bCanProne || !bHoldToProne || bIsCrouching)
	{
		return;
	}

	if (!bCanStandFromProne)
	{
		bForceStandFromProne = true;
		return;
	}

	StopProningInternal();
}

/**
 * @brief Update the character mesh location while crouching
 * @param SizeDifference The difference between the original capsule size and the crouched capsule size
 */
void AUSKCharacter::UpdateCharacterMeshLocationWhileCrouching(float SizeDifference)
{
	GetMesh()->SetRelativeLocation(DefaultMeshLocation + FVector(0.0f, 0.0f, SizeDifference));
}

/**
 * @brief Start the stomping ability
 */
void AUSKCharacter::StartStomping()
{
	bIsStomping = true;
	if (StompZeroGravityDuration <= 0.0f)
	{
		ApplyStompVelocity();
		return;
	}
	
    GetCharacterMovement()->GravityScale = 0.0f;
	const FVector CurrentVelocity = GetCharacterMovement()->Velocity;
	GetCharacterMovement()->Velocity = FVector(CurrentVelocity.X, CurrentVelocity.Y, 0.0f);
	UKismetSystemLibrary::K2_SetTimer(this, "StompAfterZeroGravity", StompZeroGravityDuration, false);
}

/**
 * @brief Stop the stomping ability
 */
void AUSKCharacter::StopStomping()
{
	if (!bIsStomping)
	{
		return;
	}
	
	UKismetSystemLibrary::K2_SetTimer(this, "ResetStomping", StompRecoveryTime, false);
	if (StompLandVelocity > 0.0f)
	{
		LaunchCharacter(FVector(0.0f, 0.0f, StompLandVelocity), false, true);	
	}	
	
	if (IsValid(StompCameraShake))
	{
		UGameplayStatics::PlayWorldCameraShake(GetWorld(), StompCameraShake,
			GetActorLocation(), 1000.0f, 2000.0f, 1.0f);
	}

	if (bCanStompJump && StompJumpDuration > 0.0f)
	{
		bIsStompJumpAllowed = true;
		UKismetSystemLibrary::K2_SetTimer(this, "ResetStompJump", StompJumpDuration, false);
	}
}

/**
 * @brief Apply the stomp velocity to the player
 */
void AUSKCharacter::ApplyStompVelocity()
{
	LaunchCharacter(FVector(0.0f, 0.0f, StompVelocity), true, false);
}

/**
 * @brief Move the character
 * @param Input The input action containing the input values
 */
void AUSKCharacter::MoveCharacter(const FInputActionValue& Input)
{
	if (bIsStomping || bIsSliding)
	{
		return;
	}
	
	const FVector2D InputValue = Input.Get<FVector2D>();
	if (bSmoothMovement)
	{
		TargetMovementInput = InputValue;
		return;
	}

	ApplyMovementInput(InputValue);
}

/**
 * @brief Apply movement to the character
 * @param Input The movement input that should be applied
 */
void AUSKCharacter::ApplyMovementInput(FVector2D Input)
{
	FRotator Rotation = GetControlRotation();
	Rotation.Pitch = 0.0f;
	Rotation.Roll = 0.0f;
	
	const float ProneTraceOffset = ProneSpeed * ProneMoveTraceSizeMultiplier;
	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(Rotation);
	if (!bIsProning || CheckProneAllowedAtLocation(ForwardVector * FVector(Input.Y * ProneTraceOffset)))
	{
		AddMovementInput(ForwardVector, Input.Y);	
	}

	Rotation = GetControlRotation();
	Rotation.Pitch = 0.0f;

	const FVector RightVector = UKismetMathLibrary::GetRightVector(Rotation);
	if (!bIsProning || CheckProneAllowedAtLocation(RightVector * FVector(Input.X * ProneTraceOffset)))
	{
		AddMovementInput(RightVector, Input.X);	
	}
}

/**
 * @brief Rotate the camera
 * @param Input The input action containing the input values
 */
void AUSKCharacter::RotateCamera(const FInputActionValue& Input)
{
	const FVector2D InputValue = Input.Get<FVector2D>();
	if (bSmoothCameraRotation)
    {
		TargetCameraInput = InputValue;
		return;
    }
	
	AddControllerYawInput(InputValue.X);
	AddControllerPitchInput(InputValue.Y);	
}

/**
 * @brief Update the position and rotation of the camera
 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
 */
void AUSKCharacter::UpdateCamera(const float DeltaSeconds)
{
	if (bSmoothCameraRotation)
	{
		CameraInput = FMath::Vector2DInterpTo(CameraInput, TargetCameraInput,
			DeltaSeconds, SmoothCameraRotationSpeed);
		TargetCameraInput = FMath::Vector2DInterpTo(TargetCameraInput, FVector2D::ZeroVector,
			DeltaSeconds, SmoothCameraRotationSpeed);
		AddControllerYawInput(CameraInput.X);
		AddControllerPitchInput(CameraInput.Y);
	}
	
	if (GetCameraPerspective() != ECameraPerspective::ThirdPerson)
	{
		return;
	}

	const float ArmAdjustment = UKismetMathLibrary::VSizeXY(GetMovementComponent()->Velocity) * ArmLengthMultiplier;
	CurrentArmLength = TargetArmLength + ArmAdjustment;
	GetSpringArmComponent()->TargetArmLength = FMath::Lerp(GetSpringArmComponent()->TargetArmLength,
		CurrentArmLength, DeltaSeconds * CameraAdjustmentSpeed);
}

/**
 * @brief Reset the coyote jump values
 */
void AUSKCharacter::ResetCoyoteJump()
{
	USK_LOG_TRACE("Resetting coyote jump");
	CanPerformCoyoteJump = false;
}

/**
 * @brief Stop crouching
 */
void AUSKCharacter::StopCrouchingInternal()
{
	if (bIsSliding)
	{
		bStopCrouchingAfterSliding = true;
		return;
	}
	
	bIsEndingCrouch = true;
	CrouchTimeline->Reverse();

	if (bSprintQueued)
	{
		StartSprinting();
	}
}

/**
 * @brief Stop proning
 */
void AUSKCharacter::StopProningInternal()
{
	bIsEndingProne = true;
	bForceStandFromProne = false;
	ProneTimeline->Reverse();

	if (bSprintQueued)
	{
		StartSprinting();
	}
}

/**
 * @brief Called after the crouch timeline is updated
 */
void AUSKCharacter::OnCrouchTimelineUpdated(float Value)
{
	if (FMath::IsNearlyEqual(Value, 1.0f))
	{
		bIsCrouching = false;
		bIsEndingCrouch = false;
		bIsEndingSlide = false;
	}
	
	const float CapsuleHalfHeight = GetCharacterMovement()->IsFalling()
		? DefaultCapsuleHalfHeight
		: FMath::Lerp(GetCapsuleComponent()->GetUnscaledCapsuleRadius(), DefaultCapsuleHalfHeight, Value);
	GetCapsuleComponent()->SetCapsuleRadius(DefaultCapsuleRadius);
	UpdateCharacterMeshLocationWhileCrouching(DefaultCapsuleHalfHeight - CapsuleHalfHeight);
	GetCapsuleComponent()->SetCapsuleHalfHeight(CapsuleHalfHeight);
}

/**
 * @brief Called after the prone timeline is updated
 */
void AUSKCharacter::OnProneTimelineUpdated(float Value)
{
	if (FMath::IsNearlyEqual(Value, 1.0f))
	{
		bIsProning = false;
		bIsEndingProne = false;
	}
	
	const float CapsuleHalfHeight = GetCharacterMovement()->IsFalling()
		? DefaultCapsuleHalfHeight
		: DefaultCapsuleHalfHeight * Value;
	const float CapsuleRadius = GetCharacterMovement()->IsFalling()
		? DefaultCapsuleRadius
		: DefaultCapsuleRadius * Value;
	GetCapsuleComponent()->SetCapsuleRadius(CapsuleRadius);
	UpdateCharacterMeshLocationWhileCrouching(DefaultCapsuleHalfHeight - CapsuleHalfHeight);
	GetCapsuleComponent()->SetCapsuleHalfHeight(CapsuleHalfHeight);
}

/**
 * @brief Perform a stomp after the zero gravity duration has elapsed
 */
void AUSKCharacter::StompAfterZeroGravity()
{
	GetCharacterMovement()->GravityScale = Gravity;
	ApplyStompVelocity();
}

/**
 * @brief Reset the stomping values
 */
void AUSKCharacter::ResetStomping()
{
	bIsStomping = false;
}

/**
 * @brief Reset the stomp jump values
 */
void AUSKCharacter::ResetStompJump()
{
	bIsStompJumpAllowed = false;
}

/**
 * @brief Start/Stop leaning
 * @param Input The input action containing the input values
 */
void AUSKCharacter::Lean(const FInputActionValue& Input)
{
    if (!bCanLean)
    {
        return;
    }
	
    const float InputValue = Input.Get<float>();
	const float LeanValue = InputValue * LeanOffset;
	TargetLeanCameraOffset = FVector(0.0f,
		GetCameraPerspective() == ECameraPerspective::ThirdPerson ? LeanValue : 0.0f, 0.0f);
    TargetLeanCameraRoll = InputValue * LeanRotation;
}

/**
 * @brief Update the leaning of the character
 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
 */
void AUSKCharacter::UpdateLeaning(const float DeltaSeconds)
{
    if (!bCanLean)
    {
        return;
    }

	const FVector DefaultCameraLocation = GetCameraPerspective() == ECameraPerspective::ThirdPerson
		? FVector::ZeroVector : CameraAttachOffset;
	GetCameraComponent()->SetRelativeLocation(UKismetMathLibrary::VInterpTo(
		GetCameraComponent()->GetRelativeLocation(), DefaultCameraLocation + TargetLeanCameraOffset,
		DeltaSeconds, LeanSpeed));

    AController* CharacterController = GetController();
    const FRotator ControlRotation = CharacterController->GetControlRotation();
	const FRotator NewLeanRotation = UKismetMathLibrary::RInterpTo(ControlRotation,
		FRotator(ControlRotation.Pitch, ControlRotation.Yaw, TargetLeanCameraRoll),
		DeltaSeconds, LeanSpeed);
    CharacterController->SetControlRotation(NewLeanRotation);
	CurrentLeanCameraRoll = NewLeanRotation.Roll;
}

/**
 * @brief Try to start sprinting by checking the character states
 */
void AUSKCharacter::Sprint()
{
	if (!bCanSprint)
	{
		return;
	}

	if (bIsCrouching || bIsProning || bIsAiming)
	{
		bSprintQueued = true;
		return;
	}
	
	StartSprinting();
}

/**
 * @brief Start sprinting
 */
void AUSKCharacter::StartSprinting()
{
	USK_LOG_TRACE("Starting to sprint");
	bIsSprinting = true;
	bSprintQueued = false;
}

/**
 * @brief Stop sprinting
 */
void AUSKCharacter::StopSprinting()
{
	if (!bIsSprinting)
	{
		bSprintQueued = false;
		return;
	}
	
	USK_LOG_TRACE("Stopping sprint");
	bIsSprinting = false;
}

/**
 * @brief Update the stamina of the character while sprinting
 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
 */
void AUSKCharacter::UpdateStaminaWhileSprinting(const float DeltaSeconds)
{
	if (!bIsSprinting || !bSprintRequiresStamina)
	{
		return;
	}

	if (!IsValid(StatsComponent))
	{
		USK_LOG_ERROR("Stats component is not valid");
		return;
	}

	if (StatsComponent->GetValue(SprintStaminaStatName) <= 0.0f)
	{
		USK_LOG_INFO("Stamina empty. Stopping sprint");
		StopSprinting();
		return;
	}

	StatsComponent->Remove(SprintStaminaStatName, SprintStaminaUseRate * DeltaSeconds);
}

/**
 * @brief Start sliding
 */
void AUSKCharacter::StartSliding()
{
	if (!bCanSlide)
	{
		return;
	}
	
	USK_LOG_TRACE("Start sliding");
	bIsSliding = true;
	CurrentSlidingTime = SlidingTime;
	CurrentSlidingCooldown = SlidingCooldown;
	SlideDirection = GetActorForwardVector();
	UAudioUtils::PlayRandomSound(this, SlideSoundEffects);
}

/**
 * @brief Stop sliding
 */
void AUSKCharacter::StopSliding()
{
	USK_LOG_TRACE("Stop sliding");
	CurrentSlidingTime = 0.0f;
	bIsSliding = false;

	if (bIsCrouching && bStopCrouchingAfterSliding)
	{
		bIsEndingSlide = true;
		StopCrouchingInternal();
		bStopCrouchingAfterSliding = false;
	}
}

/**
 * @brief Update the character state while sliding
 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
 */
void AUSKCharacter::UpdateSliding(const float DeltaSeconds)
{
	if (!bIsSliding && CurrentSlidingCooldown <= 0.0f)
	{
		return;
	}

	if (CurrentSlidingTime > 0.0f)
	{
		CurrentSlidingTime -= DeltaSeconds;
		AddMovementInput(SlideDirection, 1.0f, false);
		if (CurrentSlidingTime <= 0.0f)
		{
			StopSliding();
		}
		
		return;
	}

	CurrentSlidingCooldown -= DeltaSeconds;
	if (CurrentSlidingCooldown <= 0.0f)
	{
		StopSliding();
	}
}

/**
 * @brief Update the current movement and speed of the character
 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
 */
void AUSKCharacter::UpdateMovement(const float DeltaSeconds)
{
	if (bSmoothMovement)
	{
		MovementInput = FMath::Vector2DInterpTo(MovementInput, TargetMovementInput,
			DeltaSeconds, SmoothMovementSpeed);
		TargetMovementInput = FMath::Vector2DInterpTo(TargetMovementInput, FVector2D::ZeroVector,
			DeltaSeconds, SmoothMovementSpeed);
		ApplyMovementInput(MovementInput);
	}
	
	if (bIsSliding)
	{
		GetCharacterMovement()->MaxWalkSpeed = SlideSpeed;
		return;
	}

	if (bIsProning)
	{
		GetCharacterMovement()->MaxWalkSpeed = ProneSpeed;
		return;
	}

	if (bIsCrouching)
	{
		GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
		return;
	}

	GetCharacterMovement()->MaxWalkSpeed = bIsSprinting && !bIsAiming ? SprintSpeed : MovementSpeed;
}

/**
 * @brief Check if the character can perform a long jump
 * @return A boolean value indicating if the character can perform a long jump
 */
bool AUSKCharacter::CanLongJump() const
{
	return bCanLongJump && bCanSlide && bIsSliding;
}

/**
 * @brief Perform a long jump
 */
void AUSKCharacter::PerformLongJump()
{
	USK_LOG_TRACE("Performing long jump");

	CurrentSlidingCooldown = 0.0f;
	StopSliding();
	
	Super::Jump();
	const FVector LaunchVelocity = GetActorForwardVector() *
		FVector(LongJumpVelocity.X, LongJumpVelocity.Y, 0.0f) +
		FVector(0.0f, 0.0f, LongJumpVelocity.Z);
	LaunchCharacter(LaunchVelocity, true, true);
	UAudioUtils::PlayRandomSound(this, JumpSoundEffects);

	if (JumpParticleFx != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), JumpParticleFx,
			GetActorLocation() + JumpParticleFxSpawnOffset);
	}
}

/**
 * @brief Interact with the current interact trigger
 */
void AUSKCharacter::Interact()
{
	if (!IsValid(InteractTrigger))
	{
		return;
	}

	InteractTrigger->OnInteracted(this);
}

/**
 * @brief Called when the current weapon's ammo is updated
 * @param Weapon The current weapon used by the character
 * @param Ammo The amount of ammo remaining
 * @param ReloadAmmo The amount of ammo that can be used to reload the weapon
 */
void AUSKCharacter::OnWeaponAmmoUpdated(AWeapon* Weapon, int Ammo, int ReloadAmmo)
{
	if (Weapons.Num() == 0 || Weapons[CurrentWeaponIndex] != Weapon)
	{
		return;
	}
	
	NotifyWeaponUpdated();
}

/**
 * @brief Notify other classes that the weapon has been updated
 */
void AUSKCharacter::NotifyWeaponUpdated()
{	
	AWeapon* Weapon = Weapons.Num() == 0 ? nullptr : Weapons[CurrentWeaponIndex];
	if (!IsValid(Weapon))
	{
		OnCurrentWeaponUpdated.Broadcast(nullptr, 0, 0);
		return;
	}
	
	OnCurrentWeaponUpdated.Broadcast(Weapon, Weapon->GetAmmoRemaining(), Weapon->GetReloadAmmoRemaining());
}

/**
 * @brief Update the current weapon index
 * @param EquipNextWeapon Should the next weapon be equipped?
 */
void AUSKCharacter::UpdateWeaponIndex(const bool EquipNextWeapon)
{
	if (Weapons.Num() <= 1)
	{
		return;
	}

	AWeapon* PreviousWeapon = Weapons[CurrentWeaponIndex];
	if (IsValid(PreviousWeapon))
	{
		PreviousWeapon->Unequip();
	}	
	
	CurrentWeaponIndex = EquipNextWeapon
		? (Weapons.Num() <= CurrentWeaponIndex + 1  ? 0 : CurrentWeaponIndex + 1)
		: (CurrentWeaponIndex == 0 ? Weapons.Num() - 1 : CurrentWeaponIndex - 1);
	Weapons[CurrentWeaponIndex]->Equip(this, false);
	OnCrosshairUpdated.Broadcast(GetCrosshair());
}

/**
 * @brief Reload the current weapon
 */
void AUSKCharacter::ReloadWeapon()
{
	if (Weapons.Num() == 0)
	{
		return;
	}

	AWeapon* Weapon = Weapons[CurrentWeaponIndex];
	if (IsValid(Weapon))
	{
		Weapon->Reload();
	}
}

/**
 * @brief Start aiming with the current weapon
 */
void AUSKCharacter::StartAiming()
{
	const AWeapon* Weapon = Weapons.Num() == 0 ? nullptr : Weapons[CurrentWeaponIndex];
	if (!IsValid(Weapon))
	{
		return;
	}
	
	bIsAiming = true;
	AimTimeline->Play();
}

/**
 * @brief Start aiming with the current weapon
 */
void AUSKCharacter::StopAiming()
{
	bIsAiming = false;
	AimTimeline->Reverse();

	if (bSprintQueued)
	{
		StartSprinting();
	}
}

/**
 * @brief Called after the aim timeline is updated
 */
void AUSKCharacter::OnAimTimelineUpdated(float Value)
{
	AWeapon* Weapon = Weapons.Num() == 0 ? nullptr : Weapons[CurrentWeaponIndex];
	if (!IsValid(Weapon))
	{
		return;
	}

	const FTransform OriginalTransform = Weapon->WeaponTransform;
	const FTransform TargetTransform = Weapon->WeaponAimTransform;
	Weapon->SetActorRelativeTransform(UKismetMathLibrary::TLerp(OriginalTransform, TargetTransform, Value));
	GetCameraComponent()->SetFieldOfView(FMath::Lerp(DefaultCameraFov, Weapon->AimFov, Value));
}

/**
 * @brief Called after the look at center timeline is updated
 */
void AUSKCharacter::OnLookAtCenterTimelineUpdated(float Value)
{	
	const FRotator CurrentRotation = GetActorRotation();
	const FRotator StartRotation = FRotator(CurrentRotation.Pitch, StartLookAtActorRotation, CurrentRotation.Roll);
	const FRotator TargetRotation = FRotator(CurrentRotation.Pitch, TargetLookAtActorRotation, CurrentRotation.Roll);
	const FRotator NewRotation = UKismetMathLibrary::RLerp(StartRotation, TargetRotation, Value, true);
	SetActorRotation(NewRotation);
}

/**
 * @brief Initialize the current camera perspective
 */
void AUSKCharacter::InitializeCameraPerspective()
{
	USK_LOG_INFO("Initializing camera perspective");
	
	GetCameraComponent()->bUsePawnControlRotation = GetCameraPerspective() == ECameraPerspective::FirstPerson;
	bUseControllerRotationYaw = GetCameraPerspective() == ECameraPerspective::FirstPerson;
	
	CurrentArmLength = 0.0f;
	GetSpringArmComponent()->TargetArmLength = 0.0f;	

	if (GetCameraPerspective() == ECameraPerspective::ThirdPerson)
	{
		GetCameraComponent()->AttachToComponent(GetSpringArmComponent(),
			FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
	else
	{
		GetCameraComponent()->AttachToComponent(GetMesh(),
			FAttachmentTransformRules::SnapToTargetIncludingScale, HeadSocketName);
		GetCameraComponent()->SetRelativeLocation(CameraAttachOffset);
	}
}

/**
 * @brief Calculate the current weapon sway
 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
 */
void AUSKCharacter::CalculateWeaponSway(const float DeltaSeconds)
{
	const AWeapon* Weapon = GetWeapon();
	if (!IsValid(Weapon) || !Weapon->bWeaponSway)
	{
		PreviousControlRotation = GetControlRotation();
		WeaponSway = FRotator::ZeroRotator;
		return;
	}
	
	const FRotator TargetWeaponSway = PreviousControlRotation - GetControlRotation() * Weapon->WeaponSwayMultiplier;
	WeaponSway = UKismetMathLibrary::RInterpTo(WeaponSway, TargetWeaponSway,
		DeltaSeconds, Weapon->WeaponSwayInterpSpeed);
	PreviousControlRotation = GetControlRotation();
}

/**
 * @brief Update the proning state of the character
 */
void AUSKCharacter::UpdateProning()
{
	if (!bCanProne)
	{
		return;
	}

	bProneAllowed = CheckProneAllowedAtLocation(FVector::ZeroVector);

	const FVector CanStandFromProneTraceLocation = GetActorLocation() +
		FVector(0.0f, 0.0f, DefaultCapsuleHalfHeight);
	FHitResult CanStandFromProneTraceResult;
	bCanStandFromProne = bIsProning && !UKismetSystemLibrary::CapsuleTraceSingle(GetWorld(),
		CanStandFromProneTraceLocation, CanStandFromProneTraceLocation, DefaultCapsuleRadius,
		DefaultCapsuleRadius, UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false, { }, EDrawDebugTrace::None, CanStandFromProneTraceResult, true);

	if (bCanStandFromProne && bForceStandFromProne)
	{
		StopProningInternal();
	}
}

/**
 * @brief Check if the character is allowed to prone at a location
 * @param LocationOffset The offset applied to the character location when checking if proning is allowed
 * @return A boolean value indicating if the character is allowed to prone at the location
 */
bool AUSKCharacter::CheckProneAllowedAtLocation(FVector LocationOffset) const
{
	const FVector TraceSize = FVector(DefaultCapsuleHalfHeight, DefaultCapsuleRadius, ProneTraceHeight);
	const FVector TraceLocationOffset = FVector(0.0f, 0.0f,
		GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() + ProneTraceOffsetZ);
	const FVector TraceLocation = GetActorLocation() - TraceLocationOffset + LocationOffset;

	FHitResult ProneAllowedTraceResult;
	return !UKismetSystemLibrary::BoxTraceSingle(GetWorld(), TraceLocation, TraceLocation, TraceSize,
		GetActorRotation(), UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false, { }, EDrawDebugTrace::None, ProneAllowedTraceResult, true);
}

/**
 * @brief Update the rotation of the character while looking at the center of the screen
 */
void AUSKCharacter::UpdateLookAtCenterActorRotation()
{
	const bool bShouldLookAtCenter = ShouldLookAtCenter();
	GetCharacterMovement()->bOrientRotationToMovement =
		GetCameraPerspective() == ECameraPerspective::ThirdPerson && !bShouldLookAtCenter;
	if (!bShouldLookAtCenter || GetCameraPerspective() != ECameraPerspective::ThirdPerson)
	{
		return;
	}

	const float MaxLookAtCenterRotation = FMath::Abs(GetMaxLookAtCenterRotation());
	const float LookAtCenterRotation = GetLookAtCenterRotation();
	if (LookAtCenterRotation <= MaxLookAtCenterRotation &&
		LookAtCenterRotation >= -MaxLookAtCenterRotation)
	{
		return;
	}

	StartLookAtActorRotation = GetActorRotation().Yaw;
	TargetLookAtActorRotation = StartLookAtActorRotation +
		(MaxLookAtCenterRotation * FMath::Sign(LookAtCenterRotation));
	LookAtCenterTimeline->Stop();
	LookAtCenterTimeline->PlayFromStart();
}

/**
 * @brief Check if the character should look at the center of the screen
 * @return A boolean value indicating if the character should look at the center of the screen
 */
bool AUSKCharacter::ShouldLookAtCenter() const
{
	if (bIsProning)
	{
		return bLookAtCenterWhileProning;
	}

	if (bIsCrouching)
	{
		return bLookAtCenterWhileCrouching;
	}

	const float Speed = UKismetMathLibrary::VSizeXY(GetMovementComponent()->Velocity);
	if (FMath::IsNearlyZero(Speed, 1.0f))
	{
		return bLookAtCenterWhileIdle;
	}

	return bIsSprinting && !bIsAiming ? bLookAtCenterWhileSprinting : bLookAtCenterWhileRunning;
}

/**
 * @brief Get the max look at center rotation before rotating the actor
 * @return The max look at center rotation before rotating the actor
 */
float AUSKCharacter::GetMaxLookAtCenterRotation() const
{
	if (bIsProning)
	{
		return MaxLookAtCenterRotationWhileProning;
	}

	if (bIsCrouching)
	{
		return MaxLookAtCenterRotationWhileCrouching;
	}

	const float Speed = UKismetMathLibrary::VSizeXY(GetMovementComponent()->Velocity);
	if (FMath::IsNearlyZero(Speed, 1.0f))
	{
		return MaxLookAtCenterRotationWhileIdle;
	}

	return bIsSprinting && !bIsAiming ? MaxLookAtCenterRotationWhileSprinting : MaxLookAtCenterRotationWhileRunning;
}
