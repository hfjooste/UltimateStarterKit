// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Narrative/WorldText.h"
#include "WorldTextAssetFactory.generated.h"

/**
 * @brief Factory class used to create a world text actor
 */
UCLASS()
class USKEDITOR_API UWorldTextAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UWorldTextAssetFactory() { SupportedClass = AWorldText::StaticClass(); }
};
