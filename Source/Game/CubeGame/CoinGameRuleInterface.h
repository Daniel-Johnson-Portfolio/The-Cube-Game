// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CoinGameRuleInterface.generated.h"

class UGameRule_Coins;
// This class does not need to be modified.
UINTERFACE()
class UCoinGameRuleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAME_API ICoinGameRuleInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UGameRule_Coins* GetGameRule();
};
