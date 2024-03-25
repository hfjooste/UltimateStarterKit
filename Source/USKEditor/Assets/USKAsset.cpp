// Created by Henry Jooste

#include "USKAsset.h"

/**
 * @brief Create a new instance of this class
 * @param Category The category of the asset
 * @param SubMenu The submenu of the asset
 * @param Name The name of the asset
 * @param Color The color of the asset
 * @param Class The class of the asset
 */
FUSKAsset::FUSKAsset(const EAssetTypeCategories::Type Category, const FString& SubMenu, const FString& Name,
	const FColor Color, UClass* Class) : AssetCategory(Category), AssetSubMenu({FText::FromString(SubMenu)}),
		AssetName(Name), AssetColor(Color), AssetClass(Class) { }

/**
 * @brief Get the name of the asset
 * @return The name of the asset
 */
FText FUSKAsset::GetName() const
{
	return FText::FromString(AssetName);
}

/**
 * @brief Get the color used to represent the asset
 * @return The color used to represent the asset
 */
FColor FUSKAsset::GetTypeColor() const
{
	return AssetColor;
}

/**
 * @brief Get the class represented by this asset
 * @return The class represented by this asset
 */
UClass* FUSKAsset::GetSupportedClass() const
{
	return AssetClass;
}

/**
 * @brief Get the sub menus for this asset
 * @return An array of sub menus for this asset
 */
const TArray<FText>& FUSKAsset::GetSubMenus() const
{
	return AssetSubMenu;
}

/**
 * @brief Get the category for this asset
 * @return The category for this asset
 */
uint32 FUSKAsset::GetCategories()
{
	return AssetCategory;
}