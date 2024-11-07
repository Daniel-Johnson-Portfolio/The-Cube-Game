// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Cube.h"

#include "Inputs.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AAIController_Cube::AAIController_Cube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAIController_Cube::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIController_Cube::OnPossess(APawn* InPawn)
{
	RunBehaviorTree(_BehaviourTree);
	UE_LOG(LogTemp, Warning, TEXT("TREE RUN"));
	Super::OnPossess(InPawn);
	
}

// Called every frame
void AAIController_Cube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

