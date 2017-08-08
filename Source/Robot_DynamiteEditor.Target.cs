// (C) 2017 Todd D. Vance

using UnrealBuildTool;
using System.Collections.Generic;

public class Robot_DynamiteEditorTarget : TargetRules
{
	public Robot_DynamiteEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Robot_Dynamite" } );
	}
}
