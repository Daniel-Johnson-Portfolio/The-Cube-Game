// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Stack.h"

#include "SkeletalMeshAttributes.h"
#include "CADKernel/UI/Display.h"
#include "CADKernel/UI/Display.h"
#include "Game/CubeGame/CubeBase.h"
#include "Game/CubeGame/PawnInterface.h"
#include "Kismet/KismetSystemLibrary.h"


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

	_OverlapBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &APuzzle_Stack::ComponentEntered);

	_StaticMesh->SetMobility(EComponentMobility::Static);
	_OverlapBox->SetMobility(EComponentMobility::Static);
	_PlaneExtents2D = FVector(_StaticMesh->GetComponentScale().X * 50.0f, _StaticMesh->GetComponentScale().Y * 50.0f, 0.0f);
}

// Called when the game starts or when spawned
void APuzzle_Stack::BeginPlay()
{
	Super::BeginPlay();
	
}




void APuzzle_Stack::InterfaceToOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("PreInterface"));
	if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, UPawnInterface::StaticClass()))
	{
	
	}
}

void APuzzle_Stack::ComponentEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, UPawnInterface::StaticClass()))
	{
		_CubesOverlapped++;
		_OverlappedPawns.AddUnique(OtherActor);
		
		
	}
}

// Called every frame
void APuzzle_Stack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

