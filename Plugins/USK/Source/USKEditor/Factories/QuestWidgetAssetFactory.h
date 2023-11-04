// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Widgets/QuestWidget.h"
#include "QuestWidgetAssetFactory.generated.h"

/**
 * @brief Factory class used to create a quest widget
 */
UCLASS()
class USKEDITOR_API UQuestWidgetAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UQuestWidgetAssetFactory() { SupportedClass = UQuestWidget::StaticClass(); }
};