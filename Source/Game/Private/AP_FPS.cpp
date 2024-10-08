// Fill out your copyright notice in the Description page of Project Settings.


#include "AP_FPS.h"


// Sets default values
AAP_FPS::AAP_FPS()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAP_FPS::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAP_FPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAP_FPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

