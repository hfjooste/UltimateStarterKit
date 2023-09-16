// Created by Henry Jooste

#include "USKDataAssetFactory.h"

#include "KismetCompilerModule.h"
#include "Kismet2/KismetEditorUtilities.h"

/**
 * @brief Create a new instance of the factory class
 */
UUSKDataAssetFactory::UUSKDataAssetFactory()
{
	DataAssetClass = nullptr;
	SupportedClass = nullptr;
	bCreateNew = true;
	bEditAfterNew = true;
}

/**
 * @brief Configure the properties of the asset
 * @return A boolean value indicating if the asset should be created
 */
bool UUSKDataAssetFactory::ConfigureProperties()
{
	return true;
}

/**
 * @brief Create a new data asset
 * @param Class The class to create
 * @param InParent The parent of the newly created object
 * @param Name The name of the newly created object
 * @param Flags The object flags to apply to the new object
 * @param Context The context used to create the new object
 * @param Warn The context used for displaying modal warning messages
 * @return A reference to the newly created object
 */
UObject* UUSKDataAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UDataAsset>(InParent, DataAssetClass, Name, Flags | RF_Transactional);
}