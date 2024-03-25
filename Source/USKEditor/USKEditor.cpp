// Created by Henry Jooste

#include "USKEditor.h"

#include "AssetToolsModule.h"
#include "Assets/DialogueAsset.h"
#include "Assets/USKAsset.h"
#include "Dialogue/AssetEditor/DialogueEditorStyle.h"
#include "USK/Audio/MusicPlayer.h"
#include "USK/Character/USKCharacter.h"
#include "USK/Components/InteractTrigger.h"
#include "USK/Core/USKGameInstance.h"
#include "USK/Dialogue/Dialogue.h"
#include "USK/Dialogue/DialogueManager.h"
#include "USK/Dialogue/DialogueWidget.h"
#include "USK/Inventory/InventoryMenuItem.h"
#include "USK/Inventory/InventoryWidget.h"
#include "USK/Items/CollectableItem.h"
#include "USK/Logger/LogConfig.h"
#include "USK/Narrative/WorldText.h"
#include "USK/Narrative/WorldTextLetterWidget.h"
#include "USK/Narrative/WorldTextWidget.h"
#include "USK/Narrative/WorldTextWordWidget.h"
#include "USK/Quests/Quest.h"
#include "USK/Quests/QuestManager.h"
#include "USK/Weapons/Weapon.h"
#include "USK/Weapons/WeaponItem.h"
#include "USK/Weapons/WeaponAmmoItem.h"
#include "USK/Weapons/WeaponProjectile.h"
#include "USK/Weapons/WeaponProjectileDecal.h"
#include "USK/Widgets/CollectableItemIcon.h"
#include "USK/Widgets/CreditsWidget.h"
#include "USK/Widgets/FpsCounter.h"
#include "USK/Widgets/InputIndicator.h"
#include "USK/Widgets/InteractWidget.h"
#include "USK/Widgets/Menu.h"
#include "USK/Widgets/MessagePopupWidget.h"

#define LOCTEXT_NAMESPACE "FUSKEditorModule"

