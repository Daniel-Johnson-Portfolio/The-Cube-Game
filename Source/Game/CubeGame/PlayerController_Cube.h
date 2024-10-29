// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController_Cube.generated.h"

class ACubeBase;
/**
 * 
 */
class UInputAction;
struct FInputActionValue;

UCLASS(Abstract)
class GAME_API APlayerController_Cube : public APlayerController
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
	TArray<ACubeBase*> _CharacterArray;

	UPROPERTY(VisibleAnywhere, Category="Characters")
	TArray<TObjectPtr<AActor>> _PlayerStarts;

	
	virtual void SetupInputComponent() override;

	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void JumpPressed();
	void SwapChar();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

public:
	void FindPlayerStart_Implementation();
	
	UFUNCTION()
	void MoveAI(FVector pos);
	
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
