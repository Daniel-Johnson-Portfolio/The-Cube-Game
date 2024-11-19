// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_HasReachedPlayer.generated.h"

class ACubeBase;
/**
 * 
 */
UCLASS()
class GAME_API UBTTask_HasReachedPlayer : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
	UPROPERTY()
	AAIController* _AiController;

	UPROPERTY()
	ACubeBase* _CurrentPlayer;

	UPROPERTY()
	ACubeBase* _AIPawn;
};
