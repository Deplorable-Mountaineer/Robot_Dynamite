// (C) 2017 Todd D. Vance

#include "KeyBindings.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerInput.h"
#include "Runtime/Engine/Classes/GameFramework/InputSettings.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectIterator.h"


// Sets default values
AKeyBindings::AKeyBindings()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());

}

// Called when the game starts or when spawned
void AKeyBindings::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AKeyBindings::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<FBlueprintActionBinding> AKeyBindings::GetActionBindings(FName ActionName)
{
	TArray<FBlueprintActionBinding> Result;

	for (FInputActionKeyMapping& Mapping : Settings->ActionMappings)
	{
		if (ActionName == Mapping.ActionName)
		{
			Result.Add(FromFInputActionKeyMapping(Mapping));
		}
	}
	return Result;
}

void AKeyBindings::ApplyBindings()
{	

	Settings->SaveKeyMappings();

	for (TObjectIterator<UPlayerInput> It; It; ++It)
	{
		It->ForceRebuildingKeyMaps(true);
	}
}

void AKeyBindings::AddNewBinding(FBlueprintActionBinding& NewMapping)
{
	Settings->AddActionMapping(ToFInputActionKeyMapping(NewMapping));
}

void AKeyBindings::RemoveBinding(FBlueprintActionBinding& OldMapping)
{
	Settings->RemoveActionMapping(ToFInputActionKeyMapping(OldMapping));
}

FBlueprintActionBinding AKeyBindings::FromFInputActionKeyMapping(FInputActionKeyMapping & Mapping)
{
	FBlueprintActionBinding Result;
	Result.ActionName = Mapping.ActionName;
	Result.bAlt = Mapping.bAlt;
	Result.bCmd = Mapping.bCmd;
	Result.bCtrl = Mapping.bCtrl;
	Result.bShift = Mapping.bShift;
	Result.Key = Mapping.Key;

	return Result;
}

FInputActionKeyMapping AKeyBindings::ToFInputActionKeyMapping(FBlueprintActionBinding & Mapping)
{
	FInputActionKeyMapping Result;

	Result.ActionName = Mapping.ActionName;
	Result.bAlt = Mapping.bAlt;
	Result.bCmd = Mapping.bCmd;
	Result.bCtrl = Mapping.bCtrl;
	Result.bShift = Mapping.bShift;
	Result.Key = Mapping.Key;

	return Result;
}

