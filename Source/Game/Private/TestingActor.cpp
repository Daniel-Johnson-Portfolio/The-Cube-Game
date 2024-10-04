// Fill out your copyright notice in the Description page of Project Settings.


#include "TestingActor.h"

#include "MovieSceneObjectBindingID.h"
#include "Components/BoxComponent.h"
#include "Preferences/PersonaOptions.h"


// Sets default values
ATestingActor::ATestingActor()
{
	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = _Collider;

	_Collider->OnComponentHit.AddUniqueDynamic(this, &ATestingActor::ATestingActor::Handle_ColliderHit);
	//_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//RootComponent = _Root;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh -> SetupAttachment(_Collider);

	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	_Arrow -> SetupAttachment(_Collider);

	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATestingActor::Handle_ColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Display, TEXT("======================================") );
}

// Called every frame
void ATestingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



