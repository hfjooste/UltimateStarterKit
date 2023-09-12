// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Character/ShadowDecal.h"
#include "ShadowDecalAssetFactory.generated.h"

/**
 * @brief Factory class used to create a shadow decal
 */
UCLASS()
class USKEDITOR_API UShadowDecalAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UShadowDecalAssetFactory() { SupportedClass = AShadowDecal::StaticClass(); }
};
