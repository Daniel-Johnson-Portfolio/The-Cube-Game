// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CubeGamemode.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GAME_API ACubeGamemode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

protected:
	TArray<TObjectPtr<AActor>> _PlayerStarts;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<AController>> _PlayerControllers;
};
