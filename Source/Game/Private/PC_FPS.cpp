// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_FPS.h"
#include "EnhancedInputComponent.h"
#include "MyInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnhancedInputSubsystems.h"

void APC_FPS::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EIP->BindAction(_LookAction, ETriggerEvent::Triggered, this, &APC_FPS::Look);
		EIP->BindAction(_MoveAction, ETriggerEvent::Triggered, this, &APC_FPS::Move);
		EIP->BindAction(_JumpAction, ETriggerEvent::Triggered, this, &APC_FPS::JumpPressed);
		EIP->BindAction(_JumpAction, ETriggerEvent::Completed, this, &APC_FPS::JumpReleased);
		EIP->BindAction(_FireAction, ETriggerEvent::Triggered, this, &APC_FPS::FirePressed);
		EIP->BindAction(_FireAction, ETriggerEvent::Completed, this, &APC_FPS::FireReleased);

		
	}
}

void APC_FPS::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UMyInterface::StaticClass()))
		{
			IMyInterface::Execute_Input_Look(currentPawn, LookVector);
		}
	}
}

void APC_FPS::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UMyInterface::StaticClass()))
		{
			IMyInterface::Execute_Input_Move(currentPawn, MoveVector);
		}
	}
}

void APC_FPS::JumpPressed()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UMyInterface::StaticClass()))
		{
			IMyInterface::Execute_Input_JumpPressed(currentPawn);
		}
	}
	
}

void APC_FPS::JumpReleased()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UMyInterface::StaticClass()))
		{
			IMyInterface::Execute_Input_JumpReleased(currentPawn);
		}
	}
}

void APC_FPS::FirePressed()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UMyInterface::StaticClass()))
		{
			IMyInterface::Execute_Input_FirePressed(currentPawn);
		}
	}
}

void APC_FPS::FireReleased()
{
	if(APawn* currentPawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentPawn, UMyInterface::StaticClass()))
		{
			IMyInterface::Execute_Input_FireReleased(currentPawn);
		}
	}
}

void APC_FPS::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if(UEnhancedInputLocalPlayerSubsystem* Subsytem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if(UKismetSystemLibrary::DoesImplementInterface(InPawn, UMyInterface::StaticClass()))
		{
			Subsytem->AddMappingContext(IMyInterface::Execute_GetMappingContext(InPawn),0);
			UE_LOG(LogTemp, Display, TEXT("HFUEHFEHUFRrt"));
		}

		
	}
	
}
