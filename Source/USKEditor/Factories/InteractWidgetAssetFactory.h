// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Widgets/InteractWidget.h"
#include "InteractWidgetAssetFactory.generated.h"

/**
 * @brief Factory class used to create an interact widget
 */
UCLASS()
class USKEDITOR_API UInteractWidgetAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UInteractWidgetAssetFactory() { SupportedClass = UInteractWidget::StaticClass(); }
};