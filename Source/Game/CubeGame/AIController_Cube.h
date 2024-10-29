// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "AIController_Cube.generated.h"

UCLASS()
class GAME_API AAIController_Cube : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAIController_Cube();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="PlayerController")
	APawn* _CurrentlyActivePawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
