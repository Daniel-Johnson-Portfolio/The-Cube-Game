// Fill out your copyright notice in the Description page of Project Settings.


#include "GameRule.h"


// Sets default values for this component's properties
UGameRule::UGameRule()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGameRule::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UGameRule::BroadcastComplete()
{
	OnComplete.Broadcast();
	
}

void UGameRule::BroadcastPointsScored(AController* causer, int points)
{
	OnPointScored.Broadcast(causer, points);
	
}


// Called every frame
void UGameRule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

