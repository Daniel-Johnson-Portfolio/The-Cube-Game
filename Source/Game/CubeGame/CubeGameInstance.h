// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameInstanceInterface.h"
#include "Engine/GameInstance.h"
#include "CubeGameInstance.generated.h"

class ACubeGamemode;
/**
 * 
 */
UCLASS()
class GAME_API UCubeGameInstance : public UGameInstance, public IGameInstanceInterface
{
	GENERATED_BODY()

public:

	virtual int getCoins_Implementation() override;
	void OnPostLoadMap(const FActorsInitializedParams& Params);
	
	virtual void Init() override;

	UFUNCTION()
	void NextLevel();

	UFUNCTION()
	void CoinCollected(int coin);
	
	UFUNCTION()
	void setCoins();
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "LevelData")
	int _CurrentLevel = 0;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "LevelData")
	int _MaxLevel; //This number should be provided via the gamemodes levels array.num

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "LevelData")
	ACubeGamemode* _CurrentGameMode;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "LevelData")
	int _GamecoinsCollected = 0;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "LevelData")
	int _LevelcoinsCollected = 0;
	
};
