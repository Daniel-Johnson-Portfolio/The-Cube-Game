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

	virtual void StartGameInstance() override;
	void OnPostLoadMap(UWorld* LoadedWorld);
	virtual void Init() override;

	void BeginPlay();

	UFUNCTION()
	void NextLevel();
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "LevelData")
	int _CurrentLevel = 0;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "LevelData")
	ACubeGamemode* _CurrentGameMode;
};
