﻿// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Quests/QuestManager.h"
#include "QuestManagerAssetFactory.generated.h"

/**
 * @brief Factory class used to create a quest manager
 */
UCLASS()
class USKEDITOR_API UQuestManagerAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UQuestManagerAssetFactory() { SupportedClass = AQuestManager::StaticClass(); }
};