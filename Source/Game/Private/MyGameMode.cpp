// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "GameRule.h"
#include "PC_FPS.h"
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

void AMyGameMode::AddPoints(int Addby)
{
	Handle_GameRulePointsScored(UGameplayStatics::GetPlayerController(GetWorld(), 0) ,1  );
	
}

void AMyGameMode::DecreaseCountdown()
{
	_CountdownTimer--;
	UE_LOG(LogTemp, Display, TEXT("GAMEMODE Countdown: %d"), _CountdownTimer);
	if(_CountdownTimer == 0)
	{
		StartMatch();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(_TimerDecreaseCountdown, this, &AMyGameMode::DecreaseCountdown, 1.f, false);
	}
}

void AMyGameMode::HandleGameRuleCompleted()
{
}

void AMyGameMode::Handle_GameRulePointsScored(AController* scorer, int points)
{
	 Cast<APC_FPS>(scorer)->AddPointsToUI(points);
}

void AMyGameMode::HandleMatchIsWaitingToStart()
{
	TArray<UActorComponent*> outComponents;
	GetComponents(outComponents);
	for(UActorComponent* comp : outComponents)
	{
		if(UGameRule* rule = Cast<UGameRule>(comp))
		{
			_GameRuleManagers.Add(rule);
			rule->Init();
			rule->OnComplete.AddUniqueDynamic(this, &AMyGameMode::HandleGameRuleCompleted);
			rule->OnPointScored.AddUniqueDynamic(this, &AMyGameMode::Handle_GameRulePointsScored);
			_GameRulesLeft++;
			
		}
		
		GetWorld()->GetTimerManager().SetTimer(_TimerDecreaseCountdown, this, &AMyGameMode::DecreaseCountdown, 1.f, false);
		Super::HandleMatchIsWaitingToStart();
		
	}
	Super::HandleMatchIsWaitingToStart();
}

void AMyGameMode::HandleMatchHasStarted()
{
	DefaultPawnClass = _MatchPawn;
	for(AController* controller : _PlayerControllers)
	{
		RestartPlayer(controller);
	}
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
