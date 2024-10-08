// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_Testing.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"


void APC_Testing::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EIP->BindAction(_DebugAction, ETriggerEvent::Triggered, this, &APC_Testing::Debug);

		
	}
}

void APC_Testing::Debug(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("DEBUG WORKS:::::::::::::::::::::::::::::::::::::::::::::::::::"));
	//if(AActor* Testing - UGameplayStatics::GetActorOfClass(GetWorld(), AFirstActor::StaticClass()))
	//{

		
	//}

	
}
