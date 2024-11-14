// Fill out your copyright notice in the Description page of Project Settings.


#include "GameRuleBase.h"


// Sets default values for this component's properties
UGameRuleBase::UGameRuleBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UGameRuleBase::BroadcastComplete()
{
	OnComplete.Broadcast();
	
}

// Called when the game starts
void UGameRuleBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGameRuleBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

