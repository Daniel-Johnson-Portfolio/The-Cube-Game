// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeSlots_Component.h"

#include "DoorInterface.h"
#include "PuzzleInterface.h"
#include "ToolBuilderUtil.h"
#include "Kismet/GameplayStatics.h"
#include "Puzzles/Puzzle_CubeSlots.h"


// Sets default values for this component's properties
UCubeSlots_Component::UCubeSlots_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCubeSlots_Component::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APuzzle_CubeSlots::StaticClass(), _FoundCubeSlots);

	for(AActor* puzzle : _FoundCubeSlots)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(puzzle, UPuzzleInterface::StaticClass()))
		{
			APuzzle_CubeSlots* CubeSlot = IPuzzleInterface::Execute_GetCubeSlot(puzzle);
			CubeSlot->OnValidActor.AddUniqueDynamic(this, &UCubeSlots_Component::ValidActor);
		}
	}

	// ...
	
}


void UCubeSlots_Component::ValidActor()
{
	_amountOfValidActors++;
	UE_LOG(LogTemp, Warning, TEXT("Actors %d"), _amountOfValidActors)
	if(_amountOfValidActors >= _FoundCubeSlots.Num())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(this->GetOwner(), UDoorInterface::StaticClass()))
		{
			IDoorInterface::Execute_OpenDoor(this->GetOwner());
			UE_LOG(LogTemp, Warning, TEXT("AllCubesOnPlats"));
			
		}
	}
}

// Called every frame
void UCubeSlots_Component::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

