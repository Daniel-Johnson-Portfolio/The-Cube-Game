// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	_MaxHealth = 100.0f;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	_CurrentHealth = _MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealthComponent::DamageTaken);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	const float change = FMath::Min(_CurrentHealth, Damage);

	_CurrentHealth -= change;
	OnDamaged.Broadcast(_CurrentHealth, _MaxHealth, change);
	UE_LOG(LogTemp, Display, TEXT("Damage for %f, %f health remaining"), change, _CurrentHealth);
	if(_CurrentHealth == 0.0f)
	{
		OnDead.Broadcast(InstigatedBy);
		UE_LOG(LogTemp, Display, TEXT("Dead"));
	}
}

