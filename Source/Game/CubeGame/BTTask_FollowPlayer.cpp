// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FollowPlayer.h"

#include "AIController.h"
#include "AiControllerInterface.h"
#include "CubeBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

EBTNodeResult::Type UBTTask_FollowPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(UKismetSystemLibrary::DoesImplementInterface(OwnerComp.GetAIOwner(), UAiControllerInterface::StaticClass()))
	{
		_AiController = OwnerComp.GetAIOwner();
		_CurrentPlayer = IAiControllerInterface::Execute_newPawn(_AiController);
		_AIPawn = OwnerComp.GetAIOwner()->GetPawn();

		FVector AiPawnLocation = _AIPawn->GetActorLocation();
		FVector CurrentPlayerLocation = _CurrentPlayer->GetActorLocation();
		
		bInRange = (FVector::Dist(CurrentPlayerLocation, AiPawnLocation) < 250.0f);
		if(!bInRange && !OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("Pause")))
		{
			FVector NewLocation = FMath::VInterpTo(AiPawnLocation, FVector(CurrentPlayerLocation.X, CurrentPlayerLocation.Y, CurrentPlayerLocation.Z / 2.0f), GetWorld()->GetDeltaSeconds(), 1.0f);
			_AIPawn->SetActorLocation(NewLocation);
			return EBTNodeResult::Failed;
		}
		if(OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("Pause")))
		{
			_AIPawn->SetActorLocation(_AIPawn->GetActorLocation());
			return EBTNodeResult::Failed;
		}
			return EBTNodeResult::Succeeded;
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

