// Created by Henry Jooste

using UnrealBuildTool;

public class USKEditor : ModuleRules
{
	public USKEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] { });
		PrivateIncludePaths.AddRange(new string[] { });
		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"UnrealEd",
			"BlueprintGraph",
			"AnimGraph"
		});

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"USK",
			"AssetTools",
			"Slate",
			"InputCore",
			"SlateCore",
			"GraphEditor",
			"PropertyEditor",
			"EditorStyle",
			"Kismet",
			"KismetWidgets",
			"ApplicationCore",
			"ToolMenus",
		});

		DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}