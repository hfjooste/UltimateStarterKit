// Created by Henry Jooste

#include "FpsCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

/**
 * @brief Create a new instance of the AFpsCharacter actor
 */
AFpsCharacter::AFpsCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCameraComponent()->bUsePawnControlRotation = true;
	GetCameraComponent()->SetupAttachment(GetCapsuleComponent());

	GetMesh()->SetOnlyOwnerSee(true);
	GetMesh()->SetupAttachment(GetCameraComponent());
}
