// Fill out your copyright notice in the Description page of Project Settings.


#include "GameRule_Coins.h"

#include "Kismet/GameplayStatics.h"
#include "Puzzles/Puzzle_Coins.h"


// Sets default values for this component's properties
UGameRule_Coins::UGameRule_Coins()
{
	PrimaryComponentTick.bCanEverTick = false;
}


UGameRule_Coins* UGameRule_Coins::GetGameRule_Implementation()
{
	return this;
}

// Called when the game starts
void UGameRule_Coins::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APuzzle_Coins::StaticClass(), _FoundCoins);

	for(AActor* coin : _FoundCoins)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(coin, UPuzzleInterface::StaticClass()))
		{
			APuzzle_Coins* Coin = IPuzzleInterface::Execute_GetCoin(coin);
			Coin->OnCoinCollected.AddUniqueDynamic(this, &UGameRule_Coins::CoinCollected);
		}
	}
	
}

void UGameRule_Coins::CoinCollected()
{
	_CoinsCollected++;
	OnCoinCollected.Broadcast(_CoinsCollected);
	if(_CoinsCollected >= _FoundCoins.Num())
	{
		OnComplete.Broadcast();
	}
}

// Called every frame
void UGameRule_Coins::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

