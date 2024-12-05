// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeInterface.h"
#include "GameFramework/GameMode.h"
#include "CubeGamemode.generated.h"

class UGameRule_Coins;
class APlayerController_Cube;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndOfLevelSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNeedTotalCoinsSignature, int, coins);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGamemodeIsReadySignature);
UCLASS(Abstract)
class GAME_API ACubeGamemode : public AGameMode, public IGameModeInterface
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UGameRule_Coins* _CoinGameRule;

	FGamemodeIsReadySignature OnGamemodeLoaded;
	FNeedTotalCoinsSignature OnNeedCoins;
	FEndOfLevelSignature OnLevelEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	TArray<FName> Levels;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	virtual void BeginPlay() override;

	virtual ACubeGamemode* GetGameMode_Implementation() override;

	void LoadLevelInternal(int LevelNum);
	
	virtual void LoadNextLevel_Implementation(int LevelNum) override;

	virtual void SetCoins_Implementation(int Coins) override;

	UFUNCTION()
	void AllCoinsCollected();

	UFUNCTION()
	void CoinCollected(int coinsInGameRule);

	void LevelCompleted();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int _Coins;
	
	TArray<TObjectPtr<AActor>> _PlayerStarts;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<AController>> _PlayerControllers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APlayerController_Cube* _PlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHasCollectedAllCoins;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCubesAreStacked;

	UFUNCTION()
	void CubesStacked();
	
};
