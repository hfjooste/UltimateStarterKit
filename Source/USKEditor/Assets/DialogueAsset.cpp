// Created by Henry Jooste

#include "DialogueAsset.h"
#include "USKEditor/Dialogue/AssetEditor/AssetEditorDialogue.h"

/**
 * @brief Create a new instance of this class
 * @param Category The category of the asset
 * @param Name The name of the asset
 * @param Color The color of the asset
 * @param Class The class of the asset
 */
FDialogueAsset::FDialogueAsset(const EAssetTypeCategories::Type Category, const FString& Name,
	const FColor& Color, UClass* Class) : FUSKAsset(Category, "Dialogue", Name, Color, Class) { }

/**
 * @brief Open the editor used to edit this asset
 * @param InObjects The objects to edit
 * @param EditWithinLevelEditor Should the asset be edited within the level editor?
 */
void FDialogueAsset::OpenAssetEditor(const TArray<UObject*>& InObjects,
                                                TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	for (auto ObjectIterator = InObjects.CreateConstIterator(); ObjectIterator; ++ObjectIterator)
	{
		UDialogue* Dialogue = dynamic_cast<UDialogue*>(*ObjectIterator);
		if (IsValid(Dialogue))
		{
			const TSharedRef<FAssetEditorDialogue> Editor(new FAssetEditorDialogue());
			Editor->InitDialogueAssetEditor(EditWithinLevelEditor, Dialogue);
		}
	}
}