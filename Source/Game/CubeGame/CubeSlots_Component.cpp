// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeSlots_Component.h"

#include "DoorInterface.h"
#include "PuzzleInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Puzzles/Puzzle_CubeSlots.h"


// Sets default values for this component's properties
UCubeSlots_Component::UCubeSlots_Component()
{
	PrimaryComponentTick.bCanEverTick = false;

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
	
}


void UCubeSlots_Component::ValidActor(bool bIsValidActor)
{
	switch (bIsValidActor)
	{
		case true:
			_amountOfValidActors++;
			if(_amountOfValidActors >= _FoundCubeSlots.Num() && !bhasAlreadyOpened)
			{
				if (UKismetSystemLibrary::DoesImplementInterface(this->GetOwner(), UDoorInterface::StaticClass()))
				{
					IDoorInterface::Execute_OpenDoor(this->GetOwner());
					bhasAlreadyOpened = true;
				}
			}
		break;

		
		case false:
			_amountOfValidActors--;
		break;
	}

}

// Called every frame
void UCubeSlots_Component::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

