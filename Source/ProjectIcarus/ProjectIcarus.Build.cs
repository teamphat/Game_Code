// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectIcarus : ModuleRules
{
	public ProjectIcarus(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Slate" });
	}
}
