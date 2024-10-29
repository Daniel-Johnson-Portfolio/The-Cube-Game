// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController_Cube.h"
#include "Inputs.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CubeBase.generated.h"

class UCubeType;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPawnHasMovedSignature, FVector, Pos);

UCLASS()
class GAME_API ACubeBase : public APawn, public IInputs
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACubeBase();

	UPROPERTY(BlueprintAssignable)
	FPawnHasMovedSignature OnMoved;
	
	void Init(UCubeType* type);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> _Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> _SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> _BoxComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	int _CameraPitchLimit = 30;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement Settings")
	float _Movementspeed = 300.0f;

	

public:
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_JumpReleased_Implementation() override;
	virtual void Input_Look_Implementation(FVector2D Value) override;
	virtual void Input_Move_Implementation(FVector2D Value) override;
	virtual void Input_AIMove_Implementation(FVector Pos) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetLocaiton(FVector location);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character")
	UCubeType* _CubeType;
};
