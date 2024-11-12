// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameRule.h"
#include "GameRule_CubeSlots.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAME_API UGameRule_CubeSlots : public UGameRule
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGameRule_CubeSlots();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void AddValidActor();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
