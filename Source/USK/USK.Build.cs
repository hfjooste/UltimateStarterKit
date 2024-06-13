// Created by Henry Jooste

using UnrealBuildTool;

public class USK : ModuleRules
{
	public USK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] { });
		PrivateIncludePaths.AddRange(new string[] { });
		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"InputCore",
			"EnhancedInput",
			"Niagara",
			"UMG",
			"AnimGraphRuntime",
			"AIModule",
			"NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
			"GameplayTags",
			"AIModule"
		});

		DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}