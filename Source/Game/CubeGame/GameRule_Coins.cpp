// Fill out your copyright notice in the Description page of Project Settings.


#include "GameRule_Coins.h"

#include "Kismet/GameplayStatics.h"
#include "Puzzles/Puzzle_Coins.h"


// Sets default values for this component's properties
UGameRule_Coins::UGameRule_Coins()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
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

	// ...
	
}

void UGameRule_Coins::CoinCollected()
{
	_CoinsCollected++;

	if(_CoinsCollected >= _FoundCoins.Num())
	{
		OnComplete.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("AllCoinsCollected"));
		
	}
}


// Called every frame
void UGameRule_Coins::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

