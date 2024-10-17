// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Base.h"

#include "Components/ArrowComponent.h"


// Sets default values
AWeapon_Base::AWeapon_Base()
{
	PrimaryActorTick.bCanEverTick = false;
	_FireDelay = 0.f;
 
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;
 
	_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(RootComponent);
 
	_Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_Muzzle->SetupAttachment(_Mesh);
}

void AWeapon_Base::StartFire()
{
	Fire();
	if(_FireDelay != 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(_FireDelayTimer, this, &AWeapon_Base::Fire, _FireDelay, true);
	}
}
 
void AWeapon_Base::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(_FireDelayTimer);
}
 
void AWeapon_Base::Fire()
{
	OnFire.Broadcast();
}


