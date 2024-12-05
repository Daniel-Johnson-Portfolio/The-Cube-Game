// Fill out your copyright notice in the Description page of Project Settings.


#include "GameRuleBase.h"


// Sets default values for this component's properties
UGameRuleBase::UGameRuleBase()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGameRuleBase::BroadcastComplete()
{
	OnComplete.Broadcast();
	
}

// Called when the game starts
void UGameRuleBase::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UGameRuleBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

