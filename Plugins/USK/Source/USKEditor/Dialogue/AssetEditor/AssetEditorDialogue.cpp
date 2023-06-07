// Created by Henry Jooste

#include "AssetEditorDialogue.h"
#include "AssetSchemaDialogue.h"
#include "DialogueAssetEditorTabs.h"
#include "EdGraphDialogue.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Framework/Commands/GenericCommands.h"
#include "GraphEditorActions.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "EdGraphUtilities.h"
#include "EditorStyleSet.h"
#include "EdGraphNodeDialogueEntry.h"
#include "EdGraphNodeDialogueTransition.h"

const FName FDialogueAssetEditorTabs::DialoguePropertyID(TEXT("DialogueProperty"));
const FName FDialogueAssetEditorTabs::ViewportID(TEXT("Viewport"));

/**
 * @brief Create a new dialogue editor
 */
FAssetEditorDialogue::FAssetEditorDialogue()
{
	EditingDialogue = nullptr;

#if ENGINE_MAJOR_VERSION < 5
	OnPackageSavedDelegateHandle = UPackage::PackageSavedEvent.AddRaw(this, &FAssetEditorDialogue::OnPackageSaved);
#else
	OnPackageSavedDelegateHandle = UPackage::PackageSavedWithContextEvent.AddRaw(this, &FAssetEditorDialogue::OnPackageSavedWithContext);
#endif
}

/**
 * @brief Deinitialize the dialogue editor
 */
FAssetEditorDialogue::~FAssetEditorDialogue()
{
#if ENGINE_MAJOR_VERSION < 5
	UPackage::PackageSavedEvent.Remove(OnPackageSavedDelegateHandle);
#else
	UPackage::PackageSavedWithContextEvent.Remove(OnPackageSavedDelegateHandle);
#endif
}

/**
 * @brief Initialize the dialogue editor
 * @param EditWithinLevelEditor Should the asset be edited within the level editor?
 * @param Dialogue The dialogue to edit
 */
void FAssetEditorDialogue::InitDialogueAssetEditor(
	const TSharedPtr<IToolkitHost>& EditWithinLevelEditor, UDialogue* Dialogue)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()
		? EToolkitMode::WorldCentric
		: EToolkitMode::Standalone;
	
	EditingDialogue = Dialogue;
	CreateEdGraph();

	FGenericCommands::Register();
	FGraphEditorCommands::Register();

	CreateInternalWidgets();
	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);	
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_DialogueEditor_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
#if ENGINE_MAJOR_VERSION < 5
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)->SetHideTabWell(true)
			)
#endif
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)->SetSizeCoefficient(0.9f)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.65f)
					->AddTab(FDialogueAssetEditorTabs::ViewportID, ETabState::OpenedTab)->SetHideTabWell(true)
				)
				->Split
				(
					FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.7f)
						->AddTab(FDialogueAssetEditorTabs::DialoguePropertyID, ETabState::OpenedTab)->SetHideTabWell(true)
					)
				)
			)
		);

	InitAssetEditor(Mode, EditWithinLevelEditor, FName(TEXT("DialogueEditorApp")), StandaloneDefaultLayout,
		true, true, EditingDialogue, false);
	RegenerateMenusAndToolbars();
}

/**
 * @brief Register the tabs used by the dialogue editor
 * @param InTabManager The manager used to register the tabs
 */
void FAssetEditorDialogue::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(FText::FromString("Dialogue Editor"));
	const auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(FDialogueAssetEditorTabs::ViewportID, FOnSpawnTab::CreateSP(this, &FAssetEditorDialogue::SpawnTab_Viewport))
		.SetDisplayName(FText::FromString("Viewport"))
		.SetGroup(WorkspaceMenuCategoryRef)
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 1
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "GraphEditor.EventGraph_16x"));
#else
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "GraphEditor.EventGraph_16x"));
#endif
	
	InTabManager->RegisterTabSpawner(FDialogueAssetEditorTabs::DialoguePropertyID, FOnSpawnTab::CreateSP(this, &FAssetEditorDialogue::SpawnTab_Details))
		.SetDisplayName(FText::FromString("Property"))
		.SetGroup(WorkspaceMenuCategoryRef)
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 1
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"));
#else
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));
#endif
}

/**
 * @brief Unregister the tabs used by the dialogue editor
 * @param InTabManager The manager used to unregister the tabs
 */
