// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController_Cube.generated.h"

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

	
	virtual void SetupInputComponent() override;

	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void JumpPressed();
	void JumpReleased();

	virtual void OnPossess(APawn* InPawn) override;
};
