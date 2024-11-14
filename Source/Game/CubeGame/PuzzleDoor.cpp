// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleDoor.h"


// Sets default values
APuzzleDoor::APuzzleDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = _StaticMeshComponent;
}

// Called when the game starts or when spawned
void APuzzleDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void APuzzleDoor::OpenDoor_Implementation()
{
	if (!GetWorld()->GetTimerManager().IsTimerActive(MovementCheckTimer))
	{
		GetWorld()->GetTimerManager().SetTimer(MovementCheckTimer, this, &APuzzleDoor::DoorMovement, 0.01f, true);
	
	}
	
	
}

void APuzzleDoor::DoorMovement()
{
	NewLocation = FMath::VInterpTo(this->GetActorLocation(), this->GetActorLocation() + FVector(0,0, _DoorOpenHeight), GetWorld()->GetDeltaSeconds(), 3.0f);
	this->SetActorLocation(NewLocation);

	if(this->GetActorLocation().Z >= _DoorOpenHeight)
	{
		GetWorld()->GetTimerManager().ClearTimer(MovementCheckTimer);
		UE_LOG(LogTemp, Log, TEXT("DoorStopped"));
	}
}


// Called every frame
void APuzzleDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

