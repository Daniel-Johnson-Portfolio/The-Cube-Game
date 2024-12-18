﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inputs.h"
#include "PawnInterface.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CubeBase.generated.h"

class UCubeType;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPawnHasMovedSignature, FVector, Pos);

UCLASS(Abstract)
class GAME_API ACubeBase : public APawn ,public IInputs, public IPawnInterface
{
	//Changing to character may be an idea
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACubeBase();

	UPROPERTY(BlueprintAssignable)
	FPawnHasMovedSignature OnMoved;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _StaticMesh;

	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> _Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> _SpringArm;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	int _CameraPitchLimit = 30;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement Settings")
	float _Movementspeed = 300.0f;

	FVector _CubeExtents2D;


	

public:
	bool bIsGrounded = false;
	bool bCanJump = true;
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_Look_Implementation(FVector2D Value) override;
	virtual void Input_Move_Implementation(FVector2D Value) override;
	virtual ACubeBase* GetPawn_Implementation() override;
	virtual FVector GetPawnLocation_Implementation() override;
	virtual void SetPawnLocation_Implementation(FVector location) override;
	virtual void Pawn_Init_Implementation(UCubeType* Type, FVector Location) override;
	

	virtual FHitResult ReturnActorUnderPawn_Implementation() override;

	virtual FName ReturnCubeType_Implementation() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character")
	UCubeType* _CubeType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character")
	FVector _CubeExtents3D;

private:
	float JumpCooldown = 1.25f;               
	FTimerHandle TimerHandle_JumpCooldown;

	void CheckIfGrounded();
	void ResetJumpCooldown();
	FHitResult DownwardTrace(FVector StartPos, FVector EndPos, FCollisionQueryParams CollisionParams, FQuat BoxRotation, ECollisionChannel TraceChannel = ECC_Visibility);
};
