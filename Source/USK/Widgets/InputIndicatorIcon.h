// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InputIndicatorIcon.generated.h"

/**
 * @brief A widget used to display a single input indicator image 
 */
UCLASS()
class USK_API UInputIndicatorIcon : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief The size box container used to resize the image
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class USizeBox* Container;

	/**
	 * @brief The image used to display the input indicator
	 */
	UPROPERTY(meta = (BindWidget), EditAnywhere, BlueprintReadWrite, Category = "Ultimate Starter Kit|UI")
	class UImage* Image;

	/**
	 * @brief Update the icon
	 * @param Size The size of the image
	 * @param Icon The new icon
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Starter Kit|UI")
	void UpdateIcon(float Size, UTexture2D* Icon) const;
};