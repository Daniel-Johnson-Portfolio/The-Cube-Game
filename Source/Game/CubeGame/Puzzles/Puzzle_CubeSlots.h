// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle_CubeSlots.generated.h"

class UBoxComponent;
class UCubeType;

UCLASS()
class GAME_API APuzzle_CubeSlots : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APuzzle_CubeSlots();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Puzzle")
	UCubeType* _CubeType;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void CubeEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> _BoxComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> _ActorsOnPlatform;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bValidActor;

	UPROPERTY()
	APlayerController* _PlayerController;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
