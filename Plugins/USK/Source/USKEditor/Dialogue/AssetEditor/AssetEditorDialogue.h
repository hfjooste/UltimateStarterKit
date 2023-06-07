// Created by Henry Jooste

#pragma once

#include "CoreMinimal.h"
#include "USK/Dialogue/Dialogue.h"

#if ENGINE_MAJOR_VERSION == 5
#include "UObject/ObjectSaveContext.h"
#endif

class FGGAssetEditorToolbar;

/**
 * @brief Editor used to edit a dialogue asset
 */
class USKEDITOR_API FAssetEditorDialogue : public FAssetEditorToolkit, public FNotifyHook, public FGCObject
{
public:
	/**
	 * @brief Create a new dialogue editor
	 */
	FAssetEditorDialogue();

	/**
	 * @brief Deinitialize the dialogue editor
	 */
	virtual ~FAssetEditorDialogue() override;

	/**
	 * @brief Initialize the dialogue editor
	 * @param EditWithinLevelEditor Should the asset be edited within the level editor?
	 * @param Dialogue The dialogue to edit
	 */
	void InitDialogueAssetEditor(const TSharedPtr<IToolkitHost>& EditWithinLevelEditor, UDialogue* Dialogue);

	/**
	 * @brief Register the tabs used by the dialogue editor
	 * @param InTabManager The manager used to register the tabs
	 */
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	/**
	 * @brief Unregister the tabs used by the dialogue editor
	 * @param InTabManager The manager used to unregister the tabs
	 */
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	/**
	 * @brief Get the FName of the editor
	 * @return The FName of the editor
	 */
	virtual FName GetToolkitFName() const override;

	/**
	 * @brief Get the name of the editor
	 * @return The name of the editor
	 */
	virtual FText GetBaseToolkitName() const override;

	/**
	 * @brief Get the name displayed in the editor tab
	 * @return The name displayed in the editor tab
	 */
	virtual FText GetToolkitName() const override;

	/**
	 * @brief Get the tooltip text displayed in the editor tab
	 * @return The tooltip text displayed in the editor tab
	 */
	virtual FText GetToolkitToolTipText() const override;

	/**
	 * @brief Get the world centric tab color scale
	 * @return The world centric tab color scale
	 */
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	/**
	 * @brief Get the world centric tab prefix
	 * @return The world centric tab prefix
	 */
	virtual FString GetWorldCentricTabPrefix() const override;

	/**
	 * @brief Save the asset
	 */
	virtual void SaveAsset_Execute() override;

	/**
	 * @brief Add referenced objects to the collector
	 * @param Collector The collector containing the referenced objects
	 */
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

#if ENGINE_MAJOR_VERSION == 5
	/**
	 * @brief Get the name of the referencer
	 * @return The name of the referencer
	 */
	virtual FString GetReferencerName() const override;
#endif

protected:
	/**
	 * @brief Spawn the viewport tab
	 * @param Args Arguments containing info about the tab to spawn
	 * @return The spawned viewport tab
	 */
	TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args) const;

	/**
	 * @brief Spawn the details tab
	 * @param Args Arguments containing info about the tab to spawn
	 * @return The spawned details tab
	 */
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args) const;

	/**
	 * @brief Create the internal widgets for the editor
	 */
	void CreateInternalWidgets();

	/**
	 * @brief Create the viewport widget for the editor
	 * @return A reference to the created viewport widget
	 */
	TSharedRef<SGraphEditor> CreateViewportWidget();

	/**
	 * @brief Create the editor graph
	 */
	void CreateEdGraph() const;

	/**
	 * @brief Create the list of commands used by the editor
	 */
	void CreateCommandList();

	/**
	 * @brief Get the current graph editor
	 * @return The current graph editor
	 */
	TSharedPtr<SGraphEditor> GetCurrentGraphEditor() const;

	/**
	 * @brief Get the selected nodes
	 * @return The selected nodes
	 */
	FGraphPanelSelectionSet GetSelectedNodes() const;

	/**
	 * @brief Rebuild the dialogue
	 */
	void RebuildDialogue();

	/**
	 * @brief Delete the selected nodes
	 */
	void DeleteSelectedNodes() const;

	/**
	 * @brief Can the selected nodes be deleted?
	 * @return A boolean value indicating whether the selected nodes can be deleted
	 */
	bool CanDeleteNodes() const;

	/**
	 * @brief Delete the selected duplicatable nodes
	 */
	void DeleteSelectedDuplicatableNodes() const;

	/**
	 * @brief Cut the selected nodes
	 */
	void CutSelectedNodes() const;

	/**
	 * @brief Can the selected nodes be cut?
	 * @return A boolean value indicating whether the selected nodes can be cut
	 */
	bool CanCutNodes() const;

	/**
	 * @brief Copy the selected nodes
	 */
	void CopySelectedNodes() const;

	/**
	 * @brief Can the selected nodes be copied?
	 * @return A boolean value indicating whether the selected nodes can be copied
	 */
	bool CanCopyNodes() const;

	/**
	 * @brief Paste the copied nodes
	 */
	void PasteNodes() const;

	/**
	 * @brief Paste the copied nodes at the given location
	 * @param Location The location to paste the nodes at
	 */
	void PasteNodesHere(const FVector2D& Location) const;

	/**
	 * @brief Can the copied nodes be pasted?
	 * @return A boolean value indicating whether the copied nodes can be pasted
	 */
	bool CanPasteNodes() const;

	/**
	 * @brief Duplicate the selected nodes
	 */
	void DuplicateNodes() const;

	/**
	 * @brief Called when the selected nodes have changed
	 * @param NewSelection The new set of selected nodes
	 */
	void OnSelectedNodesChanged(const TSet<UObject*>& NewSelection) const;

	/**
	 * @brief Called after a property has been changed
	 * @param PropertyChangedEvent The event containing info about the changed property
	 */
	void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent) const;

#if ENGINE_MAJOR_VERSION < 5
	/**
	 * @brief Called when a package has been saved
	 * @param PackageFileName The name of the package that was saved
	 * @param Context The context of the objects that were saved
	 */
	void OnPackageSaved(const FString& PackageFileName, UObject* Context);
#else
	/**
	 * @brief Called when a package has been saved
	 * @param PackageFileName The name of the package that was saved
	 * @param Package The package that was saved
	 * @param ObjectSaveContext The context of the objects that were saved
	 */
	void OnPackageSavedWithContext(const FString& PackageFileName, UPackage* Package, FObjectPostSaveContext ObjectSaveContext);
#endif

private:
	/**
	 * @brief A reference to the dialogue being edited
	 */
	UDialogue* EditingDialogue;

	/**
	 * @brief Handle to the registered OnPackageSave delegate
	 */
	FDelegateHandle OnPackageSavedDelegateHandle;

	/**
	 * @brief A reference to the viewport widget
	 */
	TSharedPtr<SGraphEditor> ViewportWidget;

	/**
	 * @brief A reference to the property widget
	 */
	TSharedPtr<IDetailsView> PropertyWidget;

	/**
	 * @brief The command list for this editor
	 */
	TSharedPtr<FUICommandList> GraphEditorCommands;
};