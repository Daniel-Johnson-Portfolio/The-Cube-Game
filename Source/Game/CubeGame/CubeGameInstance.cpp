// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeGameInstance.h"

#include "CubeGamemode.h"
#include "GameModeInterface.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"

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
		IGameModeInterface::Execute_SetCoins(_CurrentGameMode, _coinsCollected);
		_CurrentGameMode->OnLevelEnd.AddUniqueDynamic(this, &UCubeGameInstance::NextLevel);
		_CurrentGameMode->OnCoinCollected.AddUniqueDynamic(this, &UCubeGameInstance::CoinCollected);
	}
}

void UCubeGameInstance::Init()
{
	Super::Init();
	FWorldDelegates::OnWorldInitializedActors.AddUObject(this, &UCubeGameInstance::OnPostLoadMap);
	
}

void UCubeGameInstance::NextLevel()
{
	_CurrentLevel++;
	IGameModeInterface::Execute_LoadNextLevel(_CurrentGameMode, _CurrentLevel);
}

void UCubeGameInstance::CoinCollected()
{
	_coinsCollected++;
	UE_LOG(LogTemp, Warning, TEXT("Coins %d"), _coinsCollected);
}
