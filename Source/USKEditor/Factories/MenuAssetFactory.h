// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "USKAssetFactory.h"
#include "USK/Widgets/Menu.h"
#include "MenuAssetFactory.generated.h"

/**
 * @brief Factory class used to create a menu
 */
UCLASS()
class USKEDITOR_API UMenuAssetFactory : public UUSKAssetFactory
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Create a new instance of the factory class
	 */
	UMenuAssetFactory() { SupportedClass = UMenu::StaticClass(); }
};
