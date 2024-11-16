// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_CubeSlots.h"

#include "Components/BoxComponent.h"
#include "Game/CubeGame/CubeType.h"
#include "Game/CubeGame/PawnInterface.h"
#include "Game/CubeGame/PlayerControllerInterface.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
APuzzle_CubeSlots::APuzzle_CubeSlots()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	_BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	_BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &APuzzle_CubeSlots::CubeEntered);
	_BoxComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &APuzzle_CubeSlots::CubeLeft);
	RootComponent = _BoxComponent;
	_StaticMesh->SetupAttachment(_BoxComponent);
	_StaticMesh->AddRelativeLocation(FVector(0,0,0.1)); //Keeps the slot above the ground
}

APuzzle_CubeSlots* APuzzle_CubeSlots::GetCubeSlot_Implementation()
{
	return this;
}

// Called when the game starts or when spawned
void APuzzle_CubeSlots::BeginPlay()
{
	Super::BeginPlay();
	_PlayerController = GetWorld()->GetFirstPlayerController();
	_StaticMesh->SetMaterial(0, _CubeType->_CubeMaterial);
}

void APuzzle_CubeSlots::CubeEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UPawnInterface::StaticClass()) && !bValidActor)
	{
		_ActorsOnPlatform.AddUnique(OtherActor);
		
		if(IPawnInterface::Execute_ReturnCubeType(OtherActor) == _CubeType->UniqueID) //may be able to convert back from ID
		{
			bValidActor = true;
			OnValidActor.Broadcast(bValidActor); //Needs bool
		}
	}
	
	
}

void APuzzle_CubeSlots::CubeLeft(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bValidActor = false;
	OnValidActor.Broadcast(bValidActor);
	_ActorsOnPlatform.Remove(OtherActor);
}

//When cube step off remove from array and broadcast false

// Called every frame
void APuzzle_CubeSlots::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

