// Created by Henry Jooste

#include "DynamicCrosshair.h"

#include <Components/CanvasPanel.h>

#include "Components/Image.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "USK/Character/USKCharacter.h"
#include "USK/Logger/Log.h"

/**
 * @brief Overridable native event for when the widget has been constructed
 */
void UDynamicCrosshair::NativeConstruct()
{
	Super::NativeConstruct();
	Character = dynamic_cast<AUSKCharacter*>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!IsValid(Character))
	{
		USK_LOG_ERROR("Character is not valid");
		return;
	}

	Character->OnCrosshairUpdated.AddDynamic(this, &UDynamicCrosshair::UpdateCrosshair);
	UpdateCrosshair(Character->GetCrosshair());
}

/**
 * @brief Event called every frame, if ticking is enabled
 * @param MyGeometry Represents the position, size, and absolute position of a widget
 * @param InDeltaTime Game time elapsed during last frame modified by the time dilation 
 */
void UDynamicCrosshair::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (!IsValid(Character))
	{
		USK_LOG_ERROR("Character is not valid");
		return;
	}

	UpdateCrosshairSides(InDeltaTime);
}

/**
 * @brief Update the crosshair using new config
 * @param NewCrosshair The new crosshair config
 */
void UDynamicCrosshair::UpdateCrosshair(UCrosshairConfig* NewCrosshair)
{
	Crosshair = NewCrosshair;
	if (!IsValid(Crosshair))
	{
		SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	SetVisibility(ESlateVisibility::Visible);
	CenterImage->SetVisibility(Crosshair->bDisplayCenterImage ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	CenterShadowImage->SetVisibility(Crosshair->bDisplayCenterImage && Crosshair->bDisplayCenterShadow
		? ESlateVisibility::Visible
		: ESlateVisibility::Collapsed);
	
	CenterImage->SetBrushFromTexture(Crosshair->CenterImage, true);
	CenterShadowImage->SetBrushFromTexture(Crosshair->CenterImage, true);	
	CenterImage->SetBrushTintColor(Crosshair->CenterColor);
	CenterShadowImage->SetBrushTintColor(Crosshair->CenterShadowColor);
	CenterShadowImage->SetRenderScale(FVector2D(Crosshair->CenterShadowScale));
	SidesContainer->SetRenderTransformAngle(Crosshair->Rotation);

	UpdateSideImage(TopContainer, TopImage, TopShadowImage, Crosshair->bDisplayTop,
		true, Crosshair->TopColor, Crosshair->TopShadowColor, Crosshair->TopShadowScale,
		Crosshair->TopThickness, Crosshair->TopLength);

	UpdateSideImage(BottomContainer, BottomImage, BottomShadowImage, Crosshair->bDisplayBottom,
		true, Crosshair->BottomColor, Crosshair->BottomShadowColor, Crosshair->BottomShadowScale,
		Crosshair->BottomThickness, Crosshair->BottomLength);
		
	UpdateSideImage(LeftContainer, LeftImage, LeftShadowImage, Crosshair->bDisplayLeft,
		false, Crosshair->LeftColor, Crosshair->LeftShadowColor, Crosshair->LeftShadowScale,
		Crosshair->LeftThickness, Crosshair->LeftLength);

	UpdateSideImage(RightContainer, RightImage, RightShadowImage, Crosshair->bDisplayRight,
		false, Crosshair->RightColor, Crosshair->RightShadowColor, Crosshair->RightShadowScale,
		Crosshair->RightThickness, Crosshair->RightLength);
}

/**
 * @brief Update the sides of the crosshair
 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
 */
void UDynamicCrosshair::UpdateCrosshairSides(const float DeltaSeconds)
{
	if (!IsValid(Crosshair))
	{
		return;
	}
	
	const float MaxSpeed = Character->SprintSpeed;
	const float NewSpeed = Character->GetMovementComponent()->IsFalling()
		? MaxSpeed
		: UKismetMathLibrary::VSizeXY(Character->GetMovementComponent()->Velocity);
	CurrentSpeed = FMath::Lerp(CurrentSpeed, NewSpeed, DeltaSeconds * Crosshair->SpreadBlendSpeed);	

	UpdateSideImageSpread(TopContainer, true, Crosshair->TopLength, MaxSpeed, Crosshair->TopSpread,
		Crosshair->TopOffset, -1.0f);

	UpdateSideImageSpread(BottomContainer, true, Crosshair->BottomLength, MaxSpeed, Crosshair->BottomSpread,
		Crosshair->BottomOffset, 1.0f);
		
	UpdateSideImageSpread(LeftContainer, false, Crosshair->LeftLength, MaxSpeed, Crosshair->LeftSpread,
		Crosshair->LeftOffset, -1.0f);

	UpdateSideImageSpread(RightContainer, false, Crosshair->RightLength, MaxSpeed, Crosshair->RightSpread,
		Crosshair->RightOffset, 1.0f);
}

/**
 * @brief Update the side image of the crosshair
 * @param Container The container used by the side image
 * @param Image The side image
 * @param ShadowImage The side shadow image
 * @param ShouldDisplay Should the image be displayed?
 * @param IsVertical Is the image a vertical image?
 * @param Color The color of the image
 * @param ShadowColor The color of the shadow image
 * @param ShadowScale The scale of the shadow image
 * @param Thickness The thickness of the image
 * @param Length The length of the image
 */
void UDynamicCrosshair::UpdateSideImage(UCanvasPanel* Container, UImage* Image, UImage* ShadowImage,
	const bool ShouldDisplay, const bool IsVertical, const FSlateColor& Color, const FSlateColor& ShadowColor,
	const float ShadowScale, const float Thickness, const float Length) const
{
	Image->SetVisibility(ShouldDisplay ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	Image->SetBrushTintColor(Crosshair->bUseGlobalColor ? Crosshair->GlobalColor : Color);

	ShadowImage->SetVisibility(ShouldDisplay ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	ShadowImage->SetBrushTintColor(ShadowColor);

	const float SizeX = IsVertical ? Thickness : Length;
	const float SizeY = IsVertical ? Length : Thickness;
	Container->SetRenderScale(FVector2D(SizeX, SizeY));
	ShadowImage->SetRenderScale(FVector2D(ShadowScale));
}

/**
 * @brief Update the side image spread
 * @param Container The container used by the side image
 * @param IsVertical Is the image a vertical image?
 * @param Length The length of the image
 * @param MaxSpeed The maximum speed of the character
 * @param Spread The spread of the image
 * @param Offset The offset of the image
 * @param OffsetMultiplier The multiplier applied to the offset
 */
void UDynamicCrosshair::UpdateSideImageSpread(UCanvasPanel* Container, const bool IsVertical, const float Length,
	const float MaxSpeed, const float Spread, const float Offset, const float OffsetMultiplier) const
{
	const float ImageSpread = FMath::Min(CurrentSpeed / MaxSpeed * Spread, Spread);
	const float ImageOffset = Offset + ImageSpread + (Length * 0.5f);
	const float OffsetX = IsVertical ? 0.0f : ImageOffset * OffsetMultiplier;
	const float OffsetY = IsVertical ? ImageOffset * OffsetMultiplier : 0.0f;
	Container->SetRenderTranslation(FVector2D(OffsetX, OffsetY));
}
