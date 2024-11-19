// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeGamemode.h"

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
		IPlayerControllerInterface::Execute_SetCoins(_PlayerController, _Coins);
	}

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
	_Coins = Coins;
}

void ACubeGamemode::AllCoinsCollected_Implementation()
{
	bHasCollectedAllCoins = true;
	IPlayerControllerInterface::Execute_AllCoinsCollected(_PlayerController);
}

void ACubeGamemode::CoinCollected_Implementation()
{
	_Coins++;
	IPlayerControllerInterface::Execute_SetCoins(_PlayerController, _Coins);
	OnCoinCollected.Broadcast();
}

void ACubeGamemode::LevelCompleted()
{
	IPlayerControllerInterface::Execute_EnableWinText(_PlayerController);
	OnLevelEnd.Broadcast();
}

void ACubeGamemode::CubesStacked()
{
	bCubesAreStacked = true;
	UE_LOG(LogTemp, Warning, TEXT("CUBES STACKED"));
	if(bHasCollectedAllCoins && bCubesAreStacked)
	{
		LevelCompleted();
	}
}

