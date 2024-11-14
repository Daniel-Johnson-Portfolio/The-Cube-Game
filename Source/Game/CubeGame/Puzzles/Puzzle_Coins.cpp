// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle_Coins.h"


#include "Components/SphereComponent.h"
#include "Game/CubeGame/PawnInterface.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
APuzzle_Coins::APuzzle_Coins()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	RootComponent = _Collider;
	_StaticMeshComponent->SetupAttachment(_Collider);
	_StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	_Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &APuzzle_Coins::CoinPickUp);
}

// Called when the game starts or when spawned
void APuzzle_Coins::BeginPlay()
{
	Super::BeginPlay();
	_StaticMeshComponent->SetMaterial(0,_CoinType->_CubeMaterial);
	if (!GetWorld()->GetTimerManager().IsTimerActive(SpinTimer))
	{
		GetWorld()->GetTimerManager().SetTimer(SpinTimer, this, &APuzzle_Coins::CoinSpin, 0.01f, true);
	}
	
}

APuzzle_Coins* APuzzle_Coins::GetCoin_Implementation()
{
	return this;
}

void APuzzle_Coins::CoinSpin()
{
	this->AddActorWorldRotation(FRotator(0,1,0));
}

void APuzzle_Coins::CoinPickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UPawnInterface::StaticClass()))
	{
		if(_CoinType->UniqueID == IPawnInterface::Execute_ReturnCubeType(OtherActor))
		{
			OnCoinCollected.Broadcast();
			this->Destroy();
			
		}
		
	}
}

// Called every frame
void APuzzle_Coins::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

