// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Components/InteractTrigger.h"
#include "InteractTriggerAssetFactory.generated.h"

/**
 * @brief Factory class used to create an interact trigger
 */
UCLASS()
class USKEDITOR_API UInteractTriggerAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UInteractTriggerAssetFactory() { SupportedClass = UInteractTrigger::StaticClass(); }
};