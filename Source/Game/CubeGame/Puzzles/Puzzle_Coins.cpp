#include "Puzzle_Coins.h"
#include "Components/SphereComponent.h"
#include "Game/CubeGame/PawnInterface.h"
#include "Kismet/KismetSystemLibrary.h"

APuzzle_Coins::APuzzle_Coins()
{
	PrimaryActorTick.bCanEverTick = false;
	_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	RootComponent = _Collider;
	_StaticMeshComponent->SetupAttachment(_Collider);
	_StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	_Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &APuzzle_Coins::CoinPickUp);
}

void APuzzle_Coins::OnCoinCollectedHook_Implementation()
{
	//Designer hook
}

// Called when the game starts or when spawned
void APuzzle_Coins::BeginPlay()
{
	Super::BeginPlay();
	_StaticMeshComponent->SetMaterial(0,_CoinType->_CubeMaterial); //Sets colour to corresponding cube type
	if (!GetWorld()->GetTimerManager().IsTimerActive(SpinTimer))
	{
		GetWorld()->GetTimerManager().SetTimer(SpinTimer, this, &APuzzle_Coins::CoinSpin, 0.01f, true); //starts the spinning timer
	}
	OnCoinCollected.AddUniqueDynamic(this, &APuzzle_Coins::OnCoinCollectedHook);
	
}

APuzzle_Coins* APuzzle_Coins::GetCoin_Implementation()
{
	return this; //Returns reference to self
}

void APuzzle_Coins::CoinSpin()
{
	this->AddActorWorldRotation(FRotator(0,1,0));
}

void APuzzle_Coins::CoinPickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UPawnInterface::StaticClass()))
	{
		if(_CoinType->UniqueID == IPawnInterface::Execute_ReturnCubeType(OtherActor)) //If pawn is of correct type
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

