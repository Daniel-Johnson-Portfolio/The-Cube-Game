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
		Cast<APlayerController_Cube>(GetWorld()->GetFirstPlayerController())->OnStacked.AddUniqueDynamic(this, &ACubeGamemode::CubesStacked);
	}

	Super::BeginPlay();
}

ACubeGamemode* ACubeGamemode::GetGameMode_Implementation()
{
	return this;
}

void ACubeGamemode::LoadNextLevel_Implementation(int LevelNum)
{
	UE_LOG(LogTemp, Warning, TEXT("OPen Level %d"), LevelNum);
	UGameplayStatics::OpenLevel(this, Levels[LevelNum], true, FString());
}

void ACubeGamemode::AllCoinsCollected_Implementation()
{
	bHasCollectedAllCoins = true;
}

void ACubeGamemode::LevelCompleted()
{
	UE_LOG(LogTemp, Warning, TEXT("Level Completed"));
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
