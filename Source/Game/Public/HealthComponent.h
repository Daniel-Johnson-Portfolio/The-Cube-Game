﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthDeadSignature, AController*, causer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthDamagedSignature, float, newHealth, float, maxHealth, float, change);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();
	UPROPERTY(BlueprintAssignable)
	FHealthDeadSignature OnDead;
	UPROPERTY(BlueprintAssignable)
	FHealthDamagedSignature OnDamaged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float _CurrentHealth;

private:
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );
	//Gets the 5 params
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:

};
