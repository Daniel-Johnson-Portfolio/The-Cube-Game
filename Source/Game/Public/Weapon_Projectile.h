// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon_Base.h"
#include "Weapon_Projectile.generated.h"

class AProjectile;

UCLASS(Abstract)
class GAME_API AWeapon_Projectile : public AWeapon_Base
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	virtual void Fire() override;

protected:


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectile> _ProjectileClass;
};
