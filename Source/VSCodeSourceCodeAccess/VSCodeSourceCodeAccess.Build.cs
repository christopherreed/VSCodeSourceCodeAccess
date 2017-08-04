// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class VSCodeSourceCodeAccess : ModuleRules
	{
        public VSCodeSourceCodeAccess(ReadOnlyTargetRules Target) : base(Target)
		{
			// https://docs.unrealengine.com/latest/INT/Programming/UnrealBuildSystem/IWYUReferenceGuide/index.html
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"SourceCodeAccess",
					"DesktopPlatform",
					"Settings"
				}
			);

			if (UEBuildConfiguration.bBuildEditor)
			{
				PrivateDependencyModuleNames.Add("HotReload");
			}
		}
	}
}