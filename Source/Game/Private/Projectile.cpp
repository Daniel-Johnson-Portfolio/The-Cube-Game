// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AProjectile::AProjectile()
{
	_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = _Collider;
	_Collider->SetCollisionProfileName("Projectile");
	_Collider->OnComponentHit.AddUniqueDynamic(this, &AProjectile::Handle_Hit);
 
	_ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	_ProjectileMovement->UpdatedComponent = _Collider;
	_ProjectileMovement->InitialSpeed = 3000.f;
	_ProjectileMovement->MaxSpeed = 3000.f;
	_ProjectileMovement->bRotationFollowsVelocity = true;
	_ProjectileMovement->bShouldBounce = true;
 
	InitialLifeSpan = 3.f;
}
 
void AProjectile::Handle_Hit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		UGameplayStatics::ApplyDamage(OtherActor, _Damage, GetInstigatorController(), this, UDamageType::StaticClass());
 
		if(OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.f, GetActorLocation());   
		}
		Destroy();
	}
}


