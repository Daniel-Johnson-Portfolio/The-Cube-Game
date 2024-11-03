// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Puzzle_Stack.generated.h"

UCLASS(Abstract)
class GAME_API APuzzle_Stack : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APuzzle_Stack();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> _OverlapBox;
	FVector _PlaneExtents2D;

	UPROPERTY()
	TArray<AActor*> OverlappedPawns;

	UFUNCTION()
	void InterfaceToOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
