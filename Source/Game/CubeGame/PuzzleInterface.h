﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PuzzleInterface.generated.h"

class APuzzle_Coins;
class APuzzle_CubeSlots;
class UCubeSlots_Component;
// This class does not need to be modified.
UINTERFACE()
class UPuzzleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAME_API IPuzzleInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	APuzzle_CubeSlots* GetCubeSlot();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	APuzzle_Coins* GetCoin();
};