void FAssetEditorDialogue::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(FDialogueAssetEditorTabs::ViewportID);
	InTabManager->UnregisterTabSpawner(FDialogueAssetEditorTabs::DialoguePropertyID);
}

/**
 * @brief Get the FName of the editor
 * @return The FName of the editor
 */
FName FAssetEditorDialogue::GetToolkitFName() const
{
	return FName("FDialogueEditor");
}

/**
 * @brief Get the name of the editor
 * @return The name of the editor
 */
FText FAssetEditorDialogue::GetBaseToolkitName() const
{
	return FText::FromString("Dialogue Editor");
}

/**
 * @brief Get the name displayed in the editor tab
 * @return The name displayed in the editor tab
 */
FText FAssetEditorDialogue::GetToolkitName() const
{
	return FText::FromString(EditingDialogue->GetName());
}

/**
 * @brief Get the tooltip text displayed in the editor tab
 * @return The tooltip text displayed in the editor tab
 */
FText FAssetEditorDialogue::GetToolkitToolTipText() const
{
	return GetToolTipTextForObject(EditingDialogue);
}

/**
 * @brief Get the world centric tab color scale
 * @return The world centric tab color scale
 */
FLinearColor FAssetEditorDialogue::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

/**
 * @brief Get the world centric tab prefix
 * @return The world centric tab prefix
 */
FString FAssetEditorDialogue::GetWorldCentricTabPrefix() const
{
	return TEXT("DialogueEditor");
}

/**
 * @brief Save the asset
 */
void FAssetEditorDialogue::SaveAsset_Execute()
{
	if (IsValid(EditingDialogue))
	{
		RebuildDialogue();
	}

	FAssetEditorToolkit::SaveAsset_Execute();
}

/**
 * @brief Add referenced objects to the collector
 * @param Collector The collector containing the referenced objects
 */
void FAssetEditorDialogue::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(EditingDialogue);
	Collector.AddReferencedObject(EditingDialogue->EditorGraph);
}

#if ENGINE_MAJOR_VERSION == 5
/**
 * @brief Get the name of the referencer
 * @return The name of the referencer
 */
FString FAssetEditorDialogue::GetReferencerName() const
{
	return TEXT("FAssetEditor_LTDialogue");
}
#endif

/**
 * @brief Spawn the viewport tab
 * @param Args Arguments containing info about the tab to spawn
 * @return The spawned viewport tab
 */
TSharedRef<SDockTab> FAssetEditorDialogue::SpawnTab_Viewport(const FSpawnTabArgs& Args) const
{
	check(Args.GetTabId() == FDialogueAssetEditorTabs::ViewportID);
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab).Label(FText::FromString("Viewport"));

	if (ViewportWidget.IsValid())
	{
		SpawnedTab->SetContent(ViewportWidget.ToSharedRef());
	}

	return SpawnedTab;
}

/**
 * @brief Spawn the details tab
 * @param Args Arguments containing info about the tab to spawn
 * @return The spawned details tab
 */
TSharedRef<SDockTab> FAssetEditorDialogue::SpawnTab_Details(const FSpawnTabArgs& Args) const
{
	check(Args.GetTabId() == FDialogueAssetEditorTabs::DialoguePropertyID);

	return SNew(SDockTab)
#if ENGINE_MAJOR_VERSION < 5
		.Icon(FEditorStyle::GetBrush("LevelEditor.Tabs.Details"))
#endif
		.Label(FText::FromString("Property"))
		[
			PropertyWidget.ToSharedRef()
		];
}

/**
 * @brief Create the internal widgets for the editor
 */
void FAssetEditorDialogue::CreateInternalWidgets()
{
	ViewportWidget = CreateViewportWidget();

	FDetailsViewArgs Args;
	Args.bHideSelectionTip = true;
	Args.NotifyHook = this;

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyWidget = PropertyModule.CreateDetailView(Args);
	PropertyWidget->SetObject(EditingDialogue);
	PropertyWidget->OnFinishedChangingProperties().AddSP(this,
		&FAssetEditorDialogue::OnFinishedChangingProperties);
}

/**
 * @brief Create the viewport widget for the editor
 * @return A reference to the created viewport widget
 */
