// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CubeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UCubeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "LevelData")
	int _CurrentLevel = 0;
};
