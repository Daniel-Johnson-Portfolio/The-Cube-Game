// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_CubeSlots.h"

#include "Components/BoxComponent.h"
#include "Game/CubeGame/PawnInterface.h"
#include "Game/CubeGame/PlayerControllerInterface.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
APuzzle_CubeSlots::APuzzle_CubeSlots()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	_BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &APuzzle_CubeSlots::CubeEntered);
}

// Called when the game starts or when spawned
void APuzzle_CubeSlots::BeginPlay()
{
	Super::BeginPlay();
	_PlayerController = GetWorld()->GetFirstPlayerController();
	
}

void APuzzle_CubeSlots::CubeEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UPawnInterface::StaticClass()))
	{
		_ActorsOnPlatform.AddUnique(OtherActor);
		if(IPawnInterface::Execute_ReturnCubeType(OtherActor) == _CubeType)
		{
			bValidActor = true;
			
		}
	}
	
	
}

// Called every frame
void APuzzle_CubeSlots::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

