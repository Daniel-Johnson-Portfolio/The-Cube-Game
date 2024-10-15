// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon_Base.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFireSignature);

UCLASS(Abstract)
class GAME_API AWeapon_Base : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
