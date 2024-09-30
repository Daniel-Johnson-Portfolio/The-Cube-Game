// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "TestingActor.generated.h"

UCLASS(Abstract)
class GAME_API ATestingActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestingActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> _Root;
	UPROPERTY(EditAnywhere, BlueprintreadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _Arrow;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
