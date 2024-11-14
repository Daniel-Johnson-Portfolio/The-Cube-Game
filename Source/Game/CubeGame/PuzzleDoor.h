// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DoorInterface.h"
#include "GameFramework/Actor.h"
#include "PuzzleDoor.generated.h"

UCLASS()
class GAME_API APuzzleDoor : public AActor, public IDoorInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APuzzleDoor();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="SetupActor")
	TObjectPtr<UStaticMeshComponent> _StaticMeshComponent;
	FTimerHandle MovementCheckTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DoorSettings")
	float _DoorOpenHeight = 500.0f;

	FVector NewLocation;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OpenDoor_Implementation() override;
	void DoorMovement();

	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
