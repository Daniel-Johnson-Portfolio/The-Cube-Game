// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

AActor* AMyGameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
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

void AMyGameMode::PostLogin(APlayerController* NewPlayer)
{
	_PlayerControllers.AddUnique(NewPlayer);
	Super::PostLogin(NewPlayer);
}

void AMyGameMode::Logout(AController* Exiting)
{
	_PlayerControllers.Remove(Exiting);
	Super::Logout(Exiting);
}

void AMyGameMode::HandleMatchIsWaitingToStart()
{
	StartMatch();
	Super::HandleMatchIsWaitingToStart();
}

void AMyGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
}

void AMyGameMode::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();
}

void AMyGameMode::OnMatchStateSet()
{
	FString output;
	if(MatchState == MatchState::WaitingToStart)
	{
		output = "Waiting To Start";
	}
	else if(MatchState == MatchState::InProgress)
	{
		output = "InProgress";
	}
	else if(MatchState == MatchState::WaitingPostMatch)
	{
		output = "Waiting Post Match";
	}
	else if(MatchState == MatchState::LeavingMap)
	{
		output = "Leaving Map";
	}
 
	UE_LOG(LogTemp, Display, TEXT("MATCH STATE CHANGED: %s"), *output);
    
	Super::OnMatchStateSet();
}

bool AMyGameMode::ReadyToStartMatch_Implementation()
{
	return false;
}

bool AMyGameMode::ReadyToEndMatch_Implementation()
{
	return false;
}
