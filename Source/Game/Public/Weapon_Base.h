// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
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

	UPROPERTY(BlueprintAssignable)
	FWeaponFireSignature OnFire;
    
	void StartFire();
	void StopFire();
    

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _Root;
 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> _Mesh;
    
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _Muzzle;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _FireDelay;
	FTimerHandle _FireDelayTimer;
 
	UFUNCTION()
	virtual void Fire();

public:

};
