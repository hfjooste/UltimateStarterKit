// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Dialogue/DialogueWidget.h"
#include "DialogueWidgetAssetFactory.generated.h"

/**
 * @brief Factory class used to create a dialogue widget
 */
UCLASS()
class USKEDITOR_API UDialogueWidgetAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UDialogueWidgetAssetFactory() { SupportedClass = UDialogueWidget::StaticClass(); }
};
