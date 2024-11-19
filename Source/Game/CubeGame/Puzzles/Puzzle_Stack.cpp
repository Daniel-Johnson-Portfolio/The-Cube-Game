// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Stack.h"

#include "SkeletalMeshAttributes.h"
#include "CADKernel/UI/Display.h"
#include "CADKernel/UI/Display.h"
#include "Game/CubeGame/CubeBase.h"
#include "Game/CubeGame/PawnInterface.h"
#include "Game/CubeGame/PlayerControllerInterface.h"
#include "Game/CubeGame/PlayerController_Cube.h"
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
	PrimaryActorTick.bCanEverTick = false;

	_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = _StaticMeshComponent;
	;
	_StaticMeshComponent->SetStaticMesh(_StaticMesh);

	_OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Box"));
	_OverlapBox->SetBoxExtent(FVector(50,50,50));
	_OverlapBox->SetupAttachment(_StaticMeshComponent);
	
	_OverlapBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &APuzzle_Stack::ComponentEntered);
	_OverlapBox->OnComponentEndOverlap.AddUniqueDynamic(this, &APuzzle_Stack::ComponentExit);
	
	_StaticMeshComponent->SetMobility(EComponentMobility::Static);
	_OverlapBox->SetMobility(EComponentMobility::Static);
	//_PlaneExtents2D = FVector(_StaticMeshComponent->GetComponentScale().X * 50.0f, _StaticMeshComponent->GetComponentScale().Y * 50.0f, 0.0f);
	
}

// Called when the game starts or when spawned
void APuzzle_Stack::BeginPlay()
{
	Super::BeginPlay();
	
	if(UKismetSystemLibrary::DoesImplementInterface(GetWorld()->GetFirstPlayerController(), UPlayerControllerInterface::StaticClass()))
	{
		_PlayerController = IPlayerControllerInterface::Execute_GetPlayerController(GetWorld()->GetFirstPlayerController());
		_PlayerController->OnPlayerControllerReady.AddUniqueDynamic(this, &APuzzle_Stack::Init);
		_PlayerController->OnStacked.AddUniqueDynamic(this, &APuzzle_Stack::CancelTimer);
		
	}
	
	
}


void APuzzle_Stack::ComponentEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UPawnInterface::StaticClass()) && UKismetSystemLibrary::DoesImplementInterface(_PlayerController, UPlayerControllerInterface::StaticClass()))
	{
		_CubesOverlapped++;
		_OverlappedPawns.AddUnique(OtherActor);
        
		// Store the initial position of the actor
		InitialPositions.Add(OtherActor, OtherActor->GetActorLocation());

		// Start the timer to check for movement if it hasn't started
		if (!GetWorld()->GetTimerManager().IsTimerActive(MovementCheckTimer))
		{
			GetWorld()->GetTimerManager().SetTimer(MovementCheckTimer, this, &APuzzle_Stack::CheckForMovement, 2.0f, true);  // Check every 2 seconds
		}

		IPlayerControllerInterface::Execute_CubesOnPlatform(_PlayerController, _CubesOverlapped);
	}
}

void APuzzle_Stack::CheckForMovement()
{
	bool bAnyObjectMoved = false;

	for (auto& Elem : InitialPositions)
	{
		AActor* Actor = Elem.Key;
		FVector InitialPosition = Elem.Value;
        
		// Check if the actor is still valid and has moved
		if (Actor && Actor->GetActorLocation() != InitialPosition)
		{
			bAnyObjectMoved = true;
			UE_LOG(LogTemp, Warning, TEXT("%s has moved!"), *Actor->GetName());
			
			// Optionally update the position if you want to detect further movement
			InitialPositions[Actor] = Actor->GetActorLocation();
		}
	}

	if (!bAnyObjectMoved)
	{
		UE_LOG(LogTemp, Log, TEXT("No objects have moved."));
	}
	
	IPlayerControllerInterface::Execute_CubesOnPlatform(_PlayerController, _CubesOverlapped);
}

void APuzzle_Stack::CancelTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(MovementCheckTimer);
}

void APuzzle_Stack::Init()
{
	FVector Box = (IPlayerControllerInterface::Execute_GetCombineCubeSize(_PlayerController));
	_StaticMeshComponent->SetWorldScale3D(FVector(Box.X/50.0f, Box.Y/50.0f, Box.Z/50.0f)); //Scaling Down from extents to scale
	
}


void APuzzle_Stack::ComponentExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, UPawnInterface::StaticClass()) && UKismetSystemLibrary::DoesImplementInterface(_PlayerController, UPlayerControllerInterface::StaticClass()))
	{
		_CubesOverlapped--;
		_OverlappedPawns.Remove(OtherActor);
		InitialPositions.Remove(OtherActor);
		IPlayerControllerInterface::Execute_CubesOnPlatform(_PlayerController, _CubesOverlapped);
	}
}


// Called every frame
void APuzzle_Stack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

