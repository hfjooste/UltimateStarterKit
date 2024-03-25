// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Items/CollectableItem.h"
#include "CollectableItemAssetFactory.generated.h"

/**
 * @brief Factory class used to create a collectable item
 */
UCLASS()
class USKEDITOR_API UCollectableItemAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UCollectableItemAssetFactory() { SupportedClass = ACollectableItem::StaticClass(); }
};
