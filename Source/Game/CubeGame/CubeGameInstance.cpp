// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeGameInstance.h"

#include "CubeGamemode.h"
#include "GameModeInterface.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UCubeGameInstance::OnPostLoadMap(const FActorsInitializedParams& Params)
{
	UE_LOG(LogTemp, Warning, TEXT("BBBBBB"));
	
	if (!GetWorld() || !GetWorld()->GetAuthGameMode())
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode not available on PostLoadMap."));
		return;
	}
	
	if (UKismetSystemLibrary::DoesImplementInterface(GetWorld()->GetAuthGameMode(), UGameModeInterface::StaticClass()))
	{
		_CurrentGameMode = IGameModeInterface::Execute_GetGameMode(GetWorld()->GetAuthGameMode());
		_CurrentGameMode->OnLevelEnd.AddUniqueDynamic(this, &UCubeGameInstance::NextLevel);
		UE_LOG(LogTemp, Warning, TEXT("AAAAAAAA"));
	}
	UE_LOG(LogTemp, Warning, TEXT("GameMode Class Name: %s"), *GetWorld()->GetAuthGameMode()->GetClass()->GetName());
}

void UCubeGameInstance::Init()
{
//	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UCubeGameInstance::OnPostLoadMap);
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Being."));
	// Bind to map load event
//	FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UCubeGameInstance::OnPostLoadMap);
	FWorldDelegates::OnWorldInitializedActors.AddUObject(this, &UCubeGameInstance::OnPostLoadMap);
	
}

void UCubeGameInstance::NextLevel()
{
	_CurrentLevel++;
	IGameModeInterface::Execute_LoadNextLevel(_CurrentGameMode, _CurrentLevel);
	UE_LOG(LogTemp, Warning, TEXT("SENT"));
	
}
