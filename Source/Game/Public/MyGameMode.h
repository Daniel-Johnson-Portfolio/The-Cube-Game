 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

 class UGameRule;
/**
 * 
 */
UCLASS(Abstract)
class GAME_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Match Management")
	int _CountdownTimer;
	FTimerHandle _TimerDecreaseCountdown;
	UPROPERTY(EditAnywhere, Category="Match Management")
	TSubclassOf<APawn> _MatchPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _points;

	UFUNCTION(BlueprintCallable)
	void AddPoints(int Addby);
	
	UFUNCTION()
	void DecreaseCountdown();
	
	int _GameRulesLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UGameRule>> _GameRuleManagers;

	UFUNCTION()
	void HandleGameRuleCompleted();
	UFUNCTION()
	void Handle_GameRulePointsScored(AController* scorer, int points);

	
	TArray<TObjectPtr<AActor>> _PlayerStarts;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<AController>> _PlayerControllers;

	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;

	virtual void OnMatchStateSet() override;

	virtual bool ReadyToStartMatch_Implementation() override;
	virtual bool ReadyToEndMatch_Implementation() override;

	
};

