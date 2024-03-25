// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Widgets/CollectableItemIcon.h"
#include "CollectableItemIconAssetFactory.generated.h"

/**
 * @brief Factory class used to create a collectable item icon
 */
UCLASS()
class USKEDITOR_API UCollectableItemIconAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UCollectableItemIconAssetFactory() { SupportedClass = UCollectableItemIcon::StaticClass(); }
};
