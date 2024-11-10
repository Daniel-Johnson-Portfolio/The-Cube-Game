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

private:
	UPROPERTY(VisibleAnywhere, Category="Characters")
	TMap<AActor*, FVector> InitialPositions;
	FTimerHandle MovementCheckTimer;     
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="SetupActor")
	TObjectPtr<UStaticMeshComponent> _StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SetupActor")
	UStaticMesh* _StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SetupActor")
	UMaterial* _Material;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	APlayerController* _PlayerController;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> _OverlapBox;
	FVector _PlaneExtents2D;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Puzzle")
	int _CubesOverlapped;

	UPROPERTY()
	TArray<AActor*> _OverlappedPawns;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Puzzle")
	TArray<AActor*> _StackedPawns;

	UFUNCTION()
	void ComponentExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ComponentEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	void CheckForMovement();

	UFUNCTION()
	void Init();
};
