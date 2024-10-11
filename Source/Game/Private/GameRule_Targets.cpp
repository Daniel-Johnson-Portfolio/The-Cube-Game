// Fill out your copyright notice in the Description page of Project Settings.


#include "GameRule_Targets.h"

#include "TargetComponent.h"


// Sets default values for this component's properties
UGameRule_Targets::UGameRule_Targets()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UGameRule_Targets::Init()
{
	Super::Init();
	UTargetComponent::OnTargetRegisterd.AddUniqueDynamic(this, &UGameRule_Targets::Handle_TargetRegistered);
	OnRequestTargets.Broadcast();
}

// Called when the game starts
void UGameRule_Targets::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UGameRule_Targets::Handle_TargetRegistered(UTargetComponent* target)
{
	if(_Targets.Contains(target)){return;}
	_Targets.Add(target);
	target->OnDestroyed.AddUniqueDynamic(this, &UGameRule_Targets::Handle_TargetDestoryed);
	AmountRemaining++;
	
}

void UGameRule_Targets::Handle_TargetDestoryed(UTargetComponent* target, AController* causer, int targetValue)
{
	_Targets.Remove(target);
	AmountRemaining--;
	BroadcastPointsScored(causer, targetValue);
	if(AmountRemaining == 0)
	{
		BroadcastComplete();
	}
}

// Called every frame
void UGameRule_Targets::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

