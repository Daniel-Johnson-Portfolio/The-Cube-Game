// Fill out your copyright notice in the Description page of Project Settings.


#include "GameRule_CubeSlots.h"

#include "Puzzles/Puzzle_CubeSlots.h"


// Sets default values for this component's properties
UGameRule_CubeSlots::UGameRule_CubeSlots()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UGameRule_CubeSlots::BeginPlay()
{
	Super::BeginPlay();

///	APuzzle_CubeSlots::OnValidActor.AddUniqueDynamic(this, &UGameRule_CubeSlots::AddValidActor);

	// ...
	
}

void UGameRule_CubeSlots::AddValidActor()
{
}


// Called every frame
void UGameRule_CubeSlots::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

