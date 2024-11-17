// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeInterface.h"
#include "GameFramework/GameMode.h"
#include "CubeGamemode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndOfLevelSignature);

UCLASS(Abstract)
class GAME_API ACubeGamemode : public AGameMode, public IGameModeInterface
{
	GENERATED_BODY()

public:

	FEndOfLevelSignature OnLevelEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	TArray<FName> Levels;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	virtual void BeginPlay() override;

	virtual ACubeGamemode* GetGameMode_Implementation() override;

	virtual void LoadNextLevel_Implementation(int LevelNum) override;

	virtual void AllCoinsCollected_Implementation() override;

	void LevelCompleted();

protected:
	TArray<TObjectPtr<AActor>> _PlayerStarts;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<AController>> _PlayerControllers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHasCollectedAllCoins;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCubesAreStacked;

	UFUNCTION()
	void CubesStacked();
};
