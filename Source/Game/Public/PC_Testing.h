// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//#include "InputAction.h"
#include "PC_Testing.generated.h"


struct FInputActionValue;

class UInputAction;

/**
 * 
 */
UCLASS(Abstract)
class GAME_API APC_Testing : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _DebugAction;

	virtual void SetupInputComponent() override;

	virtual void Debug(const FInputActionValue& Value);
	
};
