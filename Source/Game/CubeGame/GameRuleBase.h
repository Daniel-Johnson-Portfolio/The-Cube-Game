// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameRuleBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameRuleCompleteSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class GAME_API UGameRuleBase : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGameRuleBase();
	FGameRuleCompleteSignature OnComplete;
	void BroadcastComplete();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
