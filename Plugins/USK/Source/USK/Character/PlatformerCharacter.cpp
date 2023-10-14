// Created by Henry Jooste

#include "PlatformerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "USK/Logger/Log.h"

/**
 * @brief Create a new instance of the APlatformerCharacter actor
 */
APlatformerCharacter::APlatformerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	SpringArmComponent->SetupAttachment(GetCapsuleComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	GetCameraComponent()->SetupAttachment(SpringArmComponent);
}

/**
 * @brief Overridable native event for when play begins for this actor
 */
void APlatformerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	USK_LOG_TRACE("Initializing character camera");
	GetSpringArmComponent()->TargetArmLength = TargetArmLength;
	CurrentArmLength = TargetArmLength;
	DefaultMeshLocation = GetMesh()->GetRelativeLocation();
}

/**
 * @brief Event called every frame, if ticking is enabled
 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
 */
void APlatformerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AdjustCameraPosition(DeltaSeconds);
}

/**
 * @brief Update the character mesh location while crouching
 * @param SizeDifference The difference between the original capsule size and the crouched capsule size
 */
void APlatformerCharacter::UpdateCharacterMeshLocationWhileCrouching(float SizeDifference)
{
	Super::UpdateCharacterMeshLocationWhileCrouching(SizeDifference);
	GetMesh()->SetRelativeLocation(DefaultMeshLocation + FVector(0.0f, 0.0f, SizeDifference));
}

/**
 * @brief Get the spring arm component of the character
 * @return The spring arm component responsible for controlling the distance of the camera
 */
USpringArmComponent* APlatformerCharacter::GetSpringArmComponent() const
{
	return SpringArmComponent;
}

/**
 * @brief Adjust the camera position
 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
 */
void APlatformerCharacter::AdjustCameraPosition(const float DeltaSeconds)
{
	const float ArmAdjustment = UKismetMathLibrary::VSizeXY(GetMovementComponent()->Velocity) * ArmLengthMultiplier;
	CurrentArmLength = TargetArmLength + ArmAdjustment;
	GetSpringArmComponent()->TargetArmLength = FMath::Lerp(GetSpringArmComponent()->TargetArmLength,
		CurrentArmLength, DeltaSeconds * CameraAdjustmentSpeed);
}
