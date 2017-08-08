// (C) 2017 Todd D. Vance

using UnrealBuildTool;
using System.Collections.Generic;

public class Robot_DynamiteTarget : TargetRules
{
	public Robot_DynamiteTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Robot_Dynamite" } );
	}
}