TSharedRef<SGraphEditor> FAssetEditorDialogue::CreateViewportWidget()
{
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = FText::FromString("Dialogue");

	CreateCommandList();
	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this,
		&FAssetEditorDialogue::OnSelectedNodesChanged);

	return SNew(SGraphEditor)
		.AdditionalCommands(GraphEditorCommands)
		.IsEditable(true)
		.Appearance(AppearanceInfo)
		.GraphToEdit(EditingDialogue->EditorGraph)
		.GraphEvents(InEvents)
		.AutoExpandActionMenu(true)
		.ShowGraphStateOverlay(false);
}

/**
 * @brief Create the editor graph
 */
void FAssetEditorDialogue::CreateEdGraph() const
{
	if (IsValid(EditingDialogue->EditorGraph))
	{
		return;
	}
	
	EditingDialogue->EditorGraph = CastChecked<UEdGraphDialogue>(
		FBlueprintEditorUtils::CreateNewGraph(EditingDialogue, NAME_None,
			UEdGraphDialogue::StaticClass(), UAssetSchemaDialogue::StaticClass()));	
	EditingDialogue->EditorGraph->bAllowDeletion = false;
	EditingDialogue->EditorGraph->GetSchema()->CreateDefaultNodesForGraph(*EditingDialogue->EditorGraph);
}

/**
 * @brief Create the list of commands used by the editor
 */
void FAssetEditorDialogue::CreateCommandList()
{
	if (GraphEditorCommands.IsValid())
	{
		return;
	}

	GraphEditorCommands = MakeShareable(new FUICommandList);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Delete,
		FExecuteAction::CreateRaw(this, &FAssetEditorDialogue::DeleteSelectedNodes),
		FCanExecuteAction::CreateRaw(this, &FAssetEditorDialogue::CanDeleteNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Copy,
		FExecuteAction::CreateRaw(this, &FAssetEditorDialogue::CopySelectedNodes),
		FCanExecuteAction::CreateRaw(this, &FAssetEditorDialogue::CanCopyNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Cut,
		FExecuteAction::CreateRaw(this, &FAssetEditorDialogue::CutSelectedNodes),
		FCanExecuteAction::CreateRaw(this, &FAssetEditorDialogue::CanCutNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Paste,
		FExecuteAction::CreateRaw(this, &FAssetEditorDialogue::PasteNodes),
		FCanExecuteAction::CreateRaw(this, &FAssetEditorDialogue::CanPasteNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Duplicate,
		FExecuteAction::CreateRaw(this, &FAssetEditorDialogue::DuplicateNodes),
		FCanExecuteAction::CreateRaw(this, &FAssetEditorDialogue::CanCopyNodes)
	);
}

/**
 * @brief Get the current graph editor
 * @return The current graph editor
 */
TSharedPtr<SGraphEditor> FAssetEditorDialogue::GetCurrentGraphEditor() const
{
	return ViewportWidget;
}

/**
 * @brief Get the selected nodes
 * @return The selected nodes
 */
FGraphPanelSelectionSet FAssetEditorDialogue::GetSelectedNodes() const
{
	FGraphPanelSelectionSet CurrentSelection;
	const TSharedPtr<SGraphEditor> FocusedGraphEd = GetCurrentGraphEditor();
	if (FocusedGraphEd.IsValid())
	{
		CurrentSelection = FocusedGraphEd->GetSelectedNodes();
	}

	return CurrentSelection;
}

/**
 * @brief Rebuild the dialogue
 */
void FAssetEditorDialogue::RebuildDialogue()
{
	if (!IsValid(EditingDialogue))
	{
		return;
	}

	UEdGraphDialogue* EdGraph = Cast<UEdGraphDialogue>(EditingDialogue->EditorGraph);
	check(IsValid(EdGraph));
	EdGraph->RebuildDialogue();
}

/**
 * @brief Delete the selected nodes
 */
void FAssetEditorDialogue::DeleteSelectedNodes() const
{
	const TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrentGraphEditor();
	if (!CurrentGraphEditor.IsValid())
	{
		return;
	}

	const FScopedTransaction Transaction(FGenericCommands::Get().Delete->GetDescription());
	CurrentGraphEditor->GetCurrentGraph()->Modify();

	const FGraphPanelSelectionSet SelectedNodes = CurrentGraphEditor->GetSelectedNodes();
	CurrentGraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator NodeIt(SelectedNodes); NodeIt; ++NodeIt)
	{
		UEdGraphNode* EdNode = Cast<UEdGraphNode>(*NodeIt);
		if (!IsValid(EdNode) || !EdNode->CanUserDeleteNode())
		{
			continue;
		}

		UEdGraphNodeDialogueEntry* EdGraphNodeDialogueEntry = Cast<UEdGraphNodeDialogueEntry>(EdNode);
		if (IsValid(EdGraphNodeDialogueEntry))
		{
			EdGraphNodeDialogueEntry->Modify();

			const UEdGraphSchema* Schema = EdGraphNodeDialogueEntry->GetSchema();
			if (IsValid(Schema))
			{
				Schema->BreakNodeLinks(*EdGraphNodeDialogueEntry);
			}

			EdGraphNodeDialogueEntry->DestroyNode();
		}
		else
		{
			EdNode->Modify();
			EdNode->DestroyNode();
		}
	}
}

/**
 * @brief Can the selected nodes be deleted?
 * @return A boolean value indicating whether the selected nodes can be deleted
 */
bool FAssetEditorDialogue::CanDeleteNodes() const
{
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		const UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (IsValid(Node) && Node->CanUserDeleteNode())
		{
			return true;
		}
	}

	return false;
}

/**
 * @brief Delete the selected duplicatable nodes
 */
void FAssetEditorDialogue::DeleteSelectedDuplicatableNodes() const
{
	const TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrentGraphEditor();
	if (!CurrentGraphEditor.IsValid())
	{
		return;
	}

	const FGraphPanelSelectionSet OldSelectedNodes = CurrentGraphEditor->GetSelectedNodes();
	CurrentGraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(OldSelectedNodes); SelectedIter; ++SelectedIter)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (IsValid(Node) && Node->CanDuplicateNode())
		{
			CurrentGraphEditor->SetNodeSelection(Node, true);
		}
	}

	DeleteSelectedNodes();
	CurrentGraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(OldSelectedNodes); SelectedIter; ++SelectedIter)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (IsValid(Node))
		{
			CurrentGraphEditor->SetNodeSelection(Node, true);
		}
	}
}

