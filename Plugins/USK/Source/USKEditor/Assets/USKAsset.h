// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 * @brief A class that represents asset type actions for USK related assets
 */
class USKEDITOR_API FUSKAsset : public FAssetTypeActions_Base
{	
public:	
	/**
	 * @brief Create a new instance of this class
	 * @param Category The category of the asset
	 * @param SubMenu The submenu of the asset
	 * @param Name The name of the asset
	 * @param Color The color of the asset
	 * @param Class The class of the asset
	 */
	FUSKAsset(EAssetTypeCategories::Type Category, const FString& SubMenu, const FString& Name, FColor Color, UClass* Class);

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
	 * @brief Get the sub menus for this asset
	 * @return An array of sub menus for this asset
	 */
	virtual const TArray<FText>& GetSubMenus() const override;

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

	/**
	 * @brief The submenu of the asset
	 */
	TArray<FText> AssetSubMenu;

	/**
	 * @brief The name of the asset
	 */
	FString AssetName;

	/**
	 * @brief The color of the asset
	 */
	FColor AssetColor;

	/**
	 * @brief The class of the asset
	 */
	UClass* AssetClass;
};