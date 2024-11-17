// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CubeGameInstance.generated.h"

class ACubeGamemode;
/**
 * 
 */
UCLASS()
class GAME_API UCubeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	void OnPostLoadMap(const FActorsInitializedParams& Params);
	virtual void Init() override;

	UFUNCTION()
	void NextLevel();
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "LevelData")
	int _CurrentLevel = 0;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "LevelData")
	ACubeGamemode* _CurrentGameMode;
};
