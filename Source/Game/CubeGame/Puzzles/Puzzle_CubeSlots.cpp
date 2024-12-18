﻿// Fill out your copyright notice in the Description page of Project Settings.


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

void APuzzle_CubeSlots::OnValidActorHook_Implementation(bool valid)
{
	//Designer hook
}

// Called when the game starts or when spawned
void APuzzle_CubeSlots::BeginPlay()
{
	Super::BeginPlay();
	_PlayerController = GetWorld()->GetFirstPlayerController();
	_StaticMesh->SetMaterial(0, _CubeType->_CubeMaterial);
	OnValidActor.AddUniqueDynamic(this, &APuzzle_CubeSlots::OnValidActorHook);
	
}

void APuzzle_CubeSlots::CubeEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UPawnInterface::StaticClass()) && !bValidActor)
	{
		if(IPawnInterface::Execute_ReturnCubeType(OtherActor) == _CubeType->UniqueID)
		{
			bValidActor = true;
			OnValidActor.Broadcast(bValidActor);
			UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),_SlotVFX,GetActorLocation(),FRotator::ZeroRotator,FVector(1.0f));
			FLinearColor BaseColor;
			
		   if (_CubeType->_CubeMaterial->GetVectorParameterValue(FName("Colour"), BaseColor) && bVFXAdoptsColour)
		   {
			   NiagaraComponent->SetVariableLinearColor(TEXT("Color"), BaseColor);
		   }
		}
	}
}

void APuzzle_CubeSlots::CubeLeft(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UPawnInterface::StaticClass()) && bValidActor)
	{
			if(IPawnInterface::Execute_ReturnCubeType(OtherActor) == _CubeType->UniqueID)
			{
				bValidActor = false;
				OnValidActor.Broadcast(bValidActor);
			}
	}
}

void APuzzle_CubeSlots::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

