﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameModeInterface.generated.h"

class ACubeGamemode;
// This class does not need to be modified.
UINTERFACE()
class UGameModeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAME_API IGameModeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AllCoinsCollected();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	ACubeGamemode* GetGameMode();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LoadNextLevel(int LevelNum);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CoinCollected();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetCoins(int Coins);
	
};