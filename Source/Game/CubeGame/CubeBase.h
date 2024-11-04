// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inputs.h"
#include "PawnInterface.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CubeBase.generated.h"

class UCubeType;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPawnHasMovedSignature, FVector, Pos);

UCLASS()
class GAME_API ACubeBase : public ACharacter, public IInputs, public IPawnInterface
{
	//Changing to character may be an idea
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACubeBase();

	UPROPERTY(BlueprintAssignable)
	FPawnHasMovedSignature OnMoved;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> _Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> _SpringArm;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	int _CameraPitchLimit = 30;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement Settings")
	float _Movementspeed = 300.0f;

	FVector _CubeExtents2D;

	

public:
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_Look_Implementation(FVector2D Value) override;
	virtual void Input_Move_Implementation(FVector2D Value) override;
	
	virtual void Input_AIMove_Implementation(FVector Pos) override;

	virtual void Pawn_Init_Implementation(UCubeType* Type, FVector Location) override;

	//virtual FHitResult ACubeBase::ReturnAactorUnderPawn_Implementation(FCollisionQueryParams Collision) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character")
	UCubeType* _CubeType;

private:
	bool bIsGrounded = false;
	bool bCanJump = true;
	float JumpCooldown = 0.5f;               
	FTimerHandle TimerHandle_JumpCooldown;

	void CheckIfGrounded();
	void ResetJumpCooldown();
	FHitResult DownwardTrace(FVector StartPos, FVector EndPos, FCollisionQueryParams CollisionParams, FQuat BoxRotation, ECollisionChannel TraceChannel = ECC_Visibility);
};
