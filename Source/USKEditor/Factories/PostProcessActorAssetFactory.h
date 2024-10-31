// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Core/USKPostProcessActor.h"
#include "PostProcessActorAssetFactory.generated.h"

/**
 * @brief Factory class used to create a post process actor
 */
UCLASS()
class USKEDITOR_API UPostProcessActorAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UPostProcessActorAssetFactory() { SupportedClass = AUSKPostProcessActor::StaticClass(); }
};
