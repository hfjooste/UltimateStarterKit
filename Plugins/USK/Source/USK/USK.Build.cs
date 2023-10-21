// Created by Henry Jooste

using UnrealBuildTool;

public class USK : ModuleRules
{
	public USK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		if (Target.Type == TargetType.Editor)
		{
			PublicDependencyModuleNames.AddRange(new[] { "UnrealEd" });
		}
		
		PublicIncludePaths.AddRange(new string[] { });
		PrivateIncludePaths.AddRange(new string[] { });
		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"InputCore",
			"EnhancedInput",
			"Niagara",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
			"GameplayTags",
			"BlueprintGraph",
			"AnimGraphRuntime",
			"AnimGraph"
		});

		DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}