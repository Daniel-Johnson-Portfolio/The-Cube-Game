// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController_Cube.h"

#include "CubeBase.h"
#include "EnhancedInputComponent.h"
#include "Inputs.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"


void APlayerController_Cube::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EIP->BindAction(_LookAction, ETriggerEvent::Triggered, this, &APlayerController_Cube::Look);
		EIP->BindAction(_MoveAction, ETriggerEvent::Triggered, this, &APlayerController_Cube::Move);
		EIP->BindAction(_JumpAction, ETriggerEvent::Triggered, this, &APlayerController_Cube::JumpPressed);
		EIP->BindAction(_JumpAction, ETriggerEvent::Completed, this, &APlayerController_Cube::JumpReleased);
		EIP->BindAction(_SwapChar, ETriggerEvent::Triggered, this , &APlayerController_Cube::SwapChar);
	}


}

void APlayerController_Cube::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	UE_LOG(LogTemp, Display, TEXT("X: %f Y: %f"), LookVector.X, LookVector.Y);
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputs::StaticClass()))
		{
			IInputs::Execute_Input_Look(currentPawn, LookVector);
		}
	}
}

void APlayerController_Cube::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputs::StaticClass()))
		{
			IInputs::Execute_Input_Move(currentPawn, MoveVector);
		}
	}
}

void APlayerController_Cube::JumpPressed()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputs::StaticClass()))
		{
			IInputs::Execute_Input_JumpPressed(currentPawn);
		}
	}
}

void APlayerController_Cube::JumpReleased()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UInputs::StaticClass()))
		{
			IInputs::Execute_Input_JumpReleased(currentPawn);
		}
	}
}

void APlayerController_Cube::SwapChar(){

	this->Possess(_CharactersMap.FindRef(1));
}

void APlayerController_Cube::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if(UKismetSystemLibrary::DoesImplementInterface(InPawn, UInputs::StaticClass()))
		{
			subsystem->AddMappingContext(IInputs::Execute_GetMappingContext(InPawn), 0);
		}
	}
}

void APlayerController_Cube::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACubeBase::StaticClass(), FoundActors);
	TArray<ACubeBase*> CubeBaseActors;
	for (AActor* Actor : FoundActors)
	{
		ACubeBase* CubeBaseActor = Cast<ACubeBase>(Actor);
		if (CubeBaseActor)
		{
			CubeBaseActors.Add(CubeBaseActor);
			_CharactersMap.Add(FoundActors.Find(Actor) ,CubeBaseActor);
		}
	}
	
}
