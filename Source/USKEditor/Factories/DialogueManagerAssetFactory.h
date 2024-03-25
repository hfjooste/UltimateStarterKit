// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Dialogue/DialogueManager.h"
#include "DialogueManagerAssetFactory.generated.h"

/**
 * @brief Factory class used to create a dialogue manager
 */
UCLASS()
class USKEDITOR_API UDialogueManagerAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UDialogueManagerAssetFactory() { SupportedClass = ADialogueManager::StaticClass(); }
};
