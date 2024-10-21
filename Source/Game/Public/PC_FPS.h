// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "PC_FPS.generated.h"

class AAP_FPS;
class UWidget_Hud;
struct FInputActionValue;
class UInputAction;
/**
 * 
 */
UCLASS(Abstract)
class GAME_API APC_FPS : public APlayerController
{

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AAP_FPS> _Pawn;
	
	void AddPointsToUI(float Points);
	
protected:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _LookAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _MoveAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _JumpAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _FireAction;

	
	virtual void SetupInputComponent() override;

	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void JumpPressed();
	void JumpReleased();
	void FirePressed();
	void FireReleased();
	
	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidget_Hud> _HUDWidgetClass;
	TObjectPtr<UWidget_Hud> _HUDWidget;

	virtual void BeginPlay() override;

private:
	GENERATED_BODY()
	UFUNCTION()
	void UpdateHealth(float Change);
	
};
