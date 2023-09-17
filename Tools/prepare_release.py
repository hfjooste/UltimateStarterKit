import os

docs = os.path.join(os.path.dirname(__file__), "docs", "docs_generator.py")
print(f"Documentation script path: {docs}\n")

os.system(f"python \"{docs}\" --input \"Audio\\AudioUtils\" --output audioutils")
os.system(f"python \"{docs}\" --input \"Audio\\MusicPlayer\" --output music")

os.system(f"python \"{docs}\" --input \"Character\\PlatformerAnimationInstance\" --output platformeranimation")
os.system(f"python \"{docs}\" --input \"Character\\PlatformerCharacter\" --output platformercharacter")
os.system(f"python \"{docs}\" --input \"Character\\ShadowDecal\" --output platformershadow")
os.system(f"python \"{docs}\" --input \"Character\\USKCharacter\" --output uskcharacter")
os.system(f"python \"{docs}\" --input \"Character\\FpsCharacter\" --output fpscharacter")

os.system(f"python \"{docs}\" --input \"Core\\InputDevice\" --output inputdevice")
os.system(f"python \"{docs}\" --input \"Core\\USKGameInstance\" --output gameinstance")

os.system(f"python \"{docs}\" --input \"Data\\TrackableData\" --output trackabledata")
os.system(f"python \"{docs}\" --input \"Data\\TrackableDataComponent\" --output trackabledatacomponent")

os.system(f"python \"{docs}\" --input \"Dialogue\\Dialogue\" --output dialogue")
os.system(f"python \"{docs}\" --input \"Dialogue\\DialogueParticipant\" --output dialogueparticipant")
os.system(f"python \"{docs}\" --input \"Dialogue\\DialogueEntry\" --output dialogueentry")
os.system(f"python \"{docs}\" --input \"Dialogue\\DialogueTransition\" --output dialoguetransition")
os.system(f"python \"{docs}\" --input \"Dialogue\\DialogueTransitionType\" --output dialoguetransitiontype")
os.system(f"python \"{docs}\" --input \"Dialogue\\DialogueManager\" --output dialoguemanager")
os.system(f"python \"{docs}\" --input \"Dialogue\\DialogueWidget\" --output dialoguewidget")

os.system(f"python \"{docs}\" --input \"Inventory\\InventoryComponent\" --output inventorycomponent")
os.system(f"python \"{docs}\" --input \"Inventory\\InventoryData\" --output inventorydata")
os.system(f"python \"{docs}\" --input \"Inventory\\InventoryItem\" --output inventoryitem")
os.system(f"python \"{docs}\" --input \"Inventory\\InventoryItemData\" --output inventoryitemdata")
os.system(f"python \"{docs}\" --input \"Inventory\\InventoryMenuItem\" --output inventorymenuitem")
os.system(f"python \"{docs}\" --input \"Inventory\\InventorySize\" --output inventorysize")
os.system(f"python \"{docs}\" --input \"Inventory\\InventoryWidget\" --output inventorywidget")

os.system(f"python \"{docs}\" --input \"Items\\AllowedCollector\" --output allowedcollector")
os.system(f"python \"{docs}\" --input \"Items\\CollectableItem\" --output collectableitem")

os.system(f"python \"{docs}\" --input \"Logger\\LogConfig\" --output logconfig")

os.system(f"python \"{docs}\" --input \"Settings\\SettingsData\" --output settingsdata")
os.system(f"python \"{docs}\" --input \"Settings\\SettingsConfig\" --output settingsconfig")
os.system(f"python \"{docs}\" --input \"Settings\\SettingsItemType\" --output settingsitemtype")
os.system(f"python \"{docs}\" --input \"Settings\\SettingsItem\" --output settingsitem")
os.system(f"python \"{docs}\" --input \"Settings\\SettingsUtils\" --output settingsutils")

os.system(f"python \"{docs}\" --input \"Utils\\ConfigUtils\" --output configutils")
os.system(f"python \"{docs}\" --input \"Utils\\Platform\" --output platformtype")
os.system(f"python \"{docs}\" --input \"Utils\\PlatformUtils\" --output platformutils")
os.system(f"python \"{docs}\" --input \"Utils\\ProjectUtils\" --output projectutils")

os.system(f"python \"{docs}\" --input \"Widgets\\CollectableItemIcon\" --output collectableitemicon")
os.system(f"python \"{docs}\" --input \"Widgets\\CreditsEntry\" --output creditsentry")
os.system(f"python \"{docs}\" --input \"Widgets\\CreditsWidget\" --output creditswidget")
os.system(f"python \"{docs}\" --input \"Widgets\\FpsCounter\" --output fpscounter --widget FpsCounter_Implementation")
os.system(f"python \"{docs}\" --input \"Widgets\\InputIndicator\" --output inputindicator --widget InputIndicator_Implementation")
os.system(f"python \"{docs}\" --input \"Widgets\\InputIndicatorIcon\" --output inputindicatoricon --widget InputIndicatorIcon_Implementation")
os.system(f"python \"{docs}\" --input \"Widgets\\Menu\" --output menu")
os.system(f"python \"{docs}\" --input \"Widgets\\MenuItem\" --output menuitem")
os.system(f"python \"{docs}\" --input \"Widgets\\MenuNavigation\" --output menunavigation")
os.system(f"python \"{docs}\" --input \"Widgets\\MenuItemValueUpdateMethod\" --output menuitemvalueupdatemethod")