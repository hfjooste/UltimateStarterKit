// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "USK/Character/USKCharacter.h"
#include "DynamicCrosshair.generated.h"

/**
 * @brief The dynamic crosshair widget
 */
UCLASS()
class USK_API UDynamicCrosshair : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The center image of the crosshair
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* CenterImage;

	/**
	 * @brief The center shadow image of the crosshair
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* CenterShadowImage;

	/**
	 * @brief The container used by all the sides
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UCanvasPanel* SidesContainer;

	/**
	 * @brief The top container of the crosshair
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UCanvasPanel* TopContainer;

	/**
	 * @brief The top image of the crosshair
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* TopImage;

	/**
	 * @brief The top shadow image of the crosshair
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* TopShadowImage;

	/**
	 * @brief The bottom container of the crosshair
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UCanvasPanel* BottomContainer;

	/**
	 * @brief The bottom image of the crosshair
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* BottomImage;

	/**
	 * @brief The bottom shadow image of the crosshair
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* BottomShadowImage;

	/**
	 * @brief The left container of the crosshair
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UCanvasPanel* LeftContainer;
	
	/**
	 * @brief The left image of the crosshair
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* LeftImage;

	/**
	 * @brief The left shadow image of the crosshair
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* LeftShadowImage;

	/**
	 * @brief The right container of the crosshair
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UCanvasPanel* RightContainer;

	/**
	 * @brief The right image of the crosshair
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* RightImage;

	/**
	 * @brief The right shadow image of the crosshair
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* RightShadowImage;

protected:
	/**
	 * @brief Overridable native event for when the widget has been constructed
	 */
	virtual void NativeConstruct() override;

	/**
	 * @brief Event called every frame, if ticking is enabled
	 * @param MyGeometry Represents the position, size, and absolute position of a widget
	 * @param InDeltaTime Game time elapsed during last frame modified by the time dilation 
	 */
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	/**
	 * @brief A reference to the character using the crosshair
	 */
	UPROPERTY()
	AUSKCharacter* Character;

	/**
	 * @brief The current crosshair config
	 */
	UPROPERTY()
	UCrosshairConfig* Crosshair;

	/**
	 * @brief The current movement speed of the character
	 */
	float CurrentSpeed;

	/**
	 * @brief Update the crosshair using new config
	 * @param NewCrosshair The new crosshair config
	 */
	UFUNCTION()
	void UpdateCrosshair(UCrosshairConfig* NewCrosshair);

	/**
	 * @brief Update the sides of the crosshair
	 * @param DeltaSeconds Game time elapsed during last frame modified by the time dilation
	 */
	void UpdateCrosshairSides(float DeltaSeconds);

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
	void UpdateSideImage(UCanvasPanel* Container, UImage* Image, UImage* ShadowImage, const bool ShouldDisplay,
		const bool IsVertical, const FSlateColor& Color, const FSlateColor& ShadowColor, const float ShadowScale,
		const float Thickness, const float Length) const;

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
	void UpdateSideImageSpread(UCanvasPanel* Container, const bool IsVertical, const float Length,
		const float MaxSpeed, const float Spread, const float Offset, const float OffsetMultiplier) const;
};
