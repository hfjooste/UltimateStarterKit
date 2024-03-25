// Created by Henry Jooste

#include "USKAssetFactory.h"

#include "KismetCompilerModule.h"
#include "Kismet2/KismetEditorUtilities.h"

/**
 * @brief Create a new instance of the factory class
 */
UUSKAssetFactory::UUSKAssetFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
}

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
UObject* UUSKAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	UClass* BlueprintClass = nullptr;
	UClass* BlueprintGeneratedClass = nullptr;

	const IKismetCompilerInterface& Compiler = FModuleManager::LoadModuleChecked<IKismetCompilerInterface>("KismetCompiler");
	Compiler.GetBlueprintTypesForClass(SupportedClass, BlueprintClass, BlueprintGeneratedClass);
	return FKismetEditorUtilities::CreateBlueprint(SupportedClass, InParent, Name, BPTYPE_Normal,
		BlueprintClass, BlueprintGeneratedClass, CallingContext);
}
