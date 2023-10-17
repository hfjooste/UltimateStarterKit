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
#include "USK/Audio/AudioUtils.h"
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

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->bOrientRotationToMovement = true;

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
	
	USK_LOG_TRACE("Initializing character movement");	
	GetCharacterMovement()->JumpZVelocity = JumpVelocity;
	GetCharacterMovement()->AirControl = AirControl;
	GetCharacterMovement()->FallingLateralFriction = FallingFriction;
	GetCharacterMovement()->GravityScale = Gravity;
	GetCharacterMovement()->BrakingFriction = BrakingFriction;
	GetCharacterMovement()->MaxAcceleration = MaxAcceleration;

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

	DefaultMovementSpeed = GetCharacterMovement()->MaxWalkSpeed;
	DefaultCapsuleSize = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	if (IsValid(CrouchCurve))
	{
		CrouchTimelineUpdateEvent.BindUFunction(this, FName("OnCrouchTimelineUpdated"));
		CrouchTimeline->AddInterpFloat(CrouchCurve, CrouchTimelineUpdateEvent);
		CrouchTimeline->SetLooping(false);
	}
}

/**
 * @brief Event called every frame, if ticking is enabled
 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
 */
void AUSKCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AirTime = GetCharacterMovement()->IsFalling() ? AirTime + DeltaSeconds : 0.0f;
}

/**
 * @brief Tell client that the Pawn is begin restarted
 */
void AUSKCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	USK_LOG_TRACE("Adding input mapping context");
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
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
	EnhancedInput->BindAction(FireWeaponAction, ETriggerEvent::Started, this, &AUSKCharacter::StartFiringWeapon);
	EnhancedInput->BindAction(FireWeaponAction, ETriggerEvent::Completed, this, &AUSKCharacter::StopFiringWeapon);
	EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Started, this, &AUSKCharacter::StartCrouching);
	EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AUSKCharacter::StopCrouching);
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
 * @brief Set the current weapon used by the character
 * @param NewWeapon The new weapon
 */
void AUSKCharacter::SetWeapon(AWeapon* NewWeapon)
{
	Weapon = NewWeapon;
}

/**
 * @brief Get the current weapon used by the character
 * @return The current weapon used by the character
 */
AWeapon* AUSKCharacter::GetWeapon() const
{
	return Weapon;
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
 * @brief Check if the character is busy ending the crouch
 * @return A boolean value indicating if the character is busy ending the crouch
 */
bool AUSKCharacter::IsEndingCrouch() const
{
	return bIsEndingCrouch;
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
	if (IsValid(Weapon))
	{
		Weapon->StartFiring();
	}
}

/**
 * @brief Stop firing the current weapon
 */
void AUSKCharacter::StopFiringWeapon()
{
	if (IsValid(Weapon))
	{
		Weapon->StopFiring();
	}
}

/**
 * @brief Start crouching
 */
void AUSKCharacter::StartCrouching()
{
	if (bCanStomp && GetCharacterMovement()->IsFalling() && AirTime >= MinAirTimeBeforeStomping)
	{
		StartStomping();
	}
	
	bIsCrouching = true;
	bIsEndingCrouch = false;
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeedCrouched;
	if (!GetCharacterMovement()->IsFalling())
	{
		CrouchTimeline->Play();
	}
}

/**
 * @brief Stop crouching
 */
void AUSKCharacter::StopCrouching()
{
	bIsEndingCrouch = true;
	GetCharacterMovement()->MaxWalkSpeed = DefaultMovementSpeed;
	CrouchTimeline->Reverse();
}

/**
 * @brief Update the character mesh location while crouching
 * @param SizeDifference The difference between the original capsule size and the crouched capsule size
 */
void AUSKCharacter::UpdateCharacterMeshLocationWhileCrouching(float SizeDifference) { }

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
	
	UKismetSystemLibrary::K2_SetTimer(this, "ResetStomping", 0.1f, false);
	LaunchCharacter(FVector(0.0f, 0.0f, StompLandVelocity), false, true);
	
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
	if (bIsStomping)
	{
		return;
	}
	
	const FVector2D InputValue = Input.Get<FVector2D>();	
	FRotator Rotation = GetControlRotation();
	Rotation.Pitch = 0.0f;
	Rotation.Roll = 0.0f;
	AddMovementInput(UKismetMathLibrary::GetForwardVector(Rotation), InputValue.Y);

	Rotation = GetControlRotation();
	Rotation.Pitch = 0.0f;
	AddMovementInput(UKismetMathLibrary::GetRightVector(Rotation), InputValue.X);
}

/**
 * @brief Rotate the camera
 * @param Input The input action containing the input values
 */
void AUSKCharacter::RotateCamera(const FInputActionValue& Input)
{
	const FVector2D InputValue = Input.Get<FVector2D>();
	AddControllerYawInput(InputValue.X);
	AddControllerPitchInput(InputValue.Y);
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
 * @brief Called after the crouch timeline is updated
 */
void AUSKCharacter::OnCrouchTimelineUpdated(float Value)
{
	if (FMath::IsNearlyEqual(Value, 1.0f))
	{
		bIsCrouching = false;
		bIsEndingCrouch = false;
	}
	
	const float CapsuleHalfHeight = GetCharacterMovement()->IsFalling()
		? DefaultCapsuleSize
		: FMath::Lerp(0.0f, DefaultCapsuleSize, Value);
	UpdateCharacterMeshLocationWhileCrouching(DefaultCapsuleSize - CapsuleHalfHeight);
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
