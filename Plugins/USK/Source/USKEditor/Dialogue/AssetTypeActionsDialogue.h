// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 * @brief A class that represents asset type actions for a Dialogue asset
 */
class USKEDITOR_API FAssetTypeActionsDialogue : public FAssetTypeActions_Base
{
public:
	/**
	 * @brief Create a new instance of this class
	 * @param Category The category of the asset
	 */
	explicit FAssetTypeActionsDialogue(EAssetTypeCategories::Type Category);

	/**
	 * @brief Get the name of the asset
	 * @return The name of the asset
	 */
	virtual FText GetName() const override;

	/**
	 * @brief Get the color used to represent the asset
	 * @return The color used to represent the asset
	 */
	virtual FColor GetTypeColor() const override;

	/**
	 * @brief Get the class represented by this asset
	 * @return The class represented by this asset
	 */
	virtual UClass* GetSupportedClass() const override;

	/**
	 * @brief Open the editor used to edit this asset
	 * @param InObjects The objects to edit
	 * @param EditWithinLevelEditor Should the asset be edited within the level editor?
	 */
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects,
		TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

	/**
	 * @brief Get the category for this asset
	 * @return The category for this asset
	 */
	virtual uint32 GetCategories() override;

private:
	/**
	 * @brief The category of the asset
	 */
	EAssetTypeCategories::Type AssetCategory;
};