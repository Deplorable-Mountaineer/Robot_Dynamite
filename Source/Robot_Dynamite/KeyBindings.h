// (C) 2017 Todd D. Vance

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerInput.h"
#include "KeyBindings.generated.h"

USTRUCT()
struct FBlueprintActionBinding
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Bindings")
		FName ActionName;

	UPROPERTY(BlueprintReadOnly, Category = "Bindings")
		bool bAlt;

	UPROPERTY(BlueprintReadOnly, Category = "Bindings")
		bool bCmd;

	UPROPERTY(BlueprintReadOnly, Category = "Bindings")
		bool bCtrl;

	UPROPERTY(BlueprintReadOnly, Category = "Bindings")
		bool bShift;

	UPROPERTY(BlueprintReadOnly, Category = "Bindings")
		FKey Key;

};

UCLASS()
class ROBOT_DYNAMITE_API AKeyBindings : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyBindings();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Bindings")
		TArray<struct FBlueprintActionBinding> GetActionBindings(FName ActionName);
	
	UFUNCTION(BlueprintCallable, Category = "Bindings")
		void ApplyBindings();

	UFUNCTION(BlueprintCallable, Category = "Bindings")
		void AddNewBinding(struct FBlueprintActionBinding& NewMapping);

	UFUNCTION(BlueprintCallable, Category = "Bindings")
		void RemoveBinding(struct FBlueprintActionBinding& OldMapping);

private:
	class UInputSettings* Settings;

	struct FBlueprintActionBinding FromFInputActionKeyMapping(struct FInputActionKeyMapping& Mapping);
	struct FInputActionKeyMapping ToFInputActionKeyMapping(struct FBlueprintActionBinding& Mapping);
};

