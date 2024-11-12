// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "PawnInterface.generated.h"


class UCubeType;
// This class does not need to be modified.
UINTERFACE()

class UPawnInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAME_API IPawnInterface
{
	
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Pawn_Init(UCubeType* Type, FVector Location);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FHitResult ReturnActorUnderPawn();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FName ReturnCubeType();
	
};
