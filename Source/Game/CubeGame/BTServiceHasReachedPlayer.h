// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTServiceHasReachedPlayer.generated.h"

/**
 * 
 */
class ACubeBase;
UCLASS()
class GAME_API UBTServiceHasReachedPlayer : public UBTService
{
	GENERATED_BODY()
public:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
	UPROPERTY()
	AAIController* _AiController;

	UPROPERTY()
	ACubeBase* _CurrentPlayer;

	UPROPERTY()
	ACubeBase* _AIPawn;
};
