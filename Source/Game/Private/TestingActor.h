// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyInterface.h"

#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "TestingActor.generated.h"

class UBoxComponent;

UCLASS(Abstract)
class GAME_API ATestingActor : public AActor, public  IMyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestingActor();
	virtual void Input_Look_Implementation() override;
	
protected:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TObjectPtr<USceneComponent> _Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> _Collider;  
	
	UPROPERTY(EditAnywhere, BlueprintreadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _Arrow;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void Handle_ColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
