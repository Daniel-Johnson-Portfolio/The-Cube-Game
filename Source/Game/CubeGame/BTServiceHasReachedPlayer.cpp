// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceHasReachedPlayer.h"

#include "AiControllerInterface.h"
#include "PawnInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AIController.h"
#include "CubeBase.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTServiceHasReachedPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
}
