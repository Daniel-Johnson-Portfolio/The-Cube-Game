// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetComponent.h"

#include "HealthComponent.h"


// Sets default values for this component's properties
UTargetComponent::UTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false
	;
	_PointsValue = 1;
	// ...
}


// Called when the game starts
void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* owner = GetOwner();
	_Health = owner->FindComponentByClass<UHealthComponent>();
	if (_Health == nullptr)
	{
		_Health = NewObject<UHealthComponent>(owner, TEXT("Health")); //creates health component if it doesnt exist
		owner->AddInstanceComponent(_Health);
		_Health->RegisterComponent();
		owner->Modify();
	}

	_Health->OnDead.AddUniqueDynamic(this, &UTargetComponent::Handle_HealthDead); //Binds Handle dead to on death

	OnTargetRegisterd.Broadcast(this); 
	
	// ...
	
}


void UTargetComponent::Handle_GameRuleRequestTarget()
{
	OnTargetRegisterd.Broadcast(this);
	
}

void UTargetComponent::Handle_HealthDead(AController* causer)
{
	OnDestroyed.Broadcast(this, causer, _PointsValue);
	GetOwner()->Destroy();
}

// Called every frame
void UTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

