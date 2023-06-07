// Created by Henry Jooste

#include "USKEditor.h"

#include "AssetToolsModule.h"
#include "Dialogue\AssetTypeActionsDialogue.h"
#include "Dialogue\AssetEditor\DialogueEditorStyle.h"

#define LOCTEXT_NAMESPACE "FUSKEditorModule"

void FUSKEditorModule::StartupModule()
{
	FDialogueEditorStyle::Initialize();
	GraphPanelNodeFactory_Dialogue = MakeShareable(new FDialogueEntryFactory());
	FEdGraphUtilities::RegisterVisualNodeFactory(GraphPanelNodeFactory_Dialogue);
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	DialogueAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Ultimate Starter Kit")), FText::FromString("Ultimate Starter Kit"));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActionsDialogue(DialogueAssetCategoryBit)));
}

void FUSKEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 Index = 0; Index < CreatedAssetTypeActions.Num(); ++Index)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[Index].ToSharedRef());
		}
	}

	if (GraphPanelNodeFactory_Dialogue.IsValid())
	{
		FEdGraphUtilities::UnregisterVisualNodeFactory(GraphPanelNodeFactory_Dialogue);
		GraphPanelNodeFactory_Dialogue.Reset();
	}

	FDialogueEditorStyle::Shutdown();
}

IModuleInterface& FUSKEditorModule::Get()
{
	return FModuleManager::LoadModuleChecked<IModuleInterface>("USKEditor");
}

bool FUSKEditorModule::IsAvailable()
{
	return FModuleManager::Get().IsModuleLoaded("USKEditor");
}

void FUSKEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUSKEditorModule, USKEditor)