/**
 * @brief Cut the selected nodes
 */
void FAssetEditorDialogue::CutSelectedNodes() const
{
	CopySelectedNodes();
	DeleteSelectedDuplicatableNodes();
}

/**
 * @brief Can the selected nodes be cut?
 * @return A boolean value indicating whether the selected nodes can be cut
 */
bool FAssetEditorDialogue::CanCutNodes() const
{
	return CanCopyNodes() && CanDeleteNodes();
}

/**
 * @brief Copy the selected nodes
 */
void FAssetEditorDialogue::CopySelectedNodes() const
{
	FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	for (FGraphPanelSelectionSet::TIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (!IsValid(Node))
		{
			SelectedIter.RemoveCurrent();
			continue;
		}

		UEdGraphNodeDialogueTransition* EdGraphNodeDialogueTransition =
			Cast<UEdGraphNodeDialogueTransition>(*SelectedIter);
		if (IsValid(EdGraphNodeDialogueTransition))
		{
			const UEdGraphNodeDialogueEntry* StartNode = EdGraphNodeDialogueTransition->GetStartNode();
			const UEdGraphNodeDialogueEntry* EndNode = EdGraphNodeDialogueTransition->GetEndNode();
			if (!SelectedNodes.Contains(StartNode) || !SelectedNodes.Contains(EndNode))
			{
				SelectedIter.RemoveCurrent();
				continue;
			}
		}

		Node->PrepareForCopying();
	}

	FString ExportedText;
	FEdGraphUtilities::ExportNodesToText(SelectedNodes, ExportedText);
	FPlatformApplicationMisc::ClipboardCopy(*ExportedText);
}

/**
 * @brief Can the selected nodes be copied?
 * @return A boolean value indicating whether the selected nodes can be copied
 */
bool FAssetEditorDialogue::CanCopyNodes() const
{
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		const UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (IsValid(Node) && Node->CanDuplicateNode())
		{
			return true;
		}
	}

	return false;
}

/**
 * @brief Paste the copied nodes
 */
void FAssetEditorDialogue::PasteNodes() const
{
	const TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrentGraphEditor();
	if (CurrentGraphEditor.IsValid())
	{
		PasteNodesHere(CurrentGraphEditor->GetPasteLocation());
	}
}

/**
 * @brief Paste the copied nodes at the given location
 * @param Location The location to paste the nodes at
 */
