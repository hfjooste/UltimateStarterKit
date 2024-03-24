// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Narrative/WorldTextWordWidget.h"
#include "WorldTextWordWidgetAssetFactory.generated.h"

/**
 * @brief Factory class used to create a world text word widget
 */
UCLASS()
class USKEDITOR_API UWorldTextWordWidgetAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UWorldTextWordWidgetAssetFactory() { SupportedClass = UWorldTextWordWidget::StaticClass(); }
};
