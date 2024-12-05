// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CubeSlots_Component.generated.h"


class APuzzle_CubeSlots;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAME_API UCubeSlots_Component : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCubeSlots_Component();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> _FoundCubeSlots;

	UFUNCTION()
	void ValidActor(bool bIsValidActor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int _amountOfValidActors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bhasAlreadyOpened = false;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
