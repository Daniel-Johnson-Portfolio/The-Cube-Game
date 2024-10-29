// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inputs.generated.h"


// This class does not need to be modified.
UINTERFACE()
class UInputs : public UInterface
{
	GENERATED_BODY()
};

class UInputMappingContext;
class GAME_API IInputs
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Look(FVector2D Value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Move(FVector2D Value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_JumpPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_JumpReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_AIMove(FVector Pos);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UInputMappingContext* GetMappingContext();
	
};
