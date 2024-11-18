// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameRuleBase.h"
#include "GameRule_Coins.generated.h"


class ACubeGamemode;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAME_API UGameRule_Coins : public UGameRuleBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGameRule_Coins();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> _FoundCoins;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void CoinCollected();
	
	int _CoinsCollected;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
