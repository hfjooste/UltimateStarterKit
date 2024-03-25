// Created by Henry Jooste

#pragma once

#include "AssetTypeCategories.h"
#include "IAssetTools.h"
#include "IAssetTypeActions.h"
#include "Dialogue\DialogueNodeFactory.h"
#include "Modules/ModuleManager.h"

class FUSKEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	static IModuleInterface& Get();
	static bool IsAvailable();

private:
	TArray< TSharedPtr<IAssetTypeActions> > CreatedAssetTypeActions;
	TSharedPtr<FGraphPanelNodeFactory> GraphPanelNodeFactory_Dialogue;
	void RegisterAssetTypeAction(IAssetTools& AssetTools, const TSharedRef<IAssetTypeActions>& Action);
	void RegisterBlueprint(IAssetTools& AssetTools, EAssetTypeCategories::Type Category, const FString& AssetSubMenu,
		const FString& AssetName, FColor AssetColor, UClass* AssetClass);
	void RegisterDialogue(IAssetTools& AssetTools, EAssetTypeCategories::Type Category,
		const FString& AssetName, FColor AssetColor, UClass* AssetClass);
};
