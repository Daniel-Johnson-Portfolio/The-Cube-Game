// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeGameInstance.h"

#include "CubeGamemode.h"
#include "GameModeInterface.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UCubeGameInstance::OnPostLoadMap(UWorld* LoadedWorld)
{
	if (!LoadedWorld || !LoadedWorld->GetAuthGameMode())
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode not available on PostLoadMap."));
		return;
	}
	
	if (UKismetSystemLibrary::DoesImplementInterface(LoadedWorld->GetAuthGameMode()->GetClass(), UGameModeInterface::StaticClass()))
	{
		_CurrentGameMode = IGameModeInterface::Execute_GetGameMode(LoadedWorld->GetAuthGameMode());
		if (_CurrentGameMode)
		{
			_CurrentGameMode->OnLevelEnd.AddUniqueDynamic(this, &UCubeGameInstance::NextLevel);
		}
	}
}

void UCubeGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Being."));
	// Bind to map load event
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UCubeGameInstance::OnPostLoadMap);
}

void UCubeGameInstance::NextLevel()
{
	_CurrentLevel ++;
	IGameModeInterface::Execute_LoadNextLevel(_CurrentGameMode, _CurrentLevel);
	
}
