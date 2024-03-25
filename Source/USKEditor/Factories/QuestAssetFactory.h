// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Quests/Quest.h"
#include "QuestAssetFactory.generated.h"

/**
 * @brief Factory class used to create a quest
 */
UCLASS()
class USKEDITOR_API UQuestAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UQuestAssetFactory() { SupportedClass = UQuest::StaticClass(); }
};