// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeBase.h"
#include "CubeType.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ACubeBase::ACubeBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	
	RootComponent = _StaticMesh;
	
	_StaticMesh->SetRelativeLocation(RootComponent->GetRelativeLocation());
	_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	_SpringArm->SetupAttachment(_StaticMesh);
	_SpringArm->SetRelativeLocation(FVector(-30, 0, 100));
	
	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(_SpringArm);

	_StaticMesh->SetSimulatePhysics(true);
	
	_StaticMesh->BodyInstance.bLockXRotation = true;
	_StaticMesh->BodyInstance.bLockYRotation = true;
}


void ACubeBase::BeginPlay()
{
	Super::BeginPlay();
	
}
void ACubeBase::Input_JumpPressed_Implementation()
{
	if (bCanJump) 
	{
		bCanJump = false;
		CheckIfGrounded();
		if (bIsGrounded)
		{
			_StaticMesh->AddImpulse(FVector(0, 0, 75000));
			bIsGrounded = false;
		}
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_JumpCooldown, this, &ACubeBase::ResetJumpCooldown, JumpCooldown, false);
		//make cool down UI
	}
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
	RootComponent->AddWorldOffset(_MovementOffset);

	OnMoved.Broadcast(GetActorLocation());
	
}


void ACubeBase::Pawn_Init_Implementation(UCubeType* Type, FVector Location)
{
	_StaticMesh->SetMassOverrideInKg(FName(NAME_None),Type->_CubeMass, true);
	
	IPawnInterface::Pawn_Init_Implementation(Type, Location);
	_StaticMesh->SetStaticMesh(Type->_CubeMesh);
	_StaticMesh->SetMaterial(0, Type->_CubeMaterial);
	
	FTransform NewTransform;
	NewTransform.SetScale3D(Type->_CubeSize);
	NewTransform.SetLocation(Location);
	RootComponent->SetRelativeTransform(NewTransform);
	
	_CubeExtents2D = FVector(_StaticMesh->GetComponentScale().X * 50.0f, _StaticMesh->GetComponentScale().Y * 50.0f, 0.0f);
	_CubeExtents3D = FVector(_StaticMesh->GetComponentScale().X * 50.0f, _StaticMesh->GetComponentScale().Y * 50.0f, _StaticMesh->GetComponentScale().Z * 50.0f);
}


// Called every frame
void ACubeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACubeBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACubeBase::CheckIfGrounded()
{
	FVector Start = _StaticMesh->GetComponentLocation();
	FVector End = Start - FVector(0, 0, 5); // Check downwards
	FRotator Rotation = FRotator(_StaticMesh->GetComponentRotation()); 
	
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	FQuat BoxRotation = Rotation.Quaternion();
	
	HitResult = DownwardTrace(Start, End, CollisionParams, BoxRotation, ECC_Visibility);
	
	if (HitResult.Normal.Z > 0.5f) 
	{
		bIsGrounded = true;
	}
	else
	{
		bIsGrounded = false;
	}
	
	DrawDebugBox(GetWorld(), HitResult.Location, _CubeExtents2D, BoxRotation, FColor::Green, false, 5, 0, 1);
}

void ACubeBase::ResetJumpCooldown()
{
	bCanJump = true;
}


FHitResult ACubeBase::ReturnActorUnderPawn_Implementation()
{
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.MobilityType = EQueryMobilityType::Static;
	return ACubeBase::DownwardTrace(_StaticMesh->GetComponentLocation(), _StaticMesh->GetComponentLocation() - FVector(0,0,20), CollisionParams, _StaticMesh->GetComponentRotation().Quaternion(), ECC_Visibility);
}

FHitResult ACubeBase::DownwardTrace(FVector StartPos, FVector EndPos, FCollisionQueryParams CollisionParams, FQuat BoxRotation, ECollisionChannel TraceChannel)
{
	FHitResult HitResult;
	
	bool bHit = GetWorld()->SweepSingleByChannel
		(
			HitResult,
			StartPos,
			EndPos,
			BoxRotation, 
			ECC_Visibility,                 
			FCollisionShape::MakeBox(_CubeExtents2D),  
			CollisionParams
		);
	DrawDebugBox(GetWorld(), HitResult.Location, _CubeExtents2D, BoxRotation, FColor::Green, false, 5, 0, 1);
	return HitResult;
}




