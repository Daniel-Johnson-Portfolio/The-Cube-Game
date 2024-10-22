﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeBase.h"

#include "Camera/CameraComponent.h"


// Sets default values
ACubeBase::ACubeBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	_StaticMesh->SetupAttachment(RootComponent);
	_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	_SpringArm->SetupAttachment(_StaticMesh);
	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(_SpringArm);
}

// Called when the game starts or when spawned
void ACubeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UInputMappingContext* ACubeBase::GetMappingContext_Implementation()
{
	return _InputMapping;
}

void ACubeBase::Input_JumpPressed_Implementation()
{
	ACubeBase::Jump();
}

void ACubeBase::Input_JumpReleased_Implementation()
{
	ACubeBase::StopJumping();
}

void ACubeBase::Input_Look_Implementation(FVector2D Value)
{
	UE_LOG(LogTemp, Display, TEXT("X: %f Y: %f"), Value.X, Value.Y);
	AddActorWorldRotation(FRotator(0.0f, Value.X, 0.0f));
	_StaticMesh->AddLocalRotation(FRotator(0.0f, Value.X, 0.0f));
	_SpringArm->SetRelativeRotation(FRotator(0.0f, FMath::Clamp(_SpringArm->GetRelativeRotation().Pitch + Value.Y, -30.0f, 30.0f), _SpringArm->GetRelativeRotation().Yaw));
}

void ACubeBase::Input_Move_Implementation(FVector2D Value)
{
	AddMovementInput(FVector::VectorPlaneProject(_Camera->GetForwardVector(), FVector::UpVector).GetSafeNormal(), Value.Y);
	AddMovementInput(GetActorRightVector(), Value.X);
}

// Called every frame
void ACubeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACubeBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
