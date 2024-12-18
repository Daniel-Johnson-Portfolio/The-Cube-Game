﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerControllerInterface.generated.h"

class APlayerController_Cube;
// This class does not need to be modified.
UINTERFACE()
class UPlayerControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class GAME_API IPlayerControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CubesOnPlatform(int Amount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetCombineCubeSize();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	APlayerController_Cube* GetPlayerController();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetCoins(int coins);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EnableWinText();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AllCoinsCollected();
	
};
