// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_CubeSlots.h"

#include "Components/BoxComponent.h"


// Sets default values
APuzzle_CubeSlots::APuzzle_CubeSlots()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	
}

// Called when the game starts or when spawned
void APuzzle_CubeSlots::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuzzle_CubeSlots::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

