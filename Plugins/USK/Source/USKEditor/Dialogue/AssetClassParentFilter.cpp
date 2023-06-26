// Created by Henry Jooste

#include "AssetClassParentFilter.h"

#include "Kismet2/KismetEditorUtilities.h"

/**
 * @brief Constructor for FAssetClassParentFilter.
 */
FAssetClassParentFilter::FAssetClassParentFilter()
	: DisallowedClassFlags(CLASS_None), bDisallowBlueprintBase(false) { }

/**
 * @brief Checks if a class is allowed based on the initialization options, the class itself, and the filter functions.
 * @param InInitOptions The initialization options.
 * @param InClass The class to check.
 * @param InFilterFuncs The filter functions.
 * @return True if the class is allowed, false otherwise.
 */
bool FAssetClassParentFilter::IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions,
	const UClass* InClass, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs)
{
	const bool IsAllowed = !InClass->HasAnyClassFlags(DisallowedClassFlags) &&
		InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InClass) != EFilterReturn::Failed;
	return IsAllowed && bDisallowBlueprintBase &&
		FKismetEditorUtilities::CanCreateBlueprintOfClass(InClass) ? false : IsAllowed;
}

/**
 * @brief Checks if an unloaded class is allowed based on the initialization options, the unloaded class data, and the filter functions.
 * @param InInitOptions The initialization options.
 * @param InUnloadedClassData The unloaded class data to check.
 * @param InFilterFuncs The filter functions.
 * @return True if the unloaded class is allowed, false otherwise.
 */
bool FAssetClassParentFilter::IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions,
	const TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs)
{
	return !bDisallowBlueprintBase && !InUnloadedClassData->HasAnyClassFlags(DisallowedClassFlags) &&
		InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InUnloadedClassData) != EFilterReturn::Failed;	
}