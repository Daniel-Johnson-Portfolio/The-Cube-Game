// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeGamemode.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

AActor* ACubeGamemode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if(_PlayerStarts.Num() == 0)
	{
		TArray<AActor*> foundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), foundActors);
		for(AActor* actor : foundActors)
		{
			_PlayerStarts.Add(actor);
		}
	}
	if(_PlayerStarts.Num() > 0)
	{
		return _PlayerStarts[FMath::RandRange(0, _PlayerStarts.Num()-1)];
	}
	return nullptr;
}

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