void FAssetEditorDialogue::PasteNodesHere(const FVector2D& Location) const
{
	const TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrentGraphEditor();
	if (!CurrentGraphEditor.IsValid())
	{
		return;
	}

	UEdGraph* EdGraph = CurrentGraphEditor->GetCurrentGraph();
	if (IsValid(EdGraph))
	{
		const FScopedTransaction Transaction(FGenericCommands::Get().Paste->GetDescription());
		EdGraph->Modify();
		CurrentGraphEditor->ClearSelectionSet();

		FString TextToImport;
		FPlatformApplicationMisc::ClipboardPaste(TextToImport);

		TSet<UEdGraphNode*> PastedNodes;
		FEdGraphUtilities::ImportNodesFromText(EdGraph, TextToImport, PastedNodes);
		FVector2D AvgNodePosition(0.0f, 0.0f);

		for (TSet<UEdGraphNode*>::TIterator It(PastedNodes); It; ++It)
		{
			const UEdGraphNode* Node = *It;
			AvgNodePosition.X += Node->NodePosX;
			AvgNodePosition.Y += Node->NodePosY;
		}

		const float NumNodes = 1.0f / static_cast<float>(PastedNodes.Num());
		AvgNodePosition.X *= NumNodes;
		AvgNodePosition.Y *= NumNodes;

		for (TSet<UEdGraphNode*>::TIterator It(PastedNodes); It; ++It)
		{
			UEdGraphNode* Node = *It;
			CurrentGraphEditor->SetNodeSelection(Node, true);

			Node->NodePosX = (Node->NodePosX - AvgNodePosition.X) + Location.X;
			Node->NodePosY = (Node->NodePosY - AvgNodePosition.Y) + Location.Y;

			Node->SnapToGrid(16);
			Node->CreateNewGuid();
		}
	}

	CurrentGraphEditor->NotifyGraphChanged();
	UObject* GraphOwner = EdGraph->GetOuter();
	if (IsValid(GraphOwner))
	{
		GraphOwner->PostEditChange();
		GraphOwner->MarkPackageDirty();
	}
}

/**
 * @brief Can the copied nodes be pasted?
 * @return A boolean value indicating whether the copied nodes can be pasted
 */
bool FAssetEditorDialogue::CanPasteNodes() const
{
	const TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrentGraphEditor();
	if (!CurrentGraphEditor.IsValid())
	{
		return false;
	}

	FString ClipboardContent;
	FPlatformApplicationMisc::ClipboardPaste(ClipboardContent);
	return FEdGraphUtilities::CanImportNodesFromText(CurrentGraphEditor->GetCurrentGraph(), ClipboardContent);
}

/**
 * @brief Duplicate the selected nodes
 */
void FAssetEditorDialogue::DuplicateNodes() const
{
	CopySelectedNodes();
	PasteNodes();
}

/**
 * @brief Called when the selected nodes have changed
 * @param NewSelection The new set of selected nodes
 */
void FAssetEditorDialogue::OnSelectedNodesChanged(const TSet<UObject*>& NewSelection) const
{
	TArray<UObject*> Selection;
	for (UObject* SelectionEntry : NewSelection)
	{
		Selection.Add(SelectionEntry);
	}

	if (Selection.Num() == 0) 
	{
		PropertyWidget->SetObject(EditingDialogue);
		return;
	}

	PropertyWidget->SetObjects(Selection);
}

/**
 * @brief Called after a property has been changed
 * @param PropertyChangedEvent The event containing info about the changed property
 */
void FAssetEditorDialogue::OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent) const
{
	if (!IsValid(EditingDialogue))
	{
		return;	
	}

	EditingDialogue->EditorGraph->GetSchema()->ForceVisualizationCacheClear();
}

#if ENGINE_MAJOR_VERSION < 5
/**
 * @brief Called when a package has been saved
 * @param PackageFileName PackageFileName The name of the package that was saved
 * @param Context The context of the objects that were saved
 */
void FAssetEditorDialogue::OnPackageSaved(const FString& PackageFileName, UObject* Context)
{
	RebuildDialogue();
}
#else
/**
 * @brief Called when a package has been saved
 * @param PackageFileName The name of the package that was saved
 * @param Package The package that was saved
 * @param ObjectSaveContext The context of the objects that were saved
 */
void FAssetEditorDialogue::OnPackageSavedWithContext(const FString& PackageFileName, UPackage* Package, FObjectPostSaveContext ObjectSaveContext)
{
	RebuildDialogue();
}
#endif