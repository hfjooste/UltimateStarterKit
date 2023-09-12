// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USKAsset.h"

/**
 * @brief A class that represents asset type actions for a Dialogue asset
 */
class USKEDITOR_API FDialogueAsset : public FUSKAsset
{
public:
	/**
	 * @brief Create a new instance of this class
	 * @param Category The category of the asset
	 * @param Name The name of the asset
	 * @param Color The color of the asset
	 * @param Class The class of the asset
	 */
	FDialogueAsset(EAssetTypeCategories::Type Category, const FString& Name, const FColor& Color, UClass* Class);
	
	/**
	 * @brief Open the editor used to edit this asset
	 * @param InObjects The objects to edit
	 * @param EditWithinLevelEditor Should the asset be edited within the level editor?
	 */
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects,
		TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
};