// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Projectile.h"
#include "Components/ArrowComponent.h"
#include "Projectile.h"

void AWeapon_Projectile::Fire()
{
	UWorld* const world = GetWorld();
	if(world == nullptr || _ProjectileClass == nullptr) { return; }
    
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	spawnParams.Instigator = GetInstigator();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	world->SpawnActor(_ProjectileClass, &_Muzzle->GetComponentTransform(), spawnParams);
 
	Super::Fire();
}
