// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeGamemode.h"

#include "CubeGameInstance.h"
#include "GameInstanceInterface.h"
#include "GameRule_Coins.h"
#include "PlayerControllerInterface.h"
#include "PlayerController_Cube.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"



void ACubeGamemode::PostLogin(APlayerController* NewPlayer)
{
	_PlayerControllers.AddUnique(NewPlayer);
	Super::PostLogin(NewPlayer);
}

void ACubeGamemode::Logout(AController* Exiting)
{
	_PlayerControllers.Remove(Exiting);
	Super::Logout(Exiting);
}

void ACubeGamemode::BeginPlay()
{
	if(UKismetSystemLibrary::DoesImplementInterface(GetWorld()->GetFirstPlayerController(), UPlayerControllerInterface::StaticClass()))
	{
		_PlayerController = IPlayerControllerInterface::Execute_GetPlayerController(GetWorld()->GetFirstPlayerController());
		_PlayerController->OnStacked.AddUniqueDynamic(this, &ACubeGamemode::CubesStacked);
	}
	
	if(UKismetSystemLibrary::DoesImplementInterface(GetComponentByClass(UGameRule_Coins::StaticClass()), UCoinGameRuleInterface::StaticClass()))
	{
		_CoinGameRule = ICoinGameRuleInterface::Execute_GetGameRule(GetComponentByClass(UGameRule_Coins::StaticClass()));
		_CoinGameRule->OnCoinCollected.AddUniqueDynamic(this, &ACubeGamemode::CoinCollected);
		_CoinGameRule->OnComplete.AddUniqueDynamic(this, &ACubeGamemode::AllCoinsCollected);
	}

	OnGamemodeLoaded.Broadcast();
	Super::BeginPlay();
}

ACubeGamemode* ACubeGamemode::GetGameMode_Implementation()
{
	return this;
}

void ACubeGamemode::LoadLevelInternal(int LevelNum)
{
	if(Levels.Num() >= LevelNum)
	{
		UGameplayStatics::OpenLevel(this, Levels[LevelNum], true, FString());
	}
	
}

void ACubeGamemode::LoadNextLevel_Implementation(int LevelNum)
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateUObject(this, &ACubeGamemode::LoadLevelInternal, LevelNum), 5, false);
}

void ACubeGamemode::SetCoins_Implementation(int Coins)
{
	IPlayerControllerInterface::Execute_SetCoins(_PlayerController, Coins);
}

void ACubeGamemode::AllCoinsCollected()
{
	bHasCollectedAllCoins = true;
	IPlayerControllerInterface::Execute_AllCoinsCollected(_PlayerController);
}

void ACubeGamemode::CoinCollected(int coinsInGameRule)
{
	OnNeedCoins.Broadcast(coinsInGameRule);
}


void ACubeGamemode::LevelCompleted()
{
	IPlayerControllerInterface::Execute_EnableWinText(_PlayerController);
	OnLevelEnd.Broadcast();
}

void ACubeGamemode::CubesStacked()
{
	bCubesAreStacked = true;
	if(bHasCollectedAllCoins && bCubesAreStacked)
	{
		LevelCompleted();
	}
}

