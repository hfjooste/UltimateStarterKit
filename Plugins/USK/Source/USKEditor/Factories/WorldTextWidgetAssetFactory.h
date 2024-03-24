// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Narrative/WorldTextWidget.h"
#include "WorldTextWidgetAssetFactory.generated.h"

/**
 * @brief Factory class used to create a world text widget
 */
UCLASS()
class USKEDITOR_API UWorldTextWidgetAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UWorldTextWidgetAssetFactory() { SupportedClass = UWorldTextWidget::StaticClass(); }
};
