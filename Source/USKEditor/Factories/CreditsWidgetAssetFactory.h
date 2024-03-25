// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Widgets/CreditsWidget.h"
#include "CreditsWidgetAssetFactory.generated.h"

/**
 * @brief Factory class used to create a credits widget
 */
UCLASS()
class USKEDITOR_API UCreditsWidgetAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UCreditsWidgetAssetFactory() { SupportedClass = UCreditsWidget::StaticClass(); }
};
