// Created by Henry Jooste

#include "AssetTypeActionsDialogue.h"
#include "AssetEditor/AssetEditorDialogue.h"

/**
 * @brief Create a new instance of this class
 * @param Category The category of the asset
 */
FAssetTypeActionsDialogue::FAssetTypeActionsDialogue(const EAssetTypeCategories::Type Category)
	: AssetCategory(Category) { }

/**
 * @brief Get the name of the asset
 * @return The name of the asset
 */
FText FAssetTypeActionsDialogue::GetName() const
{
	return FText::FromString("Dialogue");
}

/**
 * @brief Get the color used to represent the asset
 * @return The color used to represent the asset
 */
FColor FAssetTypeActionsDialogue::GetTypeColor() const
{
	return FColor(255, 201, 14);
}

/**
 * @brief Get the class represented by this asset
 * @return The class represented by this asset
 */
UClass* FAssetTypeActionsDialogue::GetSupportedClass() const
{
	return UDialogue::StaticClass();
}

/**
 * @brief Open the editor used to edit this asset
 * @param InObjects The objects to edit
 * @param EditWithinLevelEditor Should the asset be edited within the level editor?
 */
void FAssetTypeActionsDialogue::OpenAssetEditor(const TArray<UObject*>& InObjects,
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

/**
 * @brief Get the category for this asset
 * @return The category for this asset
 */
uint32 FAssetTypeActionsDialogue::GetCategories()
{
	return AssetCategory;
}