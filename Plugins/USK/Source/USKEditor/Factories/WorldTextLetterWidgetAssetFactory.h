// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Narrative/WorldTextLetterWidget.h"
#include "WorldTextLetterWidgetAssetFactory.generated.h"

/**
 * @brief Factory class used to create a world text letter widget
 */
UCLASS()
class USKEDITOR_API UWorldTextLetterWidgetAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UWorldTextLetterWidgetAssetFactory() { SupportedClass = UWorldTextLetterWidget::StaticClass(); }
};
