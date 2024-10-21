// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_FPS.h"

#include "AP_FPS.h"
#include "EnhancedInputComponent.h"
#include "MyInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "Widget_Hud.h"
#include "Blueprint/UserWidget.h"



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

void APC_FPS::AddPointsToUI(float Points)
{
	_HUDWidget->UpdateScore(Points);
}

void APC_FPS::BeginPlay()
{
	Super::BeginPlay();
	_Pawn = Cast<AAP_FPS>(this->GetCharacter());
	_Pawn->OnPawnDamaged.AddUniqueDynamic(this, &APC_FPS::UpdateHealth);
	if(_HUDWidgetClass)
	{	
		_HUDWidget = CreateWidget<UWidget_Hud, APC_FPS*>(this, _HUDWidgetClass.Get());
		_HUDWidget->AddToViewport();
	}
	
}

void APC_FPS::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
 
	if(UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if(UKismetSystemLibrary::DoesImplementInterface(InPawn, UMyInterface::StaticClass()))
		{
			subsystem->AddMappingContext(IMyInterface::Execute_GetMappingContext(InPawn), 0);
		}
	}
}
void APC_FPS::UpdateHealth(float Change)
{
	UE_LOG(LogTemp, Display, TEXT("Damage for %f,"),Change);
	_HUDWidget->UpdateHealth(Change);
}


