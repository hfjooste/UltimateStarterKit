import os

docs = os.path.join(os.path.dirname(__file__), "docs", "docs_generator.py")
print(f"Documentation script path: {docs}\n")

os.system(f"python \"{docs}\" --input \"Audio\\AudioUtils\" --output audioutils")
os.system(f"python \"{docs}\" --input \"Audio\\MusicPlayer\" --output music")

os.system(f"python \"{docs}\" --input \"Character\\PlatformerAnimationInstance\" --output platformeranimation")
os.system(f"python \"{docs}\" --input \"Character\\PlatformerCharacter\" --output platformercharacter")
os.system(f"python \"{docs}\" --input \"Character\\ShadowDecal\" --output platformershadow")

os.system(f"python \"{docs}\" --input \"Core\\InputDevice\" --output inputdevice")
os.system(f"python \"{docs}\" --input \"Core\\USKGameInstance\" --output gameinstance")

os.system(f"python \"{docs}\" --input \"Data\\TrackableData\" --output trackabledata")
os.system(f"python \"{docs}\" --input \"Data\\TrackableDataComponent\" --output trackabledatacomponent")

os.system(f"python \"{docs}\" --input \"Items\\AllowedCollector\" --output allowedcollector")
os.system(f"python \"{docs}\" --input \"Items\\CollectableItem\" --output collectableitem")

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