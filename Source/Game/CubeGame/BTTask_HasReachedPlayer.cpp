// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_HasReachedPlayer.h"

#include "AIController.h"
#include "AiControllerInterface.h"
#include "CubeBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

EBTNodeResult::Type UBTTask_HasReachedPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(UKismetSystemLibrary::DoesImplementInterface(OwnerComp.GetAIOwner(), UAiControllerInterface::StaticClass()))
	{
		_AiController = OwnerComp.GetAIOwner();
		_CurrentPlayer = IAiControllerInterface::Execute_newPawn(_AiController);
		if(UKismetSystemLibrary::DoesImplementInterface(_AiController->GetPawn(), UPawnInterface::StaticClass()))
		{
			_AIPawn = IPawnInterface::Execute_GetPawn(_AiController->GetPawn());
		}
		FVector AiPawnLocation = IPawnInterface::Execute_GetPawnLocation(_AIPawn);
		FVector CurrentPlayerLocation = IPawnInterface::Execute_GetPawnLocation(_CurrentPlayer);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsInRange"), (FVector::Dist(CurrentPlayerLocation, AiPawnLocation) < 250.0f));
	}
	return EBTNodeResult::Succeeded;
}