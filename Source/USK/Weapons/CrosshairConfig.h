// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CrosshairConfig.generated.h"

/**
 * @brief The crosshair configuration data asset
 */
UCLASS(BlueprintType)
class USK_API UCrosshairConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/**
	 * @brief Should the center image be displayed?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Center")
	bool bDisplayCenterImage = true;

	/**
	 * @brief The image to display in the center of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Center",
		meta=(EditCondition="bDisplayCenterImage", EditConditionHides))
	UTexture2D* CenterImage;

    /**
     * @brief The color of the center image
     */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Center",
		meta=(EditCondition="bDisplayCenterImage", EditConditionHides))
	FLinearColor CenterColor = FLinearColor::White;

	/**
	 * @brief Should a shadow be displayed behind the center image?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Center|Shadow",
		meta=(EditCondition="bDisplayCenterImage", EditConditionHides))
	bool bDisplayCenterShadow = true;

	/**
	 * @brief The color of the shadow behind the center image
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Center|Shadow",
		meta=(EditCondition="bDisplayCenterImage && bDisplayCenterShadow", EditConditionHides))
	FLinearColor CenterShadowColor = FLinearColor::Black;

	/**
	 * @brief The scale of the shadow behind the center image
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Center|Shadow",
		meta=(EditCondition="bDisplayCenterImage && bDisplayCenterShadow", EditConditionHides))
	float CenterShadowScale = 1.15f;

	/**
	 * @brief The rotation applied to the sides of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides")
	float Rotation;

	/**
	 * @brief The blend speed used when updating the spread of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides")
	float SpreadBlendSpeed = 10.0f;

	/**
	 * @brief Should a global color be used for the sides of the crosshair?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides")
	bool bUseGlobalColor = true;

	/**
	 * @brief The global color used for the sides of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides",
		meta=(EditCondition="bUseGlobalColor", EditConditionHides))
	FLinearColor GlobalColor = FLinearColor::White;

	/**
	 * @brief Should the top side of the crosshair be displayed?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Top")
	bool bDisplayTop = true;

	/**
	 * @brief The color of the top side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Top",
		meta=(EditCondition="bDisplayTop && !bUseGlobalColor", EditConditionHides))
	FLinearColor TopColor = FLinearColor::White;

	/**
	 * @brief The length of the top side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Top",
		meta=(EditCondition="bDisplayTop", EditConditionHides))
	float TopLength = 20.0f;

	/**
	 * @brief The thickness of the top side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Top",
		meta=(EditCondition="bDisplayTop", EditConditionHides))
	float TopThickness = 4.0f;

	/**
	 * @brief The spread of the top side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Top",
		meta=(EditCondition="bDisplayTop", EditConditionHides))
	float TopSpread = 50.0f;

	/**
	 * @brief The offset of the top side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Top",
		meta=(EditCondition="bDisplayTop", EditConditionHides))
	float TopOffset = 10.0f;

	/**
	 * @brief Should a shadow be displayed behind the top side of the crosshair?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Top|Shadow",
		meta=(EditCondition="bDisplayTop", EditConditionHides))
	bool bDisplayTopShadow = true;

	/**
	 * @brief The color of the shadow behind the top side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Top|Shadow",
		meta=(EditCondition="bDisplayTop && bDisplayTopShadow", EditConditionHides))
	FLinearColor TopShadowColor = FLinearColor::Black;

	/**
	 * @brief The scale of the shadow behind the top side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Top|Shadow",
		meta=(EditCondition="bDisplayTop && bDisplayTopShadow", EditConditionHides))
	float TopShadowScale = 1.15f;

	/**
	 * @brief Should the bottom side of the crosshair be displayed?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Bottom")
	bool bDisplayBottom = true;

	/**
	 * @brief The color of the bottom side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Bottom",
		meta=(EditCondition="bDisplayBottom && !bUseGlobalColor", EditConditionHides))
	FLinearColor BottomColor = FLinearColor::White;

	/**
	 * @brief The length of the bottom side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Bottom",
		meta=(EditCondition="bDisplayBottom", EditConditionHides))
	float BottomLength = 20.0f;

	/**
	 * @brief The thickness of the bottom side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Bottom",
		meta=(EditCondition="bDisplayBottom", EditConditionHides))
	float BottomThickness = 4.0f;

	/**
	 * @brief The spread of the bottom side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Bottom",
		meta=(EditCondition="bDisplayBottom", EditConditionHides))
	float BottomSpread = 50.0f;

	/**
	 * @brief The offset of the bottom side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Bottom",
		meta=(EditCondition="bDisplayBottom", EditConditionHides))
	float BottomOffset = 10.0f;

	/**
	 * @brief Should a shadow be displayed behind the bottom side of the crosshair?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Bottom|Shadow",
		meta=(EditCondition="bDisplayBottom", EditConditionHides))
	bool bDisplayBottomShadow = true;

	/**
	 * @brief The color of the shadow behind the bottom side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Bottom|Shadow",
		meta=(EditCondition="bDisplayBottom && bDisplayBottomShadow", EditConditionHides))
	FLinearColor BottomShadowColor = FLinearColor::Black;

	/**
	 * @brief The scale of the shadow behind the bottom side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Bottom|Shadow",
		meta=(EditCondition="bDisplayBottom && bDisplayBottomShadow", EditConditionHides))
	float BottomShadowScale = 1.15f;

	/**
	 * @brief Should the left side of the crosshair be displayed?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Left")
	bool bDisplayLeft = true;

	/**
	 * @brief The color of the left side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Left",
		meta=(EditCondition="bDisplayLeft && !bUseGlobalColor", EditConditionHides))
	FLinearColor LeftColor = FLinearColor::White;

	/**
	 * @brief The length of the left side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Left",
		meta=(EditCondition="bDisplayLeft", EditConditionHides))
	float LeftLength = 20.0f;

	/**
	 * @brief The thickness of the left side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Left",
		meta=(EditCondition="bDisplayLeft", EditConditionHides))
	float LeftThickness = 4.0f;

	/**
	 * @brief The spread of the left side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Left",
		meta=(EditCondition="bDisplayLeft", EditConditionHides))
	float LeftSpread = 50.0f;

	/**
	 * @brief The offset of the left side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Left",
		meta=(EditCondition="bDisplayLeft", EditConditionHides))
	float LeftOffset = 10.0f;

	/**
	 * @brief Should a shadow be displayed behind the left side of the crosshair?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Left|Shadow",
		meta=(EditCondition="bDisplayLeft", EditConditionHides))
	bool bDisplayLeftShadow = true;

	/**
	 * @brief The color of the shadow behind the left side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Left|Shadow",
		meta=(EditCondition="bDisplayLeft && bDisplayLeftShadow", EditConditionHides))
	FLinearColor LeftShadowColor = FLinearColor::Black;

	/**
	 * @brief The scale of the shadow behind the left side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Left|Shadow",
		meta=(EditCondition="bDisplayLeft && bDisplayLeftShadow", EditConditionHides))
	float LeftShadowScale = 1.15f;

	/**
	 * @brief Should the right side of the crosshair be displayed?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Right")
	bool bDisplayRight = true;

	/**
	 * @brief The color of the right side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Right",
		meta=(EditCondition="bDisplayRight && !bUseGlobalColor", EditConditionHides))
	FLinearColor RightColor;

	/**
	 * @brief The length of the right side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Right",
		meta=(EditCondition="bDisplayRight", EditConditionHides))
	float RightLength = 20.0f;

	/**
	 * @brief The thickness of the right side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Right",
		meta=(EditCondition="bDisplayRight", EditConditionHides))
	float RightThickness = 4.0f;

	/**
	 * @brief The spread of the right side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Right",
		meta=(EditCondition="bDisplayRight", EditConditionHides))
	float RightSpread = 50.0f;

	/**
	 * @brief The offset of the right side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Right",
		meta=(EditCondition="bDisplayRight", EditConditionHides))
	float RightOffset = 10.0f;

	/**
	 * @brief Should a shadow be displayed behind the right side of the crosshair?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Right|Shadow",
		meta=(EditCondition="bDisplayRight", EditConditionHides))
	bool bDisplayRightShadow = true;

	/**
	 * @brief The color of the shadow behind the right side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Right|Shadow",
		meta=(EditCondition="bDisplayRight && bDisplayRightShadow", EditConditionHides))
	FLinearColor RightShadowColor = FLinearColor::Black;

	/**
	 * @brief The scale of the shadow behind the right side of the crosshair
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|Dynamic Crosshair|Sides|Right|Shadow",
		meta=(EditCondition="bDisplayRight && bDisplayRightShadow", EditConditionHides))
	float RightShadowScale = 1.15f;
};
