// Created by Henry Jooste

#pragma once

#include "ClassViewerFilter.h"

/**
 * @brief A class that filters asset classes based on their parent classes.
 */
class FAssetClassParentFilter : public IClassViewerFilter
{
public:

	/**
	 * @brief A set of allowed children of classes.
	 */
	TSet<const UClass*> AllowedChildrenOfClasses;

	/**
	 * @brief Flags for disallowed classes.
	 */
	EClassFlags DisallowedClassFlags;

	/**
	 * @brief Whether to disallow blueprint base.
	 */
	bool bDisallowBlueprintBase;

	/**
	 * @brief Constructor for FAssetClassParentFilter.
	 */
	FAssetClassParentFilter();

	/**
	 * @brief Checks if a class is allowed based on the initialization options, the class itself, and the filter functions.
	 * @param InInitOptions The initialization options.
	 * @param InClass The class to check.
	 * @param InFilterFuncs The filter functions.
	 * @return True if the class is allowed, false otherwise.
	 */
	virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions,
		const UClass* InClass, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override;

	/**
	 * @brief Checks if an unloaded class is allowed based on the initialization options, the unloaded class data, and the filter functions.
	 * @param InInitOptions The initialization options.
	 * @param InUnloadedClassData The unloaded class data to check.
	 * @param InFilterFuncs The filter functions.
	 * @return True if the unloaded class is allowed, false otherwise.
	 */
	virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions,
		const TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData,
		TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override;
};
