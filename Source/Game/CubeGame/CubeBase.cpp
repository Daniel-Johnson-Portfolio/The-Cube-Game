// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeBase.h"

#include "CubeType.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/MovementComponent.h"


// Sets default values
ACubeBase::ACubeBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	
	_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = _StaticMesh;
	_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	_SpringArm->SetupAttachment(_StaticMesh);
	_SpringArm->SetRelativeLocation(FVector(-30, 0, 100));
	
	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(_SpringArm);
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/SM_Cube"));
	_StaticMesh->SetStaticMesh(MeshObj.Object);

	_StaticMesh->SetSimulatePhysics(true);
	
	_StaticMesh->BodyInstance.bLockXRotation = true;
	_StaticMesh->BodyInstance.bLockYRotation = true;
}

void ACubeBase::Init(UCubeType* type)
{
	_CubeType = type;
	_StaticMesh->SetMaterial(0, type->_CubeMaterial);
	
	FTransform NewTransform;
	NewTransform.SetScale3D(type->_CubeSize);
	_StaticMesh->SetRelativeTransform(NewTransform);
	UE_LOG(LogTemp, Display, TEXT("INITRAN"));
}


// Called when the game starts or when spawned
void ACubeBase::BeginPlay()
{
	Super::BeginPlay();
	
}
void ACubeBase::Input_JumpPressed_Implementation()
{
	//ACubeBase::Jump();
}

void ACubeBase::Input_JumpReleased_Implementation()
{
	//ACubeBase::StopJumping();
}

void ACubeBase::Input_Look_Implementation(FVector2D Value)
{
	AddActorWorldRotation(FRotator(0.0f, Value.X, 0.0f));
	_StaticMesh->AddLocalRotation(FRotator(0.0f, Value.X, 0.0f));
	_SpringArm->SetRelativeRotation(FRotator(FMath::Clamp(_SpringArm->GetRelativeRotation().Pitch + Value.Y, -_CameraPitchLimit, _CameraPitchLimit), _SpringArm->GetRelativeRotation().Yaw , 0.0f));
}

void ACubeBase::Input_Move_Implementation(FVector2D Value)
{
    FVector _ForwardVector = _Camera->GetForwardVector();  
    FVector _RightVector = _Camera->GetRightVector();       
	
    _ForwardVector = FVector::VectorPlaneProject(_ForwardVector, FVector::UpVector).GetSafeNormal();
    _RightVector = FVector::VectorPlaneProject(_RightVector, FVector::UpVector).GetSafeNormal();
	
    FVector _MovementDirection = (_ForwardVector * Value.Y + _RightVector * Value.X).GetSafeNormal();
	
    FVector _MovementOffset = _MovementDirection * _Movementspeed * GetWorld()->GetDeltaSeconds();
	
	_StaticMesh->AddWorldOffset((_MovementOffset));
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

void ACubeBase::SetLocaiton(FVector location)
{
	_StaticMesh->SetWorldLocation(location);
}

