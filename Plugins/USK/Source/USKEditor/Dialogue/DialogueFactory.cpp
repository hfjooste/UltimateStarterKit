// Created by Henry Jooste

#include "DialogueFactory.h"

#include "AssetClassParentFilter.h"
#include "USK/Dialogue/Dialogue.h"
#include "ClassViewerModule.h"
#include "Kismet2/SClassPickerDialog.h"

/**
 * @brief Create a new instance of the factory class
 */
UDialogueFactory::UDialogueFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UDialogue::StaticClass();
}

/**
 * @brief Configure the properties of the class
 * @return A boolean value indicating if the class was configured
 */
bool UDialogueFactory::ConfigureProperties()
{
	DialogueClass = nullptr;
	FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");
	
	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::ClassPicker;

#if ENGINE_MAJOR_VERSION < 5
	TSharedPtr<FAssetClassParentFilter> Filter = MakeShareable(new FAssetClassParentFilter);
	Options.ClassFilter = Filter;
#else
	TSharedRef<FAssetClassParentFilter> Filter = MakeShareable(new FAssetClassParentFilter);
	Options.ClassFilters.Add(Filter);
#endif

	Filter->DisallowedClassFlags = CLASS_Abstract | CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_HideDropDown;
	Filter->AllowedChildrenOfClasses.Add(UDialogue::StaticClass());

	UClass* ChosenClass;
	const bool ClassSelected = SClassPickerDialog::PickClass(FText::FromString("Pick Dialogue Class"), Options,
		ChosenClass, UDialogue::StaticClass());

	if (ClassSelected)
	{
		DialogueClass = ChosenClass;
	}

	return ClassSelected;
}

/**
 * @brief Create a new dialogue
 * @param Class The class to create
 * @param InParent The parent of the newly created object
 * @param Name The name of the newly created object
 * @param Flags The object flags to apply to the new object
 * @param Context The context used to create the new object
 * @param Warn The context used for displaying modal warning messages
 * @return A reference to the newly created object
 */
UObject* UDialogueFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
                                            UObject* Context, FFeedbackContext* Warn)
{
	if (IsValid(DialogueClass))
	{
		return NewObject<UDialogue>(InParent, DialogueClass, Name, Flags | RF_Transactional);
	}

	check(Class->IsChildOf(UDialogue::StaticClass()));
	return NewObject<UObject>(InParent, Class, Name, Flags | RF_Transactional);
}