void FUSKEditorModule::StartupModule()
{
	FDialogueEditorStyle::Initialize();
	GraphPanelNodeFactory_Dialogue = MakeShareable(new FDialogueEntryFactory());
	FEdGraphUtilities::RegisterVisualNodeFactory(GraphPanelNodeFactory_Dialogue);
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	const EAssetTypeCategories::Type UskCategory = AssetTools.RegisterAdvancedAssetCategory(
		FName(TEXT("USK")), FText::FromString("Ultimate Starter Kit"));

	RegisterBlueprint(AssetTools, UskCategory, "Core", "Game Instance",
		FColor(10, 25, 175), UUSKGameInstance::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Core", "Save Game",
		FColor(10, 25, 175), UUSKSaveGame::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Core", "Log Configuration",
		FColor(10, 25, 175), ULogConfig::StaticClass());

	RegisterBlueprint(AssetTools, UskCategory, "Gameplay", "USK Character",
		FColor(63, 126, 255), AUSKCharacter::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Gameplay", "Shadow Decal",
		FColor(63, 126, 255), AShadowDecal::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Gameplay", "Collectable Item",
		FColor(63, 126, 255), ACollectableItem::StaticClass());

	RegisterBlueprint(AssetTools, UskCategory, "Weapons", "Crosshair Config",
		FColor(52, 255, 180), UCrosshairConfig::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Weapons", "Weapon",
		FColor(52, 255, 180), AWeapon::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Weapons", "Weapon Item",
		FColor(52, 255, 180), AWeaponItem::StaticClass());
    RegisterBlueprint(AssetTools, UskCategory, "Weapons", "Weapon Ammo Item",
        FColor(52, 255, 180), AWeaponAmmoItem::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Weapons", "Weapon Projectile",
		FColor(52, 255, 180), AWeaponProjectile::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Weapons", "Weapon Projectile Decal",
		FColor(52, 255, 180), AWeaponProjectileDecal::StaticClass());

	RegisterDialogue(AssetTools, UskCategory, "Dialogue",
		FColor(255, 201, 14), UDialogue::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Dialogue", "Dialogue Manager",
		FColor(255, 201, 14), ADialogueManager::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Dialogue", "Dialogue Participant",
		FColor(255, 201, 14), UDialogueParticipant::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Dialogue", "Dialogue Widget",
        FColor(255, 201, 14), UDialogueWidget::StaticClass());

	RegisterBlueprint(AssetTools, UskCategory, "Audio", "Music Player",
		FColor(97, 85, 212), AMusicPlayer::StaticClass());

	RegisterBlueprint(AssetTools, UskCategory, "Interaction", "Interact Trigger",
		FColor(255, 127, 39), UInteractTrigger::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Interaction", "Interact Widget",
    	FColor(255, 127, 39), UInteractWidget::StaticClass());
	
	RegisterBlueprint(AssetTools, UskCategory, "Inventory", "Inventory Menu Item",
		FColor(62, 140, 35), UInventoryMenuItem::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Inventory", "Inventory Widget",
		FColor(62, 140, 35), UInventoryWidget::StaticClass());
	
	RegisterBlueprint(AssetTools, UskCategory, "Quests", "Quest",
		FColor(237, 28, 36), UQuest::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Quests", "Quest Manager",
		FColor(237, 28, 36), AQuestManager::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Quests", "Quest Widget",
		FColor(237, 28, 36), UQuestWidget::StaticClass());

	RegisterBlueprint(AssetTools, UskCategory, "Settings", "Settings Configuration",
		FColor(255, 105, 180), USettingsConfig::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Settings", "Settings Data",
		FColor(255, 105, 180), USettingsData::StaticClass());

	RegisterBlueprint(AssetTools, UskCategory, "Narrative", "World Text",
		FColor(255, 127, 39), AWorldText::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Narrative", "World Text Widget",
		FColor(255, 127, 39), UWorldTextWidget::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Narrative", "World Text Word Widget",
		FColor(255, 127, 39), UWorldTextWordWidget::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "Narrative", "World Text Letter Widget",
		FColor(255, 127, 39), UWorldTextLetterWidget::StaticClass());
	
	RegisterBlueprint(AssetTools, UskCategory, "UI", "Collectable Item Icon",
		FColor(44, 89, 180), UCollectableItemIcon::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "UI", "Credits Widget",
		FColor(44, 89, 180), UCreditsWidget::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "UI", "Framerate Counter",
		FColor(44, 89, 180), UFpsCounter::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "UI", "Input Indicator",
		FColor(44, 89, 180), UInputIndicator::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "UI", "Input Indicator Icon",
		FColor(44, 89, 180), UInputIndicatorIcon::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "UI", "Menu",
		FColor(44, 89, 180), UMenu::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "UI", "Menu Item",
		FColor(44, 89, 180), UMenuItem::StaticClass());
	RegisterBlueprint(AssetTools, UskCategory, "UI", "Message Popup",
		FColor(44, 89, 180), UMessagePopupWidget::StaticClass());
}

void FUSKEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 Index = 0; Index < CreatedAssetTypeActions.Num(); ++Index)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[Index].ToSharedRef());
		}
	}

	if (GraphPanelNodeFactory_Dialogue.IsValid())
	{
		FEdGraphUtilities::UnregisterVisualNodeFactory(GraphPanelNodeFactory_Dialogue);
		GraphPanelNodeFactory_Dialogue.Reset();
	}

	FDialogueEditorStyle::Shutdown();
}

IModuleInterface& FUSKEditorModule::Get()
{
	return FModuleManager::LoadModuleChecked<IModuleInterface>("USKEditor");
}

bool FUSKEditorModule::IsAvailable()
{
	return FModuleManager::Get().IsModuleLoaded("USKEditor");
}

void FUSKEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, const TSharedRef<IAssetTypeActions>& Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

void FUSKEditorModule::RegisterBlueprint(IAssetTools& AssetTools, const EAssetTypeCategories::Type Category,
	const FString& AssetSubMenu, const FString& AssetName, const FColor AssetColor, UClass* AssetClass)
{
	FUSKAsset* Asset = new FUSKAsset(Category, AssetSubMenu, AssetName, AssetColor, AssetClass);
	RegisterAssetTypeAction(AssetTools, MakeShareable(Asset));
}

void FUSKEditorModule::RegisterDialogue(IAssetTools& AssetTools, const EAssetTypeCategories::Type Category,
	const FString& AssetName, const FColor AssetColor, UClass* AssetClass)
{
	FDialogueAsset* Asset = new FDialogueAsset(Category, AssetName, AssetColor, AssetClass);
	RegisterAssetTypeAction(AssetTools, MakeShareable(Asset));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUSKEditorModule, USKEditor)