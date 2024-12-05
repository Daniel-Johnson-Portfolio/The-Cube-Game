// Fill out your copyright notice in the Description page of Project Settings.


#include "GameRule_CubeSlots.h"


UGameRule_CubeSlots::UGameRule_CubeSlots()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UGameRule_CubeSlots::BeginPlay()
{
	Super::BeginPlay();
	
}

void UGameRule_CubeSlots::AddValidActor()
{
}


// Called every frame
void UGameRule_CubeSlots::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

