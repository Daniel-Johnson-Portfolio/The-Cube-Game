// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameModeInterface.generated.h"

class ACubeGamemode;
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

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	ACubeGamemode* GetGameMode();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LoadNextLevel(int LevelNum);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetCoins(int Coins);
	
};
