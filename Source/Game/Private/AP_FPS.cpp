﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AP_FPS.h"

#include "HealthComponent.h"
#include "Camera/CameraComponent.h"

UInputMappingContext* AAP_FPS::GetMappingContext_Implementation()
{
	return _InputMapping;
}

void AAP_FPS::Input_FirePressed_Implementation()
{
	if(_WeaponRef)
	{
		_WeaponRef->StartFire();
	}
}

void AAP_FPS::Input_FireReleased_Implementation()
{
	if(_WeaponRef)
	{
		_WeaponRef->StopFire();
	}
}

void AAP_FPS::Input_JumpPressed_Implementation()
{
	ACharacter::Jump();
}

void AAP_FPS::Input_JumpReleased_Implementation()
{
	ACharacter::StopJumping();
}

void AAP_FPS::Input_Look_Implementation(FVector2D Value)
{
	UE_LOG(LogTemp, Display, TEXT("X: %f Y: %f"), Value.X, Value.Y);
	AddActorWorldRotation(FRotator(0.0f, Value.X, 0.0f));
	_Camera->AddLocalRotation(FRotator(Value.Y, 0.0f, 0.0f));
}

void AAP_FPS::Input_Move_Implementation(FVector2D Value)
{
	AddMovementInput(FVector::VectorPlaneProject(_Camera->GetForwardVector(), FVector::UpVector).GetSafeNormal(), Value.Y);
	AddMovementInput(GetActorRightVector(), Value.X);
}

void AAP_FPS::PossessedBy(AController* NewController)
{
	//_PlayerController = Cast<APC_FPS, AController>(NewController);
	Super::PossessedBy(NewController);
	
}
void AAP_FPS::Handle_HealthDamaged(float current, float max, float change)
{
	UE_LOG(LogTemp, Display, TEXT("Damage for AP %f"), change);
	OnPawnDamaged.Broadcast(change);
}

void AAP_FPS::Handle_HealthDead(AController* causer)
{
	
}

// Sets default values
AAP_FPS::AAP_FPS()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	_WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Attach"));
	_WeaponAttachPoint->SetupAttachment(_Camera);
}

// Called when the game starts or when spawned
void AAP_FPS::BeginPlay()
{
	Super::BeginPlay();
	_Health->OnDamaged.AddUniqueDynamic(this, &AAP_FPS::Handle_HealthDamaged);
	_Health->OnDead.AddUniqueDynamic(this, &AAP_FPS::Handle_HealthDead);
	if(_DefaultWeapon)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = this;
		_WeaponRef = GetWorld()->SpawnActor<AWeapon_Base>(_DefaultWeapon, _WeaponAttachPoint->GetComponentTransform(), spawnParams);
		_WeaponRef->AttachToComponent(_WeaponAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
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

