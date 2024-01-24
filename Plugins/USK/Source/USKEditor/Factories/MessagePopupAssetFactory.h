// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Widgets/MessagePopupWidget.h"
#include "MessagePopupAssetFactory.generated.h"

/**
 * @brief Factory class used to create a message popup widget
 */
UCLASS()
class USKEDITOR_API UMessagePopupAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UMessagePopupAssetFactory() { SupportedClass = UMessagePopupWidget::StaticClass(); }
};
