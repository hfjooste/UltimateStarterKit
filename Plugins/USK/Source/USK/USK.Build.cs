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
			"EnhancedInput"
		});

		PrivateDependencyModuleNames.AddRange(new[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore"	
			}
		);

		DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}