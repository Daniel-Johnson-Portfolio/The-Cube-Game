// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Stack.h"


/*
*Cube makes trace when it lands (Once each land) and ignores cube type
if it gets the platform cache the reference to the platform and then interface to the platform saying "I have cache you"
when the platform has all the cubes check there Y(Z) level make sure none of them are the same level (Use nearly equal to and not == to create a buffer)
if none of them are the same level and all of them are present then condition complete
 *
 *
 */


// Sets default values
APuzzle_Stack::APuzzle_Stack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = _StaticMesh;
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/SM_Plane"));
	_StaticMesh->SetStaticMesh(MeshObj.Object);

	_OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Box"));
	_OverlapBox->SetBoxExtent(FVector(50,50,50));
	_OverlapBox->SetupAttachment(_StaticMesh);

	_OverlapBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &APuzzle_Stack::ScanForCubes);
	
	_PlaneExtents2D = FVector(_StaticMesh->GetComponentScale().X * 50.0f, _StaticMesh->GetComponentScale().Y * 50.0f, 0.0f);
}

// Called when the game starts or when spawned
void APuzzle_Stack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuzzle_Stack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

