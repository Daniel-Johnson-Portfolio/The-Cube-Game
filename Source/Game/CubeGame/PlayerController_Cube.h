﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController_Cube.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerControllerInterface.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController_Cube.generated.h"

class ACubeBase;
/**
 * 
 */
class UInputAction;
struct FInputActionValue;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FPuzzleInformationSignature, int, amountofCubes, float, CubeStackHeight, float, biggestCubeFace);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCubesStackedSignature);

UCLASS(Abstract)
class GAME_API APlayerController_Cube : public APlayerController, public IPlayerControllerInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _LookAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _MoveAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _JumpAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _SwapChar;
	UPROPERTY(EditAnywhere, Category="Characters")
	TArray<TSubclassOf<ACubeBase>> _CharacterClassArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character")
	int _CurrentCharacter = 0;
	
	UPROPERTY(VisibleAnywhere, Category="Characters")
	TArray<ACubeBase*> _NPCCharacterArray; //List of all characters that the play isn't currently controlling
	UPROPERTY(VisibleAnywhere, Category="Characters")
	TArray<ACubeBase*> _AllCharacterArray; //List is of all characters and does not change after begin play when they are instanced

	UPROPERTY(EditAnywhere, Category="Characters")
	TSubclassOf<ACubeBase> _CubeBase;

	UPROPERTY(VisibleAnywhere, Category="Characters")
	TArray<TObjectPtr<AActor>> _PlayerStarts;

	UPROPERTY(VisibleAnywhere, Category="Inputs")
	bool isMoving;

	UPROPERTY(VisibleAnywhere, Category="Characters")
	TArray<AAIController_Cube*> _AiControllers;
	
	UPROPERTY(EditAnywhere, Category="Characters")
	TSubclassOf<AAIController_Cube> _AiControllerBluePrint;
	
	
	virtual void SetupInputComponent() override;

	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void JumpPressed();
	void SwapChar();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

public:
	void FindPlayerStart_Implementation();

	virtual void CubesOnPlatform_Implementation(int Amount); 
	
	UFUNCTION()
	void MoveAI(FVector pos);

	UPROPERTY(BlueprintAssignable)
	FCubesStackedSignature OnStacked;
	

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Characters")
//	AAIController_Cube* _AiController;
	
	UPROPERTY(BlueprintAssignable)
	FPuzzleInformationSignature OnPuzzleInformation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cube Data")
	UDataTable* _CubeDataTable;

	UPROPERTY()
	TSubclassOf<ACubeBase> _CubeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> _InputMapping;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACubeBase* _PossessedPawn;

	// Function to return the input mapping context
	UInputMappingContext* GetMappingContext() const { return _InputMapping; }

};
