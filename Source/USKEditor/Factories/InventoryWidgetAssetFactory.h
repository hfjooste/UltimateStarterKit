// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Inventory/InventoryWidget.h"
#include "InventoryWidgetAssetFactory.generated.h"

/**
 * @brief Factory class used to create an inventory widget
 */
UCLASS()
class USKEDITOR_API UInventoryWidgetAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UInventoryWidgetAssetFactory() { SupportedClass = UInventoryWidget::StaticClass(); }
};
