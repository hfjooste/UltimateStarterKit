// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "Factories/DataAssetFactory.h"
#include "USKDataAssetFactory.generated.h"

/**
 * @brief Factory class used to create USK related data assets
 */
UCLASS()
class USKEDITOR_API UUSKDataAssetFactory : public UDataAssetFactory
{
	GENERATED_BODY()

public:	
	/**
	 * @brief Create a new instance of the factory class
	 */
	UUSKDataAssetFactory();

	virtual bool ConfigureProperties() override;

	/**
	 * @brief Create a new dialogue
	 * @param Class The class to create
	 * @param InParent The parent of the newly created object
	 * @param Name The name of the newly created object
	 * @param Flags The object flags to apply to the new object
	 * @param Context The context used to create the new object
	 * @param Warn The context used for displaying modal warning messages
	 * @param CallingContext The calling context when creating the new object
	 * @return A reference to the newly created object
	 */
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};