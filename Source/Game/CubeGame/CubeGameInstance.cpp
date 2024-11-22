// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeGameInstance.h"

#include "CubeGamemode.h"
#include "GameModeInterface.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"

int UCubeGameInstance::getCoins_Implementation()
{
	return _LevelcoinsCollected;
}


void UCubeGameInstance::OnPostLoadMap(const FActorsInitializedParams& Params)
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode())
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode not available on PostLoadMap."));
		return;
	}
	if (UKismetSystemLibrary::DoesImplementInterface(GetWorld()->GetAuthGameMode(), UGameModeInterface::StaticClass()))
	{
		_CurrentGameMode = IGameModeInterface::Execute_GetGameMode(GetWorld()->GetAuthGameMode());
		_CurrentGameMode->OnLevelEnd.AddUniqueDynamic(this, &UCubeGameInstance::NextLevel);
		_CurrentGameMode->OnNeedCoins.AddUniqueDynamic(this, &UCubeGameInstance::CoinCollected);
		_CurrentGameMode->OnGamemodeLoaded.AddUniqueDynamic(this, &UCubeGameInstance::setCoins);
	}
}

void UCubeGameInstance::Init()
{
	Super::Init();
	
	FWorldDelegates::OnWorldInitializedActors.AddUObject(this, &UCubeGameInstance::OnPostLoadMap);
}

void UCubeGameInstance::NextLevel()
{
	_GamecoinsCollected += _LevelcoinsCollected;
	_LevelcoinsCollected = 0;
	_CurrentLevel++;
	UE_LOG(LogTemp, Warning, TEXT("Level Number %d"), _CurrentLevel);
	IGameModeInterface::Execute_LoadNextLevel(_CurrentGameMode, _CurrentLevel);
}

void UCubeGameInstance::CoinCollected(int coins)
{
	_LevelcoinsCollected++;
	UE_LOG(LogTemp, Warning, TEXT("Coins %d"), _GamecoinsCollected + coins);
	IGameModeInterface::Execute_SetCoins(_CurrentGameMode, _GamecoinsCollected + coins);
}

void UCubeGameInstance::setCoins()
{
	IGameModeInterface::Execute_SetCoins(_CurrentGameMode, _GamecoinsCollected);
}